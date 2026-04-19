#include "meniu.h"

#include "Generavimas.h"
#include "skaitymas.h"
#include "tyrimas.h"

#include <iostream>
#include <stdexcept>
				 
					

bool vykdytiMeniu(StudContainer& studis)
{
		   

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
            {
                Stud s;
                skaitomRanka(s);
                studis.push_back(s);
                break;
            }
            case 2:
                if (failoSkaitymas(studis))
                {
                    return true;
                }
                break;
            case 3:
            {
                Stud s;
                std::cout << "Iveskite varda: ";
                std::cin >> s.vard;
                std::cout << "Iveskite pavarde: ";
                std::cin >> s.pav;

                parinktiAtsitiktinius(s);

                studis.push_back(s);

                break;
            }
            case 4:
            {
                static int nr = 1;
                Stud s;
                s.vard = "Vardas" + std::to_string(nr);
                s.pav = "Pavarde" + std::to_string(nr);
                nr++;

                parinktiAtsitiktinius(s);

                studis.push_back(s);

                break;
            }
            case 5:
                generuotiFaila();
                break;
            case 6:
                vykdytiTyrima();
                break;
            case 7:
                if (studis.empty())
				 
					
                {
                    std::cout << "Nera sukauptu studentu.\n";
                    break;
                }
                return true;
            case 8:
                return false;
            default:
                std::cout << "Neteisingas pasirinkimas.\n";
                break;
        }
    }
				
}
