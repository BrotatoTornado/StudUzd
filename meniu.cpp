#include "meniu.h"
#include "skaitymas.h"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>


void vykdytiMeniu(std::vector<Stud>& studis)
{
    Stud s;

    while (true)
    {
        std::cout << "\nPasirinkite programos eiga:\n";
        std::cout << "1 - Ivesti studenta ranka\n";
        std::cout << "2 - Skaityti is failo\n";
        std::cout << "3 - Generuoti tik pazymius\n";
        std::cout << "4 - Generuoti vardus, pavardes ir pazymius\n";
        std::cout << "5 - Baigti darba\n";

        int pasirinkimas;
        std::cin >> pasirinkimas;

        if (!std::cin)
        {
            throw std::runtime_error("Bloga ivestis.");
        }

        if (pasirinkimas == 5)
        {
            break;
        }

        if (pasirinkimas == 1)
        {
            skaitomRanka(s);
        }
        else if (pasirinkimas == 2)
        {
            failoSkaitymas(studis);
        }
        else if (pasirinkimas == 3)
        {
            std::cout << "Iveskite varda: ";
            std::cin >> s.vard;
            std::cout << "Iveskite pavarde: ";
            std::cin >> s.pav;

            parinktiAtsitiktinius(s);
        }
        else if (pasirinkimas == 4)
        {
            static int nr = 1;
            s.vard = "Vardas" + std::to_string(nr);
            s.pav = "Pavarde" + std::to_string(nr);
            nr++;

            parinktiAtsitiktinius(s);
        }
        else
        {
            std::cout << "Neteisingas pasirinkimas.\n";
            continue;
        }

        studis.push_back(s);
    }
}
