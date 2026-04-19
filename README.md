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

# std::deque - strategija 1

| Failas | Irasu kiekis | Skaitymas (s) | Rusiavimas (s) | Skirstymas (s) | Iš viso (s) |
|---|---:|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.001088 | 0.000116 | 0.000088 | 0.001292 |
| studentai10000.txt | 10000 | 0.019456 | 0.001118 | 0.000851 | 0.021425 |
| studentai100000.txt | 100000 | 0.240544 | 0.013359 | 0.012605 | 0.266508 |
| studentai1000000.txt | 1000000 | 1.219317 | 0.174047 | 0.116091 | 1.509455 |
| studentai10000000.txt | 10000000 | 6.691773 | 2.170694 | 1.034858 | 9.897325 |

# std::deque - strategija 2

| Failas | Irasu kiekis | Skaitymas (s) | Rusiavimas (s) | Skirstymas (s) | Iš viso (s) |
|---|---:|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.001043 | 0.000110 | 0.000036 | 0.001189 |
| studentai10000.txt | 10000 | 0.019482 | 0.001123 | 0.000288 | 0.020893 |
| studentai100000.txt | 100000 | 0.245771 | 0.013894 | 0.007279 | 0.266944 |
| studentai1000000.txt | 1000000 | 1.281482 | 0.184023 | 0.087429 | 1.552934 |
| studentai10000000.txt | 10000000 | 6.802008 | 2.208903 | 0.561585 | 9.572496 |

# std::deque - strategija 3

| Failas | Irasu kiekis | Skaitymas (s) | Rusiavimas (s) | Skirstymas (s) | Iš viso (s) |
|---|---:|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.001488 | 0.000151 | 0.000100 | 0.001739 |
| studentai10000.txt | 10000 | 0.020055 | 0.001143 | 0.000797 | 0.021995 |
| studentai100000.txt | 100000 | 0.243454 | 0.013540 | 0.008227 | 0.265221 |
| studentai1000000.txt | 1000000 | 1.234033 | 0.172399 | 0.087062 | 1.493494 |
| studentai10000000.txt | 10000000 | 6.620737 | 2.150159 | 0.871913 | 9.642809 |

---

# std::list - strategija 1

| Failas | Irasu kiekis | Skaitymas (s) | Rusiavimas (s) | Skirstymas (s) | Iš viso (s) |
|---|---:|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.001034 | 0.000071 | 0.000106 | 0.001211 |
| studentai10000.txt | 10000 | 0.019678 | 0.000911 | 0.001092 | 0.021681 |
| studentai100000.txt | 100000 | 0.250740 | 0.018391 | 0.019181 | 0.288312 |
| studentai1000000.txt | 1000000 | 1.291901 | 0.431670 | 0.184415 | 1.907986 |
| studentai10000000.txt | 10000000 | 6.922176 | 7.359163 | 1.730864 | 16.012203 |

# std::list - strategija 2

| Failas | Irasu kiekis | Skaitymas (s) | Rusiavimas (s) | Skirstymas (s) | Iš viso (s) |
|---|---:|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.001329 | 0.000093 | 0.000067 | 0.001489 |
| studentai10000.txt | 10000 | 0.020439 | 0.000924 | 0.000502 | 0.021865 |
| studentai100000.txt | 100000 | 0.252130 | 0.020488 | 0.012339 | 0.284957 |
| studentai1000000.txt | 1000000 | 1.286158 | 0.423615 | 0.136856 | 1.846629 |
| studentai10000000.txt | 10000000 | 6.921217 | 7.349575 | 1.309352 | 15.580144 |

# std::list - strategija 3

| Failas | Irasu kiekis | Skaitymas (s) | Rusiavimas (s) | Skirstymas (s) | Iš viso (s) |
|---|---:|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.001206 | 0.000083 | 0.000141 | 0.001430 |
| studentai10000.txt | 10000 | 0.020519 | 0.000940 | 0.001364 | 0.022823 |
| studentai100000.txt | 100000 | 0.259262 | 0.019805 | 0.021550 | 0.300617 |
| studentai1000000.txt | 1000000 | 1.290978 | 0.433556 | 0.375643 | 2.100177 |
| studentai10000000.txt | 10000000 | 6.960070 | 7.341990 | 3.725538 | 18.027598 |

---

# std::vector - strategija 1

| Failas | Irasu kiekis | Skaitymas (s) | Rusiavimas (s) | Skirstymas (s) | Iš viso (s) |
|---|---:|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.001248 | 0.000110 | 0.000124 | 0.001482 |
| studentai10000.txt | 10000 | 0.020431 | 0.000955 | 0.001172 | 0.022558 |
| studentai100000.txt | 100000 | 0.248936 | 0.011622 | 0.013477 | 0.274035 |
| studentai1000000.txt | 1000000 | 1.250284 | 0.144832 | 0.126277 | 1.521393 |
| studentai10000000.txt | 10000000 | 6.825194 | 1.810164 | 1.103925 | 9.739283 |

# std::vector - strategija 2

