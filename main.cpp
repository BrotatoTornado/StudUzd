#include "skaitymas.h"
#include "studentas.h"
#include "meniu.h"
#include "spausdinam.h"  // naujas header su spausdinimo ir rusiavimo funkcijomis
#include "laikai.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <limits>

int gautiApdorojimoPasirinkima()
{
    std::cout << "\nKą daryti su gautais studentais?\n";
    std::cout << "1 - Spausdinti visus studentus\n";
    std::cout << "2 - Suskirstyti i vargsiukus ir kietiakus\n";
    std::cout << "3 - Abu veiksmai\n";

    while (true)
    {
        int pasirinkimas;
        std::cin >> pasirinkimas;

        if (!std::cin || pasirinkimas < 1 || pasirinkimas > 3)
        {
            std::cerr << "Neteisinga ivestis. Bandykite is naujo." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        return pasirinkimas;
    }
}


void pradetiSpausdint(const StudContainer& studis)
{
    int faila;
    std::cout << "I konsole ar i faila?\n1 - Konsole\n2 - Faila" << std::endl;

    while (true)
    {
        std::cin >> faila;

        if (!std::cin)
        {
            std::cerr << "Neteisinga ivestis. Bandykite is naujo." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        break;
    }

    if (faila == 1)
    {
        std::cout << std::left << std::setw(20) << "Vardas"
                  << std::setw(20) << "Pavarde"
                  << std::setw(20) << "Galutinis(Vid.)"
                  << std::setw(15) << "Galutinis(Med.)" << '\n';
        std::cout << "-------------------------------------------------------\n";

        for (const auto& i : studis)
        {
            std::cout << std::left << std::setw(20) << i.vard
                      << std::setw(20) << i.pav
                      << std::setw(20) << std::fixed << std::setprecision(2) << i.galrezVid
                      << std::setw(15) << std::fixed << std::setprecision(2) << i.galrezMed
                      << '\n';
        }
    }
    else if (faila == 2)
    {
        std::string pav;
        std::cout << "Iveskite pavadinima:" << std::endl;

        while (true)
        {
            std::cin >> pav;

            if (!std::cin)
            {
                std::cerr << "Neteisinga ivestis. Bandykite is naujo." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            break;
        }

        spausdinam(studis, pav);
    }
    else
    {
        std::cout << "Neteisingas pasirinkimas." << std::endl;
    }
}

void laikoRez(double progTrukme)
{
    std::cout << "Failo skaitymas: " << timers.skaitymas << std::endl;
    std::cout << "Studentų suskirstymas: " << timers.rusiavimas << std::endl;
    std::cout << "Failų išvedimas: " << timers.isvedimas << std::endl;
    std::cout << "Visos programos trukmė: " << progTrukme << std::endl;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    try
    {
        while (true)
        {
            std::vector<Stud> studis;

            if (!vykdytiMeniu(studis))
            {
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;

                laikoRez(duration.count());
                return 0;
            }

            if (studis.empty())
            {
                std::cout << "Nera ivestu studentu.\n";
                char grz;
                std::cout << "Grįžti į pradžią? (y/n): ";
                std::cin >> grz;
                if (!std::cin)
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                if (grz == 'y' || grz == 'Y')
                {
                    continue;
                }
                else
                {
                    break;
                }
            }

            if (studis.size() > 0)
            {
                suskaiciuotiGalutinius(studis);

                rikiuotiStudentus(studis, "studentus");
                pradetiSpausdint(studis);
            }

            char gr;
            // po spausdinimo paklausti, ar grįžti į pradžią
            std::cout << "Grįžti į pradžią? (y/n): ";
            std::cin >> gr;
            if (!std::cin)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            if (gr == 'y' || gr == 'Y')
            {
                continue;
            }
            else
            {
                break;
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Klaida: " << e.what() << std::endl;
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    laikoRez(duration.count());
    return 0;
}
