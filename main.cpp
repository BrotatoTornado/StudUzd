#include "skaitymas.h"
#include "studentas.h"
#include "meniu.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <limits> // for numeric_limits

void rikiuotiStudentus(std::vector<Stud>& studis, std::string target)
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

void spausdinam(std::vector<Stud>& studis, std::string pav)
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

void vargsuSkirstymas(std::vector<Stud>& studis)
{
    std::vector<Stud> vargsai;
    std::vector<Stud> protai;
    vargsai.reserve(studis.size());
    protai.reserve(studis.size());

    for (auto& i : studis)
    {
        if (i.galrezVid < 5.0)
        {
            vargsai.push_back(i);
        }
        else
        {
            protai.push_back(i);
        }
    }

    rikiuotiStudentus(vargsai, "vargsus");
    spausdinam(vargsai, "Vargsai.txt");

    rikiuotiStudentus(protai, "protobokstus");
    spausdinam(protai, "Protobokstai.txt");
}

void pradetiSpausdint(std::vector<Stud>& studis)
{
    int faila;
    std::cout << "Į konsolę ar failą?\n1 - Konsolę\n2 - Failą" << std::endl;
    while (true)
    {
        std::cin >> faila;
        if (!std::cin)
        {
            std::cerr << "Neteisinga įvestis. Bandykite iš naujo." << std::endl;
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
        for (auto& i : studis)
        {
            std::cout << std::left << std::setw(20) << i.vard
                << std::setw(20) << i.pav
                << std::setw(20) << std::fixed << std::setprecision(2) << i.galrezVid
                << std::setw(15) << std::fixed << std::setprecision(2) << i.galrezMed
                << '\n';
        }
    }
    else
    {
        std::string pav;
        std::cout << "Įveskite pavadinimą:" << std::endl;
        while (true)
        {
            std::cin >> pav;
            if (!std::cin)
            {
                std::cerr << "Neteisinga įvestis. Bandykite iš naujo." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            break;
        }

        spausdinam(studis, pav);
    }
}

int main()
{
    try
    {
        while (true)
        {
            std::vector<Stud> studis;

            vykdytiMeniu(studis);

            if (studis.empty())
            {
                std::cout << "Nera ivestu studentu.\n";
                char grz;
                std::cout << "Grįžti į pradžią? (y/n): ";
                std::cin >> grz;
                if (!std::cin) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); }
                if (grz == 'y' || grz == 'Y') continue;
                else break;
            }

            for (auto& i : studis)
            {
                std::sort(i.rez.begin(), i.rez.end());

                float med = 0.0f;
                int n = static_cast<int>(i.rez.size());

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

            std::cout << "Ar suskirstyti i vargsus ir protobokstus?(y/n)" << std::endl;
            char yn;
            while (true)
            {
                std::cin >> yn;
                if (!std::cin)
                {
                    std::cerr << "Neteisinga įvestis. Bandykite iš naujo." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                break;
            }

            if (yn == 'y' || yn == 'Y')
            {
                vargsuSkirstymas(studis);

                // po spausdinimo paklausti, ar grįžti į pradžią
                char gr;
                std::cout << "Grįžti į pradžią? (y/n): ";
                std::cin >> gr;
                if (!std::cin) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); }
                if (gr == 'y' || gr == 'Y') continue;
                else break;
            }

            rikiuotiStudentus(studis, "studentus");

            pradetiSpausdint(studis);

            // po spausdinimo paklausti, ar grįžti į pradžią
            char gr;
            std::cout << "Grįžti į pradžią? (y/n): ";
            std::cin >> gr;
            if (!std::cin) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); }
            if (gr == 'y' || gr == 'Y') continue;
            else break;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Klaida: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
