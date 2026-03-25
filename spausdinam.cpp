#include "spausdinam.h"
#include "laikai.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

void surikiuotiStudentus(StudContainer& studis, int pasirinkimas)
{
    if (studis.empty())
    {
        timers.rusiavimas = 0.0;
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();

    switch (pasirinkimas)
    {
        case 1:
            konteinerioSort(studis, [](const Stud& a, const Stud& b) { return a.vard < b.vard; });
            break;
        case 2:
            konteinerioSort(studis, [](const Stud& a, const Stud& b) { return a.pav < b.pav; });
            break;
        case 3:
            konteinerioSort(studis, [](const Stud& a, const Stud& b) { return a.galrezVid < b.galrezVid; });
            break;
        case 4:
            konteinerioSort(studis, [](const Stud& a, const Stud& b) { return a.galrezMed < b.galrezMed; });
            break;
        default:
            throw std::runtime_error("Neteisingas pasirinkimas rusiavimo meniu.");
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    timers.rusiavimas = duration.count();
}

void surikiuotiPagalGalutiniVid(StudContainer& studis)
{
    surikiuotiStudentus(studis, 3);
}

void rikiuotiStudentus(StudContainer& studis, const std::string& target)
{
    if (studis.empty())
    {
        return;
    }

    std::cout << "\nPagal ka surikiuoti " << target << "?\n";
    std::cout << "1 - Varda\n2 - Pavarde\n3 - Galutinis (Vid.)\n4 - Galutinis (Med.)\n";

    int p;
    std::cin >> p;

    if (!std::cin || p < 1 || p > 4)
    {
        throw std::runtime_error("Neteisingas pasirinkimas rusiavimo meniu.");
    }

    surikiuotiStudentus(studis, p);
}

void spausdinam(const StudContainer& studis, const std::string& pav)
{
    std::ofstream write(pav);

    if (!write.is_open())
    {
        std::cerr << "Nepavyko atidaryti failo: " << pav << std::endl;
        return;
    }

    write << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde" << std::setw(20) << "Galutinis(Vid.)" << std::setw(15) << "Galutinis(Med.)" << '\n';

    write << "-------------------------------------------------------\n";

    for (const auto& i : studis)
    {
        write << std::left << std::setw(20) << i.vard << std::setw(20) << i.pav << std::setw(20) << std::fixed << std::setprecision(2) << i.galrezVid << std::setw(15) << std::fixed << std::setprecision(2) << i.galrezMed << '\n';
    }
}
