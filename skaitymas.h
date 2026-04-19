#pragma once
#ifndef SKAITOM
#define SKAITOM

#include "konteineris.h"
#include <string>

void dinamuojamPazymius(Stud& studis);
bool failoSkaitymas(StudContainer& studis);
bool failoSkaitymas(StudContainer& studis, const std::string& pav);
void parinktiAtsitiktinius(Stud& studis);
void skaitomRanka(Stud& studis);
void suskaiciuotiGalutinius(StudContainer& studis);

#endif
