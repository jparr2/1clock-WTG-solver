/*
 * Author : Julie Parreaux
 */

#ifndef CODE_VALUEITERATION_H
#define CODE_VALUEITERATION_H

#include "Function.hpp"

template <class Game, class Locations, class Edges> class ValueIteration{
private:
    // Compute value iteration

    /*
     * Compute value iteration for ptg until it converges.
     * Return the number of iteration needed to obtain the convergence.
     */
    static int valueConvergeValIt(Game* ptg, bool outable, bool here);
    // Compute value iteration for n iterations
    static bool valueConvergeValItSteps(Game* ptg, int n, bool outable, bool here);
    // Compute value iteration until it converges with an acceleration
    static int valueConverge(Game* ptg, bool outable, bool here);
    // Compute value iteration for n iterations with an acceleration
    static bool valueSomeSteps(Game* ptg, int n, bool outable, bool here);


    // Auxiliary function for value iteration

    // Compute the function from the chosen transition according the state's owner
    static Function* chooseTransition(Game* ptg, Locations* state);
    static Function* chooseMinTransition(list<Edges*>* transition, const Fraction& maxClock);
    static Function* chooseMaxTransition(list<Edges*>* transition, const Fraction& maxClock);

    // Compute the function from choice of delay for each interval given by the previous value
    static Function* chooseMinInterval(Edges* transition);
    static Function* chooseMaxInterval(Edges* transition);

    // Compute the good delay according the line.
    static list<Line>* tryWait(Edges* transition, Line line);


public:
    // Compute value iteration for ptg

    // Compute value iteration until it converges
    static void getValueSlow(Game* ptg, bool outable, bool here);
    // Compute value iteration for n steps
    static void getValueStepSlow(Game* ptg, int n, bool outable, bool here);
    // Compute value iteration until it converges for only a state
    static void getValueStateSlow(Game* ptg, const string& state, bool outable, bool here);
    // Compute value iteration for n steps for only a state
    static void getValueStateStepSlow(Game* ptg, const string& state, int n, bool outable, bool here);


    // Compute value iteration for ptg with an acceleration

    // Compute value iteration until it converges
    static void getValue(Game* ptg, bool outable, bool here);
    // Compute value iteration for n steps
    static void getValueStep(Game* ptg, int n, bool outable, bool here);
    // Compute value iteration until it converges for only a state
    static void getValueState(Game* ptg, const string& state, bool outable, bool here);
    // Compute value iteration for n steps for only a state
    static void getValueStateStep(Game* ptg, const string& state, int n, bool outable, bool here);


    // Display value of state according here
    static void printValue(bool here, Locations* state, int nbIteration);
};


#endif //CODE_VALUEITERATION_H
