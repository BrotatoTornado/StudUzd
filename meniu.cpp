#include "meniu.h"
#include "skaitymas.h"
#include "Generavimas.h"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>

bool vykdytiMeniu(std::vector<Stud>& studis)
{
    Stud s;

    while (true)
    {
        std::cout << "\nPasirinkite programos eiga:\n";
        std::cout << "1 - Ivesti studenta ranka\n";
        std::cout << "2 - Skaityti is failo ir iskart apdoroti\n";
        std::cout << "3 - Prideti studenta su atsitiktiniais pazymiais\n";
        std::cout << "4 - Prideti sugeneruota studenta (vardas/pavarde/pazymiai)\n";
        std::cout << "5 - Sugeneruoti studentu faila\n";
        std::cout << "6 - Atlikti konteineriu ir strategiju tyrima\n";
        std::cout << "7 - Apdoroti sukauptus studentus\n";
        std::cout << "8 - Baigti darba\n";

        int pasirinkimas;
        std::cin >> pasirinkimas;

        if (!std::cin)
        {
            throw std::runtime_error("Bloga ivestis.");
        }

        switch (pasirinkimas)
        {
            case 1:
                skaitomRanka(s);
                studis.push_back(s);
                break;
            case 2:
                failoSkaitymas(studis);
                //studis.push_back(s);
                break;
            case 3:
                std::cout << "Iveskite varda: ";
                std::cin >> s.vard;
                std::cout << "Iveskite pavarde: ";
                std::cin >> s.pav;

                parinktiAtsitiktinius(s);

                studis.push_back(s);

                break;
            case 4:
                static int nr = 1;
                s.vard = "Vardas" + std::to_string(nr);
                s.pav = "Pavarde" + std::to_string(nr);
                nr++;

                parinktiAtsitiktinius(s);

                studis.push_back(s);

                break;
            case 5:
                generuotiFaila();
                char gr;
                std::cout << "Grįžti į pradžią? (y/n): ";
                std::cin >> gr;
                if (gr == 'y' || gr == 'Y')
                {
                    continue;
                }
                else
                {
                    return false;
                }
            case 6:
                return false;
            default:
                std::cout << "Neteisingas pasirinkimas.\n";
                continue;
        }
    }
    return true;
}