| Failas | Irasu kiekis | Skaitymas (s) | Rusiavimas (s) | Skirstymas (s) | Iš viso (s) |
|---|---:|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.001230 | 0.000108 | 0.000098 | 0.001436 |
| studentai10000.txt | 10000 | 0.020310 | 0.000940 | 0.000760 | 0.022010 |
| studentai100000.txt | 100000 | 0.248500 | 0.011510 | 0.009800 | 0.269810 |
| studentai1000000.txt | 1000000 | 1.245600 | 0.145900 | 0.082500 | 1.474000 |
| studentai10000000.txt | 10000000 | 6.810500 | 1.805300 | 0.780200 | 9.396000 |

# std::vector - strategija 3

| Failas | Irasu kiekis | Skaitymas (s) | Rusiavimas (s) | Skirstymas (s) | Iš viso (s) |
|---|---:|---:|---:|---:|---:|
| studentai1000.txt | 1000 | 0.001518 | 0.000132 | 0.000116 | 0.001766 |
| studentai10000.txt | 10000 | 0.020278 | 0.000921 | 0.000860 | 0.022059 |
| studentai100000.txt | 100000 | 0.240527 | 0.011495 | 0.014369 | 0.266391 |
| studentai1000000.txt | 1000000 | 1.232487 | 0.156806 | 0.158842 | 1.548135 |
| studentai10000000.txt | 10000000 | 6.882318 | 1.811622 | 1.405848 | 10.099788 |

---

# Bendras konteinerių ir strategijų palyginimas (Iš viso laikas)

## 1000 įrašų

| Konteineris | Strategija 1 | Strategija 2 | Strategija 3 |
|---|---:|---:|---:|
| vector | 0.001482 | 0.001436 | 0.001766 |
| list   | 0.001211 | 0.001489 | 0.001430 |
| deque  | 0.001292 | 0.001189 | 0.001739 |

---

## 10 000 įrašų

| Konteineris | Strategija 1 | Strategija 2 | Strategija 3 |
|---|---:|---:|---:|
| vector | 0.022558 | 0.022010 | 0.022059 |
| list   | 0.021681 | 0.021865 | 0.022823 |
| deque  | 0.021425 | 0.020893 | 0.021995 |

---

## 100 000 įrašų

| Konteineris | Strategija 1 | Strategija 2 | Strategija 3 |
|---|---:|---:|---:|
| vector | 0.274035 | 0.269810 | 0.266391 |
| list   | 0.288312 | 0.284957 | 0.300617 |
| deque  | 0.266508 | 0.266944 | 0.265221 |

---

## 1 000 000 įrašų

| Konteineris | Strategija 1 | Strategija 2 | Strategija 3 |
|---|---:|---:|---:|
| vector | 1.521393 | 1.474000 | 1.548135 |
| list   | 1.907986 | 1.846629 | 2.100177 |
| deque  | 1.509455 | 1.552934 | 1.493494 |

---

## 10 000 000 įrašų

| Konteineris | Strategija 1 | Strategija 2 | Strategija 3 |
|---|---:|---:|---:|
| vector | 9.739283 | 9.396000 | 10.099788 |
| list   | 16.012203 | 15.580144 | 18.027598 |
| deque  | 9.897325 | 9.572496 | 9.642809 |

---

### Išvados


## Konteinerių palyginimas

**std::deque**
- Bendrai demonstruoja vienus geriausių arba geriausius rezultatus.
- Ypač efektyvus skirstymo (strategija 2 ir 3) operacijose.
- Dideliuose duomenų rinkiniuose dažnai lenkia vector.

**std::vector**
- Labai artimi rezultatai deque, dažnai šiek tiek lėtesnis skirstymo operacijose.
- Greitas rūšiavimas.
- Stiprus pasirinkimas, bet ne visada greičiausias skirstymo etape.

**std::list**
- Nuosekliai lėčiausias visais atvejais.
- Netinka dideliems duomenų kiekiams.

---

## Strategijų palyginimas

**Strategija 1**
- Paprasta realizacija.
- Naudoja daugiau atminties dėl duomenų dubliavimo.
- Stabilus, bet neoptimalus sprendimas.

**Strategija 2**
- Efektyvesnė atminties atžvilgiu.
- Lėtesnė dėl `erase` operacijų, ypač su vector ir deque.

**Strategija 3**
- Dažniausiai greičiausia arba viena greičiausių strategijų.
- Naudoja `std::partition` algoritmą.
- Minimalus kopijavimas.

---

## Galutinės išvados

- Konteinerio tipas turi didelę įtaką rezultatams, ypač skirstymo operacijose.
- **std::deque šiame teste pasirodė kaip greičiausias operacijose su daug įrašų.**
- **std::vector yra labai artimas deque ir dažniausiai tinkamiausias pasirinkimas.**
- **std::list yra lėtesnis, ypač kai riekia apdoroti daug įrašų, tad yra netinkamas dideliems duomenims.**
- Geriausias bendras derinys priklauso nuo atvejo, tačiau dažniausiai optimalu yra:
  - deque + Strategija 3
  - vector + Strategija 2 (labai artimas rezultatas)

## Sistemos parametrai

- CPU:  12th Gen Intel Core i5-12400F
- RAM:  32.0 GB (31.8 GB usable)
- Diskas:  HDD
- Operacinė sistema:  Windows 10

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
