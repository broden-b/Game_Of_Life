#include "ern_calculator.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <iomanip>

using namespace std;

vector<PatternERN> calculateTheoreticalERNs() {
    vector<PatternERN> patterns;

    patterns.push_back({ "Block", 2, 2, 4, 8 });  // 2 + 2 + 4 = 8
    patterns.push_back({ "Beehive", 4, 3, 6, 13 });  // 4 + 3 + 6 = 13
    // Still Life Patterns

    patterns.push_back({ "Blinker", 3, 1, 3, 7 });  // 3 + 1 + 3 = 7 (horizontal configuration)
    patterns.push_back({ "Toad", 4, 2, 6, 12 });  // 4 + 2 + 6 = 12
    // Oscillator Patterns

    patterns.push_back({ "Glider", 3, 3, 5, 11 });  // 3 + 3 + 5 = 11
    patterns.push_back({ "LWSS (Lightweight spaceship)", 5, 4, 9, 18 });  // 5 + 4 + 9 = 18
    // Spaceship Patterns

    for (auto& pattern : patterns) {
        pattern.ern = pattern.width + pattern.height + pattern.population;
    }
    // Calculate ERN for each pattern

    sort(patterns.begin(), patterns.end(),
        [](const PatternERN& a, const PatternERN& b) { return a.ern < b.ern; });
    // Sort patterns by ERN in ascending order

    return patterns;
}

void displayTheoreticalERNs() {
    vector<PatternERN> patterns = calculateTheoreticalERNs();

    cout << "Theoretical Minimum ERNs for Game of Life Patterns:\n";
    cout << "-------------------------------------------------\n";
    cout << "Pattern Name                 Width  Height  Population  ERN\n";
    cout << "------------                 -----  ------  ----------  ---\n";

    for (const auto& pattern : patterns) {
        cout << left << setw(28) << pattern.name
            << setw(7) << pattern.width
            << setw(8) << pattern.height
            << setw(12) << pattern.population
            << pattern.ern << "\n";
    }

    cout << "\nThese are theoretical minimums based on the smallest known configurations.\n";
    cout << "Actual minimum ERNs in simulations might be larger due to required empty space around patterns.\n";
}

// Display the smallest possible ERNs for known Game of Life patterns