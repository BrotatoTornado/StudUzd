#include "Generavimas.h"
#include "studentas.h"
#include "spausdinam.h"
#include "skaitymas.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <algorithm>

bool galimasPavadinimas(std::string pav)
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
        pavadinimas = bazinisPavadinimas + std::to_string(count) + ".txt";
    }

    return pavadinimas;
}

void generuotiFaila()
{
    std::cout << "Įrašykite failo pavadinimą: ";
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

    std::cout << "Įveskite studentų kiekį: ";
    int kiekis;
    std::cin >> kiekis;

    int ndkiek = dist(gen); // kiek ND generuoti

    // spausdiname antraštę
    write << std::left << std::setw(15) << "Vardas"
        << std::setw(15) << "Pavarde";
    for (int j = 0; j < ndkiek; j++)
    {
        write << std::setw(8) << ("ND" + std::to_string(j + 1));
    }
    write << std::setw(8) << "Egz." << std::endl;

    std::vector<Stud> visiStudentai;

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
            int nd = dist(gen);
            s.rez.push_back(nd);
            s.vid += nd;
            write << std::setw(8) << nd;
        }

        if (!s.rez.empty())
        {
            s.vid /= s.rez.size();
        }

        s.egrez = dist(gen);
        write << std::setw(8) << s.egrez << std::endl;

        visiStudentai.push_back(s);
    }

    suskaiciuotiGalutinius(visiStudentai);

    // dabar daliname į vargsus ir protus ir išvedame į failus
    std::vector<Stud> vargsai;
    std::vector<Stud> protai;
    vargsai.reserve(visiStudentai.size());
    protai.reserve(visiStudentai.size());

    for (auto& s : visiStudentai)
    {
        if (s.galrezVid < 5.0f)
        {
            vargsai.push_back(s);
        }
        else
        {
            protai.push_back(s);
        }
    }

    rikiuotiStudentus(vargsai, "vargsus");
    spausdinam(vargsai, failoPavadinimas("Vargsai1"));

    rikiuotiStudentus(protai, "protobokstus");
    spausdinam(protai, failoPavadinimas("Protobokstai1"));

    std::cout << "Failai sugeneruoti" << std::endl;
}
