#include <algorithm>
#include <chrono>
#include <clocale>
#include <cwchar>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <wchar.h>
#include <cstdlib>
#include <windows.h>
#include <chrono>

struct Stud
{
    std::string vard, pav;
    int egrez;
    std::vector<int> rez;
    float vid = 0.0f, galrezMed = 0.0, galrezVid = 0.0;
};

void dinamuojamPazymius(Stud& studis)
{
    std::cout << "Iveskite namu darbu pazymius. Irasykite 0 kai baigete." << std::endl;

    while (true)
    {
        int x;
        std::cin >> x;

        if (!std::cin)
        {
            std::cerr << "Kazkas ne taip su cin";
            std::exit(1);
        }

        if (x <= 0)
        {
            break;
        }
        else if (x > 10)
        {
            std::cout << "Netinkamas skaicius. Iveskite tarp 1 ir 10" << std::endl;
            continue;
        }

        studis.rez.push_back(x);
        studis.vid += x;
    }

    if (!studis.rez.empty())
    {
        studis.vid /= studis.rez.size();
    }
    else
    {
        std::cerr << "Kur pazymiai??";
        std::exit(1);
    }
}

void failoSkaitymas(std::vector<Stud>& studis)
{
    std::cout << "Įveskite failo pavadinimą:" << std::endl;
    std::string pav;
    std::cin >> pav;

    std::ifstream read(pav);

    if (!read.is_open())
    {
        std::cerr << "Neatidarem failo. Patikrinkite pavadinimą.";
        std::exit(1);
    }

    std::string line;

    while (getline(read, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::istringstream ss(line);
        Stud s;

        ss >> s.vard >> s.pav;

        int x;

        while (ss >> x)
        {
            s.rez.push_back(x);
        }

        if (s.rez.empty())
        {
            continue;
        }

        s.egrez = s.rez.back();
        s.rez.pop_back();

        for (auto i : s.rez)
        {
            s.vid += i;
        }

        if (!s.rez.empty())
        {
            s.vid /= static_cast<float>(s.rez.size());
        }

        studis.push_back(s);
    }
}

void parinktiAtsitiktinius(Stud& studis)
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(1, 10);
    int kiekND = dist(gen);
    studis.rez.clear();
    studis.vid = 0.0f;

    for (int i = 0; i < kiekND; i++)
    {
        int balas = dist(gen);
        studis.rez.push_back(balas);
        studis.vid += balas;
    }

    studis.vid /= studis.rez.size();
    studis.egrez = dist(gen);
}

void skaitomRanka(Stud& studis)
{
    std::cout << "Iveskite varda" << std::endl;
    std::cin >> studis.vard;
    std::cout << "Iveskite pavarde" << std::endl;
    std::cin >> studis.pav;

    char c;
    std::cout << "Ar naudoti atsitiktinai parinktus n.d. rezultatus? (y/n)" << std::endl;
    std::cin >> c;

    if (c != 'n' && c != 'N')
    {
        parinktiAtsitiktinius(studis);
    }
    else
    {
        dinamuojamPazymius(studis);
        std::cout << "Iveskite egzamino rezultata" << std::endl;
        std::cin >> studis.egrez;
    }
}

int main()
{
    std::vector<Stud> studis;
    Stud s;

    std::cout << "Pasirinkite, ar norite:\nĮrašyti ranka - 0\nSkaityti iš failo - 1" << std::endl;
    bool c;
    std::cin >> c;

    auto start = std::chrono::high_resolution_clock::now();
    if (c)
    {
        failoSkaitymas(studis);
    }
    else
    {
        while (true)
        {
            skaitomRanka(s);
            studis.push_back(s);

            char c;
            std::cout << "Ar ivesti dar viena studenta? (y/n): ";
            std::cin >> c;

            if (c != 'y' && c != 'Y')
            {
                break;
            }
        }
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
        {
            med = i.rez[n / 2];
        }
        else
        {
            med = (i.rez[n / 2] + i.rez[n / 2 - 1]) / 2.0f;
        }

        i.galrezMed = 0.4f * med + 0.6f * i.egrez;
        i.galrezVid = 0.4f * i.vid + 0.6f * i.egrez;
    }

    std::cout << "Pagal ką surūšiuoti?\n1 - Vardą\n2 - Pavardę\n3 - Galutinis (Vid.)\n4 - Galutinis (Med.)" << std::endl;
    int p;
    while (true)
    {
        std::cin >> p;

        if (!std::cin || p < 1 || p > 4)
        {
            std::cout << "Įveskite skaičių nuo 1 iki 4" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
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
        break;
    }

    std::cout << "Rezultatą išvesti į:\n0 - Konsolę\n1 - Failą" << std::endl;
    bool ifaila;
    std::cin >> ifaila;

    if (ifaila)
    {
        std::cout << "Įveskite failo pavadinimą:" << std::endl;
        std::string failopav;
        std::cin >> failopav;

        std::ofstream write(failopav);

        if (!write.is_open())
        {
            std::cerr << "Nepavyko sukurti failo!" << std::endl;
            return 1;
        }

        write << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde" << std::setw(15) << "Galutinis(Vid.)" << std::setw(15) << "Galutinis(Med.)" << std::endl;

        for (auto& i : studis)
        {
            write << std::left << std::setw(20) << i.vard << std::setw(20) << i.pav << std::setw(15) << std::fixed << std::setprecision(2) << i.galrezVid << std::setw(15) << std::fixed << std::setprecision(2) << i.galrezMed << std::endl;
        }
    }
    else
    {
        printf("%-20s%-20s%-20.2s%-15.2s\n", "Vardas", "Pavarde", "Galutinis(Vid.)", "Galutinis(Med.)");
        printf("-------------------------------------------------------\n");
        for (auto& i : studis)
        {
            printf("%-20s%-20s%-20.2f%-15.2f\n", i.vard.c_str(), i.pav.c_str(), i.galrezVid, i.galrezMed);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Programa veikė: " << elapsed.count() << " sekundžių\n";
}
