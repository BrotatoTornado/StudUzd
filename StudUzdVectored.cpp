#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>

struct Stud
{
    std::string vard, pav;
    int egrez;
    std::vector<int> rez;
    float vid = 0.0f;
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

void parinktiAtsitiktinius(Stud& studis)
{
    int kiekND = 1 + rand() % 10;
    studis.rez.clear();
    studis.vid = 0.0f;

    for (int i = 0; i < kiekND; i++)
    {
        int balas = 1 + rand() % 10;
        studis.rez.push_back(balas);
        studis.vid += balas;
    }

    studis.vid /= studis.rez.size();
    studis.egrez = 1 + rand() % 10;
}

void skaitom(Stud &studis)
{
    std::cout << "Iveskite varda" << std::endl;
    std::cin >> studis.vard;
    std::cout << "Iveskite pavarde" << std::endl;
    std::cin >> studis.pav;

    char c;
    std::cout << "Ar naudoti atsitiktinai parinktus n.d. rezultatus?" << std::endl;
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

    while (true)
    {
        Stud s;
        skaitom(s);
        studis.push_back(s);

        char c;
        std::cout << "Ar ivesti dar viena studenta? (y/n): ";
        std::cin >> c;

        if (c != 'y' && c != 'Y')
        {
            break;
        }
    }

    bool kuri;
    std::cout << "Naudoti vidurki ar mediana galutiniam rezultatui?" << std::endl;
    std::cout << "0 - Vidurki\n1 - Mediana" << std::endl;
    std::cin >> kuri;

    if (kuri)
    {
        printf("%-10s%-10s%-15s\n", "Pavarde", "Vardas", "Galutinis (Med.)");

        for (auto i: studis)
        {
            double med = 0.0;
            int n = i.rez.size();

            if (n > 0)
            {
                std::vector<int> temp = i.rez;
                std::sort(temp.begin(), temp.end());

                if (n % 2 == 1)
                {
                    med = temp[n / 2];
                }
                else
                {
                    med = (temp[n / 2] + temp[n / 2 - 1]) / 2.0;
                }
            }

            double galrez = 0.4 * med + 0.6 * i.egrez;
            printf("%-10s%-10s%-10.2lf\n", i.pav.c_str(), i.vard.c_str(), galrez);
        }
    }
    else
    {
        printf("%-10s%-10s%-15s\n", "Pavarde", "Vardas", "Galutinis (Vid.)");

        for (auto i: studis)
        {
            double galrez = 0.4 * i.vid + 0.6 * i.egrez;
            printf("%-10s%-10s%-10.2lf\n", i.pav.c_str(), i.vard.c_str(), galrez);
        }
    }
}