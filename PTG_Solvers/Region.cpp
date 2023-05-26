//
// Created by Julie Parreaux.
//

#include "Region.h"

Region::Region(){
    inf = 0;
    sup = 1;
}
Region::Region(int new_inf, int new_sup) {
    if (new_inf > new_sup)
        throw "Region constructor : bad interval as inf <= sup";
    if (new_inf < 0)
        throw "Region constructor : bad interval as inf >=0";
    inf = new_inf;
    sup = new_sup;
}

int Region::getInf() const {return  inf;}
int Region::getSup() const {return  sup;}

string Region::toString() const {
    return "[" + std::to_string(inf) + ", " + std::to_string(sup) + "]";
}
void Region::show() const {cout << "[" << inf << ", " << sup << "]";}

bool Region::operator==(const Region& region) const {
    return inf == region.inf && sup == region.sup;
}
bool Region::operator<(const Region& region) const {
    return (inf < region.inf || (inf == region.inf && sup < region.sup));
}
bool Region::operator<=(const Region& region) const {
    return (*this < region || *this == region);
}

bool equalSetRegion(set<Region> regions1, set<Region> regions2){
    bool result =true;
    for (auto region : regions1){result &= (containsSetRegion(regions2, region));}
    for (auto region : regions2){result &= (containsSetRegion(regions1, region));}
    return result;
}
bool containsSetRegion(set<Region> regions, Region region){
    bool result = false;
    for (auto reg : regions){result |= (reg == region);}
    return result;
}

void showSetRegion(set<Region>* regions){
    for (auto region : *regions){
        region.show();
    }
    cout << endl;
}

Fraction Region::getMiddelValue() {
    return Fraction(inf + sup, 2);
}
