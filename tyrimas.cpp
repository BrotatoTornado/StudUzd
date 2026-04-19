#include "tyrimas.h"

#include "Generavimas.h"
#include "konteineris.h"
#include "laikai.h"
#include "skaitymas.h"
#include "spausdinam.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct TyrimoIrasas
{
    std::string failas;
    std::size_t irasuKiekis = 0;
    double skaitymas = 0.0;
    double rusiavimas = 0.0;
    double skirstymas = 0.0;
};

namespace
{
bool failasEgzistuoja(const std::string& pav)
{
    std::ifstream f(pav);
    return f.good();
}

TyrimoIrasas atliktiBandymuSerija(const std::string& failas, SkirstymoStrategija strategija, int kartojimai)
{
    TyrimoIrasas vidurkiai;
    vidurkiai.failas = failas;

    for (int i = 0; i < kartojimai; i++)
    {
        nunulintiLaikus();

        StudContainer studis;
        if (!failoSkaitymas(studis, failas))
        {
            return {};
        }

        suskaiciuotiGalutinius(studis);
        vidurkiai.irasuKiekis = studis.size();

        surikiuotiPagalGalutiniVid(studis);
        skirstymasGrupes(studis, strategija, false, false);

        vidurkiai.skaitymas += timers.skaitymas;
        vidurkiai.rusiavimas += timers.rusiavimas;
        vidurkiai.skirstymas += timers.skirstymas;
    }

    vidurkiai.skaitymas /= kartojimai;
    vidurkiai.rusiavimas /= kartojimai;
    vidurkiai.skirstymas /= kartojimai;

    return vidurkiai;
}

void spausdintiLentele(const std::vector<TyrimoIrasas>& rezultatai)
{
    std::cout << '\n';
    std::cout << std::left << std::setw(22) << "Failas" << std::setw(16) << "Irasu kiekis" << std::setw(16) << "Skaitymas (s)" << std::setw(18) << "Rusiavimas (s)" << std::setw(18) << "Skirstymas (s)" << "Is viso (s)" << '\n';

    std::cout << std::string(90, '-') << '\n';

    for (const auto& rez : rezultatai)
    {
        std::cout << std::left << std::setw(22) << rez.failas << std::setw(16) << rez.irasuKiekis << std::setw(16) << std::fixed << std::setprecision(6) << rez.skaitymas << std::setw(18) << std::fixed << std::setprecision(6) << rez.rusiavimas << std::setw(18) << std::fixed << std::setprecision(6) << rez.skirstymas << '\n';
    }
}

//spausdinam i faila readme formatu, kad butu lengviau ikelti
void iREADME(const std::vector<TyrimoIrasas>& rezultatai, SkirstymoStrategija strategija)
{
    const std::string pav = "benchmark_" + aktyvausKonteinerioTrumpasPavadinimas()
        + "_S" + std::to_string(static_cast<int>(strategija)) + ".md";

    std::ofstream write(pav);
    if (!write.is_open())
    {
        return;
    }

    write << "# " << aktyvausKonteinerioPavadinimas() << " - strategija "
        << static_cast<int>(strategija) << "\n\n";
    write << "| Failas | Irasu kiekis | Skaitymas (s) | Rusiavimas (s) | Skirstymas (s) |\n";
    write << "|---|---:|---:|---:|---:|\n";

    for (auto& rez : rezultatai)
    {
        double isViso = rez.skaitymas + rez.rusiavimas + rez.skirstymas;
        write << "| " << rez.failas << " | " << rez.irasuKiekis << " | " << std::fixed << std::setprecision(6) << rez.skaitymas << " | " << std::fixed << std::setprecision(6) << rez.rusiavimas << " | " << std::fixed << std::setprecision(6) << rez.skirstymas << " | " << std::fixed << std::setprecision(6) << isViso << " |\n";
    }

    std::cout << "Rezultatu lentele issaugota i faila: " << pav << std::endl;
}

std::vector<std::string> sudarytiNumatytujuFailuSarasa(const std::string& prefiksas)
{
    return {
        prefiksas + "1000.txt",
        prefiksas + "10000.txt",
        prefiksas + "100000.txt",
        prefiksas + "1000000.txt",
        prefiksas + "10000000.txt"
    };
}
}

void vykdytiTyrima()
{
    std::cout << "\nAktyvus studentu konteineris: " << aktyvausKonteinerioPavadinimas() << '\n';

    const SkirstymoStrategija strategija = pasirinktiStrategija();

    std::cout << "Kiek kartu kartoti kiekviena testa? ";
    int kartojimai;
    std::cin >> kartojimai;

    if (!std::cin || kartojimai < 1)
    {
        throw std::runtime_error("Neteisingas kartojimu skaicius.");
    }

    std::cout << "\n1 - Testuoti viena faila\n";
    std::cout << "2 - Testuoti numatytuosius failus pagal prefiksa (pvz. studentai1000.txt ir t.t.)\n";

    int pasirinkimas;
    std::cin >> pasirinkimas;

    if (!std::cin || pasirinkimas < 1 || pasirinkimas > 2)
    {
        throw std::runtime_error("Neteisingas tyrimo meniu pasirinkimas.");
    }

    std::vector<std::string> failai;
    if (pasirinkimas == 1)
    {
        std::cout << "Iveskite pilna failo pavadinima: ";
        std::string failas;
        std::cin >> failas;
        failai.push_back(failas);
    }
    else
    {
        std::cout << "Iveskite failu prefiksa be dydzio ir .txt (pvz. studentai): ";
        std::string prefiksas;
        std::cin >> prefiksas;
        failai = sudarytiNumatytujuFailuSarasa(prefiksas);
    }

    std::vector<TyrimoIrasas> rezultatai;
    for (const auto& failas : failai)
    {
        if (!failasEgzistuoja(failas))
        {
            std::cout << "Failas nerastas, praleidziamas: " << failas << std::endl;
            continue;
        }

        auto rez = atliktiBandymuSerija(failas, strategija, kartojimai);
        if (rez.irasuKiekis != 0)
        {
            rezultatai.push_back(rez);
        }
    }

    if (rezultatai.empty())
    {
        std::cout << "Tyrimui tinkamu failu nerasta." << std::endl;
        return;
    }

    spausdintiLentele(rezultatai);
    iREADME(rezultatai, strategija);
}
