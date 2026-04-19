#include "Generavimas.h"

#include "laikai.h"
#include "spausdinam.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <iterator>

bool galimasPavadinimas(const std::string& pav)
{
    std::ifstream f(pav);
    return f.is_open();
}

std::string failoPavadinimas(const std::string& bazinisPavadinimas)
{
    std::string pavadinimas = bazinisPavadinimas + ".txt";
    int count = 1;

    while (galimasPavadinimas(pavadinimas))
    {
        count++;
        pavadinimas = bazinisPavadinimas + "_" + std::to_string(count) + ".txt";
    }

    return pavadinimas;
}

SkirstymoStrategija pasirinktiStrategija()
{
    std::cout << "\nPasirinkite studentu skirstymo strategija:\n";
    std::cout << "1 - Sukurti du naujus konteinerius (vargsiukai ir protai)\n";
    std::cout << "2 - Kurti tik vargsiuku konteineri, o kietiakus palikti bendrame konteineryje\n";
    std::cout << "3 - Strategija su efektyviais metodais.\n";

    int pasirinkimas;
    std::cin >> pasirinkimas;

    if (!std::cin || pasirinkimas < 1 || pasirinkimas > 3)
    {
        throw std::runtime_error("Neteisingas strategijos pasirinkimas.");
    }

    return static_cast<SkirstymoStrategija>(pasirinkimas);
}

SkirstymoRezultatas skirstymasStrategija1(const StudContainer& studis)
{
    SkirstymoRezultatas rezultatas;

    for (const auto& s : studis)
    {
        if (s.galrezVid < 5.0f)
        {
            rezultatas.vargsiukai.push_back(s);
        }
        else
        {
            rezultatas.protai.push_back(s);
        }
    }

    return rezultatas;
}

SkirstymoRezultatas skirstymasStrategija2(StudContainer& studis)
{
    SkirstymoRezultatas rezultatas;

    for (auto i = studis.begin(); i != studis.end();)
    {
        if (i->galrezVid < 5.0f)
        {
            rezultatas.vargsiukai.push_back(*i);
            i = studis.erase(i);
        }
        else
        {
            i++;
        }
    }

    rezultatas.protai = std::move(studis);
    return rezultatas;
}

SkirstymoRezultatas skirstymasStrategija3(StudContainer& studis)
{
    SkirstymoRezultatas rezultatas;

    auto riba = std::partition(studis.begin(), studis.end(),
        [](const Stud& s)
        {
            return s.galrezVid >= 5.0f;
        });

    rezultatas.vargsiukai.assign(riba, studis.end());
    rezultatas.protai.assign(studis.begin(), riba);

    studis.clear();

    return rezultatas;
}

SkirstymoRezultatas skirstymasGrupes(StudContainer& studis, SkirstymoStrategija strategija, bool irasytiIFailus, bool paprasytiRikiavimo)
{
    auto start = std::chrono::high_resolution_clock::now();

    SkirstymoRezultatas rezultatas;
    if (strategija == SkirstymoStrategija::Pirma)
    {
        rezultatas = skirstymasStrategija1(studis);
    }
    else if(strategija == SkirstymoStrategija::Antra)
    {
        rezultatas = skirstymasStrategija2(studis);
    }
    else
    {
        rezultatas = skirstymasStrategija3(studis);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    timers.skirstymas = duration.count();

    if (!irasytiIFailus)
    {
        timers.isvedimas = 0.0;
        return rezultatas;
    }

    if (paprasytiRikiavimo)
    {
        rikiuotiStudentus(rezultatas.vargsiukai, "vargsiukus");
        rikiuotiStudentus(rezultatas.protai, "kietiakus");
    }

    auto startPrint = std::chrono::high_resolution_clock::now();

    const std::string sufiksas = "_" + aktyvausKonteinerioTrumpasPavadinimas() + "_S" + std::to_string(static_cast<int>(strategija));

    spausdinam(rezultatas.vargsiukai, failoPavadinimas("Vargsiukai" + sufiksas));
    spausdinam(rezultatas.protai, failoPavadinimas("protai" + sufiksas));

    auto endPrint = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationPrint = endPrint - startPrint;
    timers.isvedimas = durationPrint.count();

    std::cout << "Studentai suskirstyti. Vargsiuku: " << rezultatas.vargsiukai.size() << ", kietiaku: " << rezultatas.protai.size() << std::endl;

    return rezultatas;
}

void generuotiFaila()
{
    std::cout << "Iveskite failo pavadinima: ";
    std::string pav;
    std::cin >> pav;

    std::ofstream write(pav);
    if (!write.is_open())
    {
        std::cerr << "Nepavyko sukurti failo." << std::endl;
        return;
    }

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 10);

    std::cout << "Iveskite studentu kieki: ";
    int kiekis;
    std::cin >> kiekis;

    auto start = std::chrono::high_resolution_clock::now();

    const int ndkiek = dist(gen);

    write << std::left << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde";

    for (int j = 0; j < ndkiek; j++)
    {
        write << std::setw(8) << ("ND" + std::to_string(j + 1));
    }

    write << std::setw(8) << "Egz." << '\n';

    for (int i = 0; i < kiekis; i++)
    {
        Stud s;
        s.vard = "Vardas" + std::to_string(i + 1);
        s.pav = "Pavarde" + std::to_string(i + 1);

        write << std::left << std::setw(15) << s.vard
              << std::setw(15) << s.pav;

        s.rez.clear();
        s.vid = 0.0f;

        for (int j = 0; j < ndkiek; j++)
        {
            const int nd = dist(gen);
            s.rez.push_back(nd);
            s.vid += nd;
            write << std::setw(8) << nd;
        }

        if (!s.rez.empty())
        {
            s.vid /= static_cast<float>(s.rez.size());
        }

        s.egrez = dist(gen);
        write << std::setw(8) << s.egrez << '\n';
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    timers.generavimas = duration.count();

    std::cout << "Failas sugeneruotas per " << timers.generavimas << " s." << std::endl;
}
