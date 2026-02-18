#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

struct Stud
{
    std::string vard, pav;
    int kiek = 0, egrez;
    int* rez;
    float vid = 0.0f;
};

void dinamuojamPazymius(Stud &studis)
{
    int dydis = 2;
    int tempDydis = 0;
    studis.rez = new int[dydis];

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

        if (tempDydis > dydis)
        {
            int naujasDydis = dydis + 1;
            int* tempMas = new int[naujasDydis];
            for (int i = 0; i < tempDydis; i++)
            {
                tempMas[i] = studis.rez[i];
            }
            delete[] studis.rez;
            studis.rez = tempMas;
            dydis = naujasDydis;
        }

        studis.rez[tempDydis] = x;
        tempDydis++;
        studis.vid += x;
    }

    studis.kiek = tempDydis;
    if (studis.kiek > 0)
    {
        studis.vid /= studis.kiek;
    }
    else
    {
        std::cerr << "Kaip suprast nera studentu?"; std::exit(1);
    }
}

void parinktiAtsitiktinius(Stud& studis)
{
    int kiekND = 1 + rand() % 10;
    studis.rez = new int[kiekND];
    studis.vid = 0.0f;
    studis.kiek = kiekND;

    for (int i = 0; i < kiekND; i++)
    {
        int balas = 1 + rand() % 10;
        studis.rez[i] = balas;
        studis.vid += balas;
    }

    studis.vid /= studis.kiek;
    studis.egrez = 1 + rand() % 10;
}

void skaitom(Stud& studis)
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
    int studDydis = 2;
    Stud* studis = new Stud[studDydis];
    int tempKiekis = 0;


    while (true)
    {
        if (tempKiekis > studDydis)
        {
            int temp = studDydis + 1;
            Stud* tmp = new Stud[temp];
            for (int i = 0; i < tempKiekis; ++i) tmp[i] = studis[i];
            delete[] studis;
            studis = tmp;
            studDydis = temp;
        }

        skaitom(studis[tempKiekis]);

        tempKiekis++;

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
        for (int i = 0; i < tempKiekis; i++)
        {
            double med = 0.0;
            int n = studis[i].kiek;
            if (n > 0)
            {
                int* temp = new int[n];
                for (int j = 0; j < n; ++j)
                {
                    temp[j] = studis[i].rez[j];
                }
                std::sort(temp, temp + n);
                if (n % 2 == 1)
                {
                    med = temp[n / 2];
                }
                else
                {
                    med = (temp[n / 2] + temp[n / 2 - 1]) / 2;
                }
                delete[] temp;
            }
            double galrez = 0.4 * med + 0.6 * studis[i].egrez;
            printf("%-10s%-10s%-10.2lf\n", studis[i].pav.c_str(), studis[i].vard.c_str(), galrez);
        }
    }
    else
    {
        printf("%-10s%-10s%-15s\n", "Pavarde", "Vardas", "Galutinis (Vid.)");
        for (int i = 0; i < tempKiekis; i++)
        {
            double galrez = 0.4 * studis[i].vid + 0.6 * studis[i].egrez;
            printf("%-10s%-10s%-10.2lf\n", studis[i].pav.c_str(), studis[i].vard.c_str(), galrez);
        }
    }

    // delete atminti lol
    for (int i = 0; i < tempKiekis; i++)
    {
        delete[] studis[i].rez;
    }
    delete[] studis;
}