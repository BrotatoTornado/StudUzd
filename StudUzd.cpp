#include <iostream>
#include <iomanip>

struct Stud
{
    std::string vard, pav;
    int kiek, rez[10], egrez;
    float vid = 0;
};

void skaitom(Stud &studis)
{
    std::cout << "Iveskite varda" << std::endl;
    std::cin >> studis.vard;
    std::cout << "Iveskite pavarde" << std::endl;
    std::cin >> studis.pav;
    std::cout << "Iveskite namu darbu kieki" << std::endl;
    std::cin >> studis.kiek;
    std::cout << "Iveskite ju rezultatus" << std::endl;
    for (int i = 0; i < studis.kiek; i++)
    {
        std::cin >> studis.rez[i];
        studis.vid += studis.rez[i];
    }
    studis.vid /= studis.kiek;
    std::cout << "Iveskite egzamino rezultata" << std::endl;
    std::cin >> studis.egrez;
}

int main()
{
    Stud studis;
    float galrez, mediana;
    bool kuri;
    skaitom(studis);
    std::cout << "Naudoti vidurki ar mediana galutiniam rezultatui?" << std::endl;
    std::cout << "0 - Vidurki\n1 - Mediana" << std::endl;
    std::cin >> kuri;
    if (kuri)
    {
        mediana = (studis.kiek % 2 == 0) ? (studis.rez[studis.kiek / 2] + studis.rez[studis.kiek / 2 - 1]) / 2 : studis.rez[studis.kiek / 2];
        printf("%-10s%-10s%-10s\n", "Pavarde", "Vardas", "Galutinis (Med.)");
        galrez = 0.4 * mediana + 0.6 * studis.egrez;
    }
    else
    {
        galrez = 0.4 * studis.vid + 0.6 * studis.egrez;
        printf("%-10s%-10s%-10s\n", "Pavarde", "Vardas", "Galutinis (Vid.)");
    }
    printf("%-10s%-10s%-10lf\n", studis.pav.c_str(), studis.vard.c_str(), galrez);
}
