/*
 * Author: Samuel Dehouck & Julie Parreaux
 */

#include <iostream>
#include "PTG_Solvers/PTG.hpp"
#include "PTG_Solvers/RegionPTG.h"
#include "PTG_Solvers/UnfoldingPTG.h"
#include "PTG_Solvers/ValueIteration.hpp"
#include <cstring>
#include <cstdlib>

using namespace std;

ValueIteration<PTG, State, Transition> valueIteration;
ValueIteration<RegionPTG, State, Transition> regionValueIteration;
ValueIteration<UnfoldingPTG, UnfoldingState, UnfoldingTransition> unfoldingValueIteration;

int main(int argc, char *argv[]){
	int nb = 0;
	string stateLabel = "all";
	bool show = false;
	bool slow = false;
    bool here = true;
    bool region = false;
    bool unfolding = false;
	char* file = nullptr;

	for (int i = 1; i < argc; ++i){
		if (strcmp(argv[i], "-nb") == 0) {
            ++i;
            nb = atoi(argv[i]);
        } else
            if (strcmp(argv[i], "-state") == 0) {
                ++i;
                stateLabel = argv[i];
            } else {
                if (strcmp(argv[i], "-here") == 0) {
                    here = false;
                }
                else {
                    show |= strcmp(argv[i], "-show") == 0;
                    slow |= strcmp(argv[i], "-slow") == 0;
                    region |= strcmp(argv[i], "-reg") == 0;
                    unfolding |= strcmp(argv[i], "-unfolding") == 0;
                    file = argv[i];
                }
            }
	}

	if (file != nullptr){
	    try {
            PTG* ptg = new PTG(file);
            if (here)
                ptg->show();
            if (!region && !unfolding) {
                if (stateLabel != "all") {
                    if (nb == 0) {
                        if (slow)
                            valueIteration.getValueStateSlow(ptg, stateLabel, show, here);
                        else
                            valueIteration.getValueState(ptg, stateLabel, show, here);

                    } else {
                        if (slow)
                            valueIteration.getValueStateStepSlow(ptg, stateLabel, nb, show, here);
                        else
                            valueIteration.getValueStateStep(ptg, stateLabel, nb, show, here);
                    }
                } else {
                    if (nb == 0) {
                        if (slow)
                            valueIteration.getValueSlow(ptg, show, here);
                        else
                            valueIteration.getValue(ptg, show, here);
                    } else {
                        if (slow)
                            valueIteration.getValueStepSlow(ptg, nb, show, here);

                        else
                            valueIteration.getValueStep(ptg, nb, show, here);
                    }
                }
                delete ptg;
            }
            else {
                RegionPTG* rptg = new RegionPTG(ptg);
                if (here)
                    rptg->show();
                delete ptg;
                if (!unfolding) {
                    if (stateLabel != "all") {
                        rptg->prunedPTG("(" + stateLabel + ", [0, 0])");
                        if (nb == 0) {
                            if (slow)
                                regionValueIteration.getValueStateSlow(rptg, stateLabel, show, here);
                            else
                                regionValueIteration.getValueState(rptg, stateLabel, show, here);

                        } else {
                            if (slow)
                                regionValueIteration.getValueStateStepSlow(rptg, stateLabel, nb, show, here);
                            else
                                regionValueIteration.getValueStateStep(rptg, stateLabel, nb, show, here);
                        }
                    } else {
                        if (nb == 0) {
                            if (slow)
                                regionValueIteration.getValueSlow(rptg, show, here);
                            else
                                regionValueIteration.getValue(rptg, show, here);
                        } else {
                            if (slow)
                                regionValueIteration.getValueStepSlow(rptg, nb, show, here);

                            else
                                regionValueIteration.getValueStep(rptg, nb, show, here);
                        }
                    }
                    delete rptg;
                }
                else {
                    if (stateLabel != "all") {
                        UnfoldingPTG* uptg = new UnfoldingPTG(rptg, "(" + stateLabel + ", [0, 0])");
                        if (here)
                            uptg->show();
                        delete rptg;
                        unfoldingValueIteration.getValueState(uptg, "(" + stateLabel + ", [0, 0])", show, here);
                        delete uptg;
                    } else {
                        throw "Please add a state when we unfold the game.";
                    }
                }
            }
        }
	    catch (const char* msg) {
            cerr << msg << endl;
        }
    }
	else
		cerr << "Nothing to be done..." << endl;
	return 1;
}
