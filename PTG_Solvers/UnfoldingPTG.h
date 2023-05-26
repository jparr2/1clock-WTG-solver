//
// Created by julie on 19/12/22.
//

#ifndef CODE_UNFOLDINGPTG_H
#define CODE_UNFOLDINGPTG_H


#include "RegionPTG.h"
#include "UnfoldingState.h"
#include "UnfoldingTransition.h"
#include "MyList.h"
#include <vector>
#include  <set>
#include <string>
#include <stack>
#include <math.h>

class UnfoldingPTG {
private:
    long int kappa;
    int size;
    int nbTransition;
    UnfoldingState* lMin;
    UnfoldingState* lMax;
    UnfoldingState* lInfty;
    MyList<UnfoldingState>* statesTarget;
    MyList<UnfoldingState>* states;
    MyList<UnfoldingTransition>* transitions;

private:
    void addFinalStates(RegionPTG* ptg);
    void next(UnfoldingState* currentState, Transition transition, stack<UnfoldingState*>* statesToDo);
    void init(RegionPTG* ptg, string origin);

public:
    UnfoldingPTG();
    explicit UnfoldingPTG(RegionPTG* ptg, string origin);
    explicit UnfoldingPTG(RegionPTG* ptg, int new_kappa, string origin);


    ~UnfoldingPTG();

    // Getters
    MyList<UnfoldingState>* getStates();
    // Get the state named label if exist.
    UnfoldingState* getAState(const string& label);
    // Test if a state named label exist.
    bool containsState(const string& label) const;

    MyList<UnfoldingTransition>* getTransitions();
    // Get the transition from origin to destination if exist.
    UnfoldingTransition getATransition(const string& origin, const string& destination);
    // Test if a transition from origin to destination exist.
    bool containsTransitions(const string& origin, const string& destination);
    // Get the list of transitions from origin.
    MyList<UnfoldingTransition>* getTransitionsState(const string& origin);

    int getSize() const;
    int getMaxClock();
    int getMaxWeightLoc();
    int getMaxWeightTrans();
    Fraction getMaxWeightFin();

    // Setters
    void addState(UnfoldingState* state);
    void addTransition(UnfoldingTransition* transition);
    // Allow all states to be show.
    void setStatesShow();
    // Allow state named stateLabel to be show.
    void setAStateShow(const string& stateLabel);
    // Copy the temporal value in the current value.
    void updateValueStates();


    // Display functions
    void show();
    // Display all value functions.
    void showValues(bool here);

};


#endif //CODE_UNFOLDINGPTG_H
