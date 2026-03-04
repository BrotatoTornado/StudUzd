#include "skaitymas.h"
#include "studentas.h"
#include "meniu.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <stdexcept>

void rikiuotiStudentus(std::vector<Stud>& studis)
{
    if (studis.empty())
    {
        return;
    }

    std::cout << "\nPagal ka surusiuoti studentus?\n";
    std::cout << "1 - Varda\n2 - Pavarde\n3 - Galutinis (Vid.)\n4 - Galutinis (Med.)\n";

    int p;
    std::cin >> p;

    if (!std::cin || p < 1 || p > 4)
        throw std::runtime_error("Neteisingas pasirinkimas rusiavimo meniu.");

    switch (p)
    {
        case 1:
            std::sort(studis.begin(), studis.end(),
                [](const Stud& a, const Stud& b) { return a.vard < b.vard; });
            break;
        case 2:
            std::sort(studis.begin(), studis.end(),
                [](const Stud& a, const Stud& b) { return a.pav < b.pav; });
            break;
        case 3:
            std::sort(studis.begin(), studis.end(),
                [](const Stud& a, const Stud& b) { return a.galrezVid < b.galrezVid; });
            break;
        case 4:
            std::sort(studis.begin(), studis.end(),
                [](const Stud& a, const Stud& b) { return a.galrezMed < b.galrezMed; });
            break;
    }
}


int main()
{
    try
    {
        std::vector<Stud> studis;
        auto start = std::chrono::high_resolution_clock::now();

        vykdytiMeniu(studis);

        if (studis.empty())
        {
            std::cout << "Nera ivestu studentu.\n";
            return 0;
        }

        for (auto& i : studis)
        {
            std::sort(i.rez.begin(), i.rez.end());

            float med = 0.0f;
            int n = i.rez.size();

            if (n == 0)
            {
                i.galrezMed = 0;
                i.galrezVid = 0;
                continue;
            }

            if (n % 2 == 1)
                med = i.rez[n / 2];
            else
                med = (i.rez[n / 2] + i.rez[n / 2 - 1]) / 2.0f;

            i.galrezMed = 0.4f * med + 0.6f * i.egrez;
            i.galrezVid = 0.4f * i.vid + 0.6f * i.egrez;
        }

        rikiuotiStudentus(studis);

        std::cout << std::left << std::setw(20) << "Vardas"
            << std::setw(20) << "Pavarde"
            << std::setw(20) << "Galutinis(Vid.)"
            << std::setw(15) << "Galutinis(Med.)" << '\n';
        std::cout << "-------------------------------------------------------\n";
        for (auto& i : studis)
        {
            std::cout << std::left << std::setw(20) << i.vard << std::setw(20) << i.pav << std::setw(20) << std::fixed << std::setprecision(2) << i.galrezVid << std::setw(15) << std::fixed << std::setprecision(2) << i.galrezMed << '\n';
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Programa veike: " << elapsed.count() << " sekundziu\n";

    }
    catch (const std::exception& e)
    {
        std::cerr << "Klaida: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
