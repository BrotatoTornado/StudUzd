#include "skaitymas.h"
#include "laikai.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>

void dinamuojamPazymius(Stud& studis)
{
    std::cout << "Iveskite namu darbu pazymius. Irasykite 0 kai baigete." << std::endl;

    studis.rez.clear();
    studis.vid = 0.0f;

    while (true)
    {
        int x;
        std::cin >> x;

        if (!std::cin)
        {
            throw std::runtime_error("Kazkas ne taip su cin");
        }

        if (x <= 0)
        {
            break;
        }

        if (x > 10)
        {
            std::cout << "Netinkamas skaicius. Iveskite tarp 1 ir 10" << std::endl;
            continue;
        }

        studis.rez.push_back(x);
        studis.vid += x;
    }

    if (!studis.rez.empty())
    {
        studis.vid /= static_cast<float>(studis.rez.size());
    }
    else
    {
        throw std::runtime_error("Kur pazymiai??");
    }
}

bool failoSkaitymas(StudContainer& studis)
{
    std::cout << "Iveskite failo pavadinima:" << std::endl;
    std::string pav;
    std::cin >> pav;
    return failoSkaitymas(studis, pav);
}

bool failoSkaitymas(StudContainer& studis, const std::string& pav)
{
    auto start = std::chrono::high_resolution_clock::now();

    try
    {
        std::ifstream read(pav);

        if (!read.is_open())
        {
            throw std::runtime_error("Neatidarem failo. Patikrinkite pavadinima.");
        }

        std::string line;
        std::getline(read, line);

        while (std::getline(read, line))
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

            for (const auto& pazymys : s.rez)
            {
                s.vid += pazymys;
            }

            if (!s.rez.empty())
            {
                s.vid /= static_cast<float>(s.rez.size());
            }

            studis.push_back(s);
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        timers.skaitymas = duration.count();

        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Klaida skaitant faila: " << e.what() << std::endl;
        return false;
    }
}

void suskaiciuotiGalutinius(StudContainer& studis)
{
    for (auto& i : studis)
    {
        std::sort(i.rez.begin(), i.rez.end());

        float med = 0.0f;
        const int n = static_cast<int>(i.rez.size());

        if (n == 0)
        {
            i.galrezMed = 0.0f;
            i.galrezVid = 0.0f;
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
}

void parinktiAtsitiktinius(Stud& studis)
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(1, 10);

    const int kiekND = dist(gen);

    studis.rez.clear();
    studis.vid = 0.0f;

    for (int i = 0; i < kiekND; i++)
    {
        const int balas = dist(gen);
        studis.rez.push_back(balas);
        studis.vid += balas;
    }

    studis.vid /= static_cast<float>(studis.rez.size());
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
