#include <iostream>

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
    float galrez;
    skaitom(studis);
    galrez = 0.4 * studis.vid + 0.6 * studis.egrez;
    printf("%-10s%-10s%-10s\n", "Pavarde", "Vardas", "Galutinis (Vid.)");
    printf("%-10s%-10s%-10lf\n", studis.pav.c_str(), studis.vard.c_str(), galrez);
}
