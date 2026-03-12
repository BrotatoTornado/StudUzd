# Studentų duomenų apdorojimo programa

## v0.4

Ši versija skirta studentų duomenų automatiniam sukūrimui ir apdorojimui. Leidžia(nauja):

- generuoti studentų duomenų failus
- suskirstyti studentus į dvi grupes:
  - **vargšai** (galutinis balas < 5)
  - **protobokštai** (galutinis balas ≥ 5)
- išvesti rezultatus į failus automatiškai

Programai atlikta **veikimo spartos analizė**.

---

# Testavimo aplinka

| Parametras | Reikšmė |
|---|---|
| Kalba | C++ |
| Kompiliatorius | g++ (MinGW) |
| OS | Windows |
| Laiko matavimas | `std::chrono` |

---

# Testuojami duomenys

Buvo generuojami failai su skirtingu studentų kiekiu:

| Studentų skaičius |
|---|
| 1 000 |
| 10 000 |
| 100 000 |
| 1 000 000 |

---

# 1 tyrimas – failų generavimas

## Tikslas
Išmatuoti, kiek laiko užtrunka studentų duomenų failo sukūrimas.

## Rezultatai

| Studentų skaičius | Generavimo laikas (s) |
|---|---|
| 1 000 | 0.00255 |
| 10 000 | 0.022184 |
| 100 000 | 0.192418 |
| 1 000 000 | 2.37987 |
| 10 000 000 | 22.4681 |

---

# 2 tyrimas – duomenų apdorojimas

## Tikslas
Išmatuoti, kiek laiko užtrunka jau sugeneruotų studentų duomenų apdorojimas.

Buvo matuojami šie etapai:

1. duomenų nuskaitymas iš failo
2. studentų skirstymas į dvi grupes
3. rezultatų išvedimas į failus
4. bendras programos veikimo laikas

## Rezultatai (vidurkiai)

| Studentų skaičius | Skaitymas (s) | Skirstymas (s) | Rašymas (s) | Bendras laikas (s) |
|---|---|---|---|---|
| 1 000 | 0.00250 | 0.00012 | 0.00295 | 8.21 |
| 10 000 | 0.01557 | 0.00047 | 0.01522 | 7.84 |
| 100 000 | 0.07108 | 0.00442 | 0.10345 | 8.14 |
| 1 000 000 | 1.32472 | 0.05419 | 1.01897 | 9.26 |
| 10 000 000 | 10.91815 | 0.56308 | 9.93380 | 34.52 |

---

# Išvados

- Programa efektyviai tvarko studentų duomenis tiek mažiems, tiek dideliems kiekiams.
- Duomenų skaitymas ir failų išvedimas užima daugiausiai laiko, ypač esant milijonams įrašų, o studentų suskirstymas į grupes ir vidurkių/medianos skaičiavimas praktiškai neturi įtakos bendram vykdymo laikui.
- Optimizacijoms reikėtų dėmesio skirti failų įvesties/išvesties operacijoms arba naudoti binarinius failus ar didesnio našumo duomenų saugojimo būdus.

---

# Projekto struktūra
- main.cpp
- meniu.cpp
- skaitymas.cpp
- Generavimas.cpp
- spausdinam.cpp
/------------HEADERS------------\
studentas.h
meniu.h
skaitymas.h
Generavimas.h
spausdinam.h
---

# Naudotos bibliotekos

- `<iostream>`
- `<vector>`
- `<algorithm>`
- `<fstream>`
- `<iomanip>`
- `<chrono>`
- `<random>`
- `<sstream>`
