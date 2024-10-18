#ifndef THEORETICAL_ERN_CALCULATOR_H
#define THEORETICAL_ERN_CALCULATOR_H

#include <string>
#include <vector>

using namespace std;

struct PatternERN {
    std::string name;
    int width;
    int height;
    int population;
    int ern;
};

vector<PatternERN> calculateTheoreticalERNs();
void displayTheoreticalERNs();

#endif