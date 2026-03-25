#pragma once

#include "konteineris.h"

#include <string>

enum class SkirstymoStrategija
{
    Pirma = 1,
    Antra = 2
};

struct SkirstymoRezultatas
{
    StudContainer vargsiukai;
    StudContainer kietiakai;
};

void generuotiFaila();
std::string failoPavadinimas(const std::string& bazinisPavadinimas);
SkirstymoStrategija pasirinktiStrategija();
SkirstymoRezultatas skirstymasStrategija1(const StudContainer& studis);
SkirstymoRezultatas skirstymasStrategija2(StudContainer& studis);
SkirstymoRezultatas skirstymasGrupes(StudContainer& studis, SkirstymoStrategija strategija, bool irasytiIFailus = true, bool paprasytiRikiavimo = true);
