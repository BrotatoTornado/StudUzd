# Studentu duomenu apdorojimo programa

## v1.0

Ši v1.0 versija parengta is v0.4 bazes ir papildyta taip, kad studentų konteinerio tipas gali būti keičiamas nekeičiant programos logikos tarp:

- `std::vector<Stud>`
- `std::list<Stud>`
- `std::deque<Stud>`

Papildomai realizuotos **2 studentų skirstymo strategijos**:

1. **Strategija 1** - bendras konteineris suskaidomas į du naujus to paties tipo konteinerius:
   - `vargšiukai`
   - `protai`

2. **Strategija 2** - kuriamas tik vienas naujas konteineris:
   - `vargšiukai`

   O iš bendro konteinerio studentai trinami, todel jame po skirstymo lieka tik `protai`.

---

## Kaip keisti konteineri

Visos skirtingos programos su skirtingais konteineriais sukuriamos automatiškai. Kad paleisti, įveskite ".\programa_(konteinerio tipas)".

---

## Programos galimybes

Programa leidžia:

- įvesti studentą ranka
- nuskaityti studentus iš failo
- generuoti pavienius studentus su atsitiktiniais pažymiais
- sugeneruoti visą studentų failą
- surikiuoti studentus
- suskirstyti studentus į `vargšiukus` ir `protus`
- atlikti konteinerių ir strategijų veikimo spartos tyrimą

---

## Rūšiavimas

Visiems konteineriams išlaikyta ta pati logika. Pakeistas tik pats konteinerio tipas.

- `std::vector` ir `std::deque` atveju naudojamas `std::sort`
- `std::list` atveju naudojamas `list::sort`

---

## Projekto struktūra

- `main.cpp`
- `meniu.cpp`
- `skaitymas.cpp`
- `Generavimas.cpp`
- `spausdinam.cpp`
- `tyrimas.cpp`
- `laikai.cpp`
- `studentas.h`
- `konteineris.h`
- `meniu.h`
- `skaitymas.h`
- `Generavimas.h`
- `spausdinam.h`
- `tyrimas.h`
- `laikai.h`
- `Makefile`

---
