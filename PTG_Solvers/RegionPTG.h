//
// Created by julie on 12/08/22.
//

#ifndef CODE_REGIONPTG_H
#define CODE_REGIONPTG_H

#include "Transition.hpp"
#include "PTG.hpp"
#include <vector>
#include <list>
#include <set>
#include <string>
#include <stack>

class RegionPTG : public PTG{
private:
    void buildRegionStates(MyList<State>* states, set<Region>* regions);
    void buildRegionTransitions(MyList<Transition>* transition);
    void cleaning();

public:
    RegionPTG();
    RegionPTG(PTG* ptg);

    ~RegionPTG();

    void setPruned(string label);
    void prunedPTG(string label);

};




#endif //CODE_REGIONPTG_H
