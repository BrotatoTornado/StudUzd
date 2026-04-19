# Studentų duomenų apdorojimo programa v1.0

## Projekto aprašymas

Ši v1.0 versija sukurta remiantis v0.4 baze ir papildyta taip, kad studentų konteinerio tipas gali būti keičiamas nekeičiant programos logikos, naudojant:

- std::vector<Stud>
- std::list<Stud>
- std::deque<Stud>

Programa leidžia atlikti studentų duomenų apdorojimą, analizę bei konteinerių ir algoritmų veikimo spartos tyrimą.

---

## Programos galimybės

Programa leidžia:

- įvesti studentus rankiniu būdu
- nuskaityti studentus iš failo
- generuoti studentus su atsitiktiniais pažymiais
- sugeneruoti pilnus studentų failus
- rūšiuoti studentus
- skirstyti studentus į dvi kategorijas:
  - vargšiukai
  - protai
- atlikti konteinerių ir strategijų veikimo spartos tyrimą

---

## Konteineriai

Programa palaiko tris konteinerių tipus:

- std::vector
- std::list
- std::deque

Konteinerio tipas keičiamas kompiliavimo metu.

---

## Konteinerio paleidimas

Sukompiliavus programą, galima paleisti atskiras versijas:

- programa_vector
- programa_list
- programa_deque

---

## Studentų skirstymo strategijos

### Strategija 1

Bendras konteineris skaidomas į du naujus konteinerius:

- vargšiukai
- protai

---

### Strategija 2

Kuriamas tik vienas naujas konteineris:

- vargšiukai

Studentai, kurie yra vargšiukai, perkeliami į naują konteinerį ir pašalinami iš bendro konteinerio. Likę studentai laikomi protai.

---

### Strategija 3 (optimizuota)

Naudojamas std::stable_partition algoritmas.

Skirstymas atliekamas vienu perėjimu per duomenis, minimaliai kopijuojant elementus.

---

## Efektyvumo tyrimas

Atliekamas programos veikimo spartos palyginimas tarp:

- konteinerių tipų (vector, list, deque)
- skirtingų skirstymo strategijų

Matuojami etapai:

- duomenų nuskaitymas
- rūšiavimas
- skirstymas į grupes

---

## Testavimo duomenys

Testai atliekami su šiais failų dydžiais:

- 1000 įrašų
- 10000 įrašų
- 100000 įrašų
- 1000000 įrašų
- 10000000 įrašų

Pačius failus galima rasti repozitorijoje.

---

## Testavimo rezultatai

### Vector

| Failas | Irasu kiekis | Skaitymas (s) | Rusiavimas (s) | Skirstymas (s) |
|---|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.001248 | 0.000110 | 0.000124 |
| studentai10000.txt | 10000 | 0.020431 | 0.000955 | 0.001172 |
| studentai100000.txt | 100000 | 0.248936 | 0.011622 | 0.013477 |
| studentai1000000.txt | 1000000 | 1.250284 | 0.144832 | 0.126277 |
| studentai10000000.txt | 10000000 | 6.825194 | 1.810164 | 1.103925 |

---

## Išvados

- std::vector yra greičiausias dėl geros atminties lokalizacijos.
- std::list yra lėčiausias dėl pointer-based struktūros ir prasto cache panaudojimo.
- std::deque yra kompromisinis variantas tarp vector ir list.

Strategijų palyginimas:

- Strategija 1: paprasta, bet naudoja daugiau atminties.
- Strategija 2: efektyvesnė atminties atžvilgiu, tačiau lėtesnė dėl trynimų.
- Strategija 3: greičiausia, nes naudoja STL algoritmus ir vieną duomenų perėjimą.

---

## Sistemos parametrai

CPU:  
RAM:  
Diskas:  
Operacinė sistema:  

---

## Testavimo aplinka

Čia įterpti ekrano nuotraukas:
- programos paleidimas
- testavimo eiga
- rezultatų lentelės

---

## Projekto struktūra

main.cpp  
meniu.cpp  
skaitymas.cpp  
Generavimas.cpp  
spausdinam.cpp  
tyrimas.cpp  
laikai.cpp  

studentas.h  
konteineris.h  
meniu.h  
skaitymas.h  
Generavimas.h  
spausdinam.h  
tyrimas.h  
laikai.h  

Makefile  

---

## Paleidimas

### Kompiliavimas

make

### Paleidimas

.\programa_vector  
.\programa_list  
.\programa_deque  

---

## Valymas

make clean
