//
// Created by Julie Parreaux
//

#ifndef CODE_REGION_H
#define CODE_REGION_H

#include "Fraction.hpp"
#include <string>
#include <iostream>
#include <set>

using namespace std;

class Region{
private:
    int inf;
    int sup;

public:
    Region();
    Region(int inf, int sup);

    int getInf() const;
    int getSup() const;
    Fraction getMiddelValue();

    string toString() const;
    void show() const;

    bool operator==(const Region& region) const;
    bool operator<(const Region& region) const;
    bool operator<=(const Region& region) const;
};

bool equalSetRegion(set<Region> regions1, set<Region> regions2);
bool containsSetRegion(set<Region> regions, Region region);
void showSetRegion(set<Region>* regions);

#endif //CODE_REGION_H
