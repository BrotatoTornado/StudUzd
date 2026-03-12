#include "spausdinam.h"
#include <algorithm>
#include <stdexcept>
#include <chrono>

void rikiuotiStudentus(std::vector<Stud>& studis, const std::string& target)
{
    if (studis.empty())
    {
        return;
    }

    std::cout << "\nPagal ka surusiuoti " + target + "? \n";
    std::cout << "1 - Varda\n2 - Pavarde\n3 - Galutinis (Vid.)\n4 - Galutinis (Med.)\n";

    int p;
    std::cin >> p;
    if (!std::cin || p < 1 || p > 4)
    {
        throw std::runtime_error("Neteisingas pasirinkimas rusiavimo meniu.");
    }

    switch (p)
    {
        case 1:
            std::sort(studis.begin(), studis.end(), [](const Stud& a, const Stud& b) { return a.vard < b.vard; });
            break;
        case 2:
            std::sort(studis.begin(), studis.end(), [](const Stud& a, const Stud& b) { return a.pav < b.pav; });
            break;
        case 3:
            std::sort(studis.begin(), studis.end(), [](const Stud& a, const Stud& b) { return a.galrezVid < b.galrezVid; });
            break;
        case 4:
            std::sort(studis.begin(), studis.end(), [](const Stud& a, const Stud& b) { return a.galrezMed < b.galrezMed; });
            break;
    }
}

void spausdinam(std::vector<Stud>& studis, const std::string& pav)
{
    std::ofstream write(pav);
    if (!write.is_open())
    {
        std::cerr << "Nepavyko atidaryti failo: " << pav << std::endl;
        return;
    }

    write << std::left << std::setw(20) << "Vardas"
        << std::setw(20) << "Pavarde"
        << std::setw(20) << "Galutinis(Vid.)"
        << std::setw(15) << "Galutinis(Med.)" << '\n';

    write << "-------------------------------------------------------\n";

    for (auto& i : studis)
    {
        write << std::left << std::setw(20) << i.vard
            << std::setw(20) << i.pav
            << std::setw(20) << std::fixed << std::setprecision(2) << i.galrezVid
            << std::setw(15) << std::fixed << std::setprecision(2) << i.galrezMed
            << '\n';
    }
}