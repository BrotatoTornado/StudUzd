#pragma once
#ifndef STUDENTAS
#define STUDENTAS

#include <string>
#include <vector>

struct Stud
{
    std::string vard, pav;
    int egrez;
    std::vector<int> rez;
    float vid = 0.0f, galrezMed = 0.0f, galrezVid = 0.0f;
};

#endif
