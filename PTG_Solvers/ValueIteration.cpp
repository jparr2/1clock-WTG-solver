/*
 * Author : Julie Parreaux
 */

#include "ValueIteration.hpp"
#include "PTG.hpp"
#include "RegionPTG.h"
#include "UnfoldingPTG.h"
/*
 * Private functions : compute value iteration
 */
template<class Game, class Locations, class Edges>
int ValueIteration<Game, Locations, Edges>::valueConvergeValIt(Game* ptg, bool show, bool here) {
    bool update = true;
    int n =0;
    MyList<Locations>* states = ptg->getStates();
    Function* functionValue;
    while (update){
        update = false;
        if(show && here)
            cout << "Step " << n << endl;
        for(auto state : *states->getList()){
            if (state->isTarget()) {
                if (show && state->isShow()) {
                    if (!here) {
                        cout << "Step" << n << " : " ;
                    }
                    cout << "Value in " << state->getLabel() << " : ";
                    state->getValueFunction()->show(here);
                }
            }
            else {
                functionValue = chooseTransition(ptg, state);
                update |= *functionValue != *state->getValueFunction();
                state->setTmpValue(functionValue);
                if (show && state->isShow()) {
                    if (!here) {
                        cout << "Step" << n << " : " ;
                    }
                    cout << "Value in " <<  state->getLabel() << " : ";
                    state->getValueFunction()->show(here);
                }
            }
        }
        ptg->updateValueStates();
        n++;
    }
    states->clear();
    //delete functionValue;
    return n;
}
template<class Game, class Locations, class Edges>
bool ValueIteration<Game, Locations, Edges>::valueConvergeValItSteps(Game* ptg, int n, bool show, bool here) {
    bool update;
    bool converge = false;
    auto* states = ptg->getStates();
    Function* functionValue;
    for (int i = 1; i <= n; i++){
        update = false;
        if (show && here)
            cout << "Step " << i << endl;
        for(auto state : *states->getList()){
            if (state->isTarget() && show)
                printValue(here, state, i);
            else {
                functionValue = chooseTransition(ptg, state);
                update |= *functionValue != *state->getValueFunction();
                state->setTmpValue(functionValue);
                if (show && state->isShow())
                    printValue(here, state, i);
            }
        }
        ptg->updateValueStates();
        converge |= !update;
    }
    return converge;
}
template<class Game, class Locations, class Edges>
void ValueIteration<Game, Locations, Edges>::printValue(bool here, Locations* state, int nbIteration){
    if (here)
        cout << "Value in " << state->getLabel() << ": ";
    else
        cout << "Value in " << state->getLabel() << " after " << nbIteration << " steps: ";
    state->getValueFunction()->show(here);
}

template<class Game, class Locations, class Edges>
int ValueIteration<Game, Locations, Edges>::valueConverge(Game* ptg, bool show, bool here){
    bool update = true;
    int nbInteration =0;
    MyList<Locations>* states = ptg->getStates();
    while (update){
        update = false;
        nbInteration++;
        if(show && here)
            cout << "Step " << nbInteration << endl;
        for(auto state : *states->getList()){
            if (state->isTarget()) {
                if (show && state->isShow())
                    printValue(here, state, nbInteration);
            }
            else {
                Function* functionValue = chooseTransition(ptg, state);
                update |= *functionValue != *state->getValueFunction();
                state->setValue(functionValue);
                if (show && state->isShow())
                    printValue(here, state, nbInteration);
            }
        }
    }
    return nbInteration;
}
template<class Game, class Locations, class Edges>
bool ValueIteration<Game, Locations, Edges>::valueSomeSteps(Game* ptg, int n, bool show, bool here) {
    bool update;
    bool converge = false;
    auto* states = ptg->getStates();
    for (int i = 1; i <= n; i++){
        update = false;
        if (show)
            cout << "Step " << i << endl;
        for(auto state : *states->getList()){
            if (state->isTarget()) {
                if (show) {
                    cout << "Value in " << state->getLabel() << " after " << i << "steps" << endl;
                    state->getValueFunction()->show(here);
                }
            }
            else {
                Function* functionValue = chooseTransition(ptg, state);
                update |= *functionValue != *state->getValueFunction();
                state->setValue(functionValue);
                if (show&& state->isShow()) {
                    cout << "Value in " << state->getLabel() << " after " << i << "steps" << endl;
                    state->getValueFunction()->show(here);
                }
            }
        }
        converge |= !update;
    }
    return converge;
}

/*
 * Private functions : auxiliary function for value iteration
 */
template<class Game, class Locations, class Edges>
Function* ValueIteration<Game, Locations, Edges>::chooseTransition(Game * ptg, Locations* state){
    MyList<Edges>* transitions = ptg->getTransitionsState(state->getLabel());
    Fraction maxClock;
    maxClock = Fraction(ptg->getMaxClock());
    Function* functionValue = nullptr;
    if (state->isMin()) {
        functionValue = chooseMinTransition(transitions->getList(), maxClock);
    }
    else if (state->isMax()) {
        functionValue = chooseMaxTransition(transitions->getList(), maxClock);
    }
    transitions->clear();
    delete transitions;
    return functionValue;
}
template<class Game, class Locations, class Edges>
Function* ValueIteration<Game, Locations, Edges>::chooseMinTransition(list<Edges*>* transitions, const Fraction& maxClock) {
    auto* result = new Function(Fraction(true), maxClock);
    for(auto transition : *transitions){
        Function* valueDestination = transition->getDestination()->getValueFunction();
        if (!(valueDestination->getStart().getValue() == Fraction(true))) {
            Function* tmp = chooseMinInterval(transition);
            result = minFunction(tmp, result);
            delete tmp;
        }
    }
    Function* final =new Function(result->getFunctionLine(), true);
    delete result;
    return final;
}
template<class Game, class Locations, class Edges>
Function* ValueIteration<Game, Locations, Edges>::chooseMaxTransition(list<Edges*>* transitions, const Fraction& maxClock) {
    Function* result = new Function(Fraction(false), maxClock);
    for(auto transition : *transitions){
        Function* valueDestination = transition->getDestination()->getValueFunction();
        if (valueDestination->getStart().getValue() == Fraction(true)) {
            delete result;
            return new Function(valueDestination->getFunctionLine(), false);
        }
        Function* tmp = chooseMaxInterval(transition);
        result = maxFunction(tmp, result);
        delete tmp;
    }
    Function* final =new Function(result->getFunctionLine(), true);
    delete result;
    return final;
}
template<class Game, class Locations, class Edges>
Function* ValueIteration<Game, Locations, Edges>::chooseMinInterval(Edges* transition) {
    Function* destinationValue = transition->getDestination()->getValueFunction();
    auto* lines = new list<Line>();
    for (auto line : *destinationValue->getFunctionLine()) {
        list<Line>* linesTmp = tryWait(transition, line);
        for (auto lineTmp : *linesTmp) {
            if (!containsLine(lines, lineTmp))
                lines->push_front(lineTmp);
        }
        linesTmp->clear();
        delete linesTmp;
    }
    auto* result = new Function(lines, true);
    lines->clear();
    delete lines;
    return result;
}
template<class Game, class Locations, class Edges>
Function* ValueIteration<Game, Locations, Edges>::chooseMaxInterval(Edges* transition) {
    auto* lines = new list<Line>();
    for (auto line : *transition->getDestination()->getValueFunction()->getFunctionLine()) {
        list<Line>* linesTmp = tryWait(transition, line);
        for (auto lineTmp : *linesTmp) {
            if (!containsLine(lines, lineTmp))
                lines->push_front(lineTmp);
        }
        linesTmp->clear();
        delete linesTmp;
    }
    auto* result= new Function(lines, false);
    lines->clear();
    delete lines;
    return result;
}
template<class Game, class Locations, class Edges>
list<Line>* ValueIteration<Game, Locations, Edges>::tryWait(Edges* transition, Line line){
    auto result = new list<Line>();
    Fraction lineStart = line.getStart();
    Fraction weightTransition = Fraction(transition->getWeight());
    Fraction weightState = Fraction(transition->getOrigin()->getWeight());
    Fraction startGuard = transition->getGuard().getStartValue();
    Fraction valDest0 = transition->getDestination()->getValueFunction()->getValueClock(Fraction());
    Fraction valDestStart = transition->getDestination()->getValueFunction()->getValueClock(startGuard);

    for (auto point : *transition->getDestination()->getValueFunction()->getFunctionPoint()){
        if (transition->isReachable(point.getClock()) && point.getClock() >= lineStart) {
            if (transition->isReset()) {
                Fraction intercept = weightTransition + valDest0;
                //no wait
                if (line.getStart() < startGuard) { // must be wait : guard is not satisfy
                    Line tmp = Line(-weightState, intercept + startGuard * weightState,
                                    line.getStart(), point.getClock());
                    result->push_front(tmp);
                } else if (point.getClock() <= line.getEnd()) {
                    Line tmp = Line(Fraction(), intercept, line.getStart(), point.getClock());
                    result->push_front(tmp);
                }
                // wait
                Line tmp = Line(-weightState, intercept + point.getClock() * weightState,
                                line.getStart(), point.getClock());
                result->push_front(tmp);
            } else {
                //no wait
                if (line.getStart() < startGuard) { // must be wait : guard is not satisfy
                    Line tmp = Line(-weightState, weightTransition + startGuard * weightState +
                                                  valDestStart, line.getStart(), point.getClock());
                    result->push_front(tmp);
                } else if (point.getClock() <= line.getEnd()) {
                    Line tmp = Line(line.getSlope(), weightTransition + line.getIntercept(), line.getStart(),
                                    point.getClock());
                    result->push_front(tmp);
                }
                // wait
                Line tmp = Line(-weightState, weightTransition + point.getClock() * weightState +
                        transition->getDestination()->getValueFunction()->getValueClock(point.getClock()),
                        line.getStart(), point.getClock());
                result->push_front(tmp);
            }
        }
    }
    return result;
}


/*
 * Compute value iteration for ptg.
 */
template<class Game, class Locations, class Edges>
void ValueIteration<Game, Locations, Edges>::getValueSlow(Game * ptg, bool show, bool here) {
    ptg->setStatesShow();
    if (show)
        cout << "Values by step" << endl;
    int n = valueConvergeValIt(ptg, show, here);
    cout << "Final values given after " << n << " steps" << endl;
    ptg->showValues(here);
}
template<class Game, class Locations, class Edges>
void ValueIteration<Game, Locations, Edges>::getValueStepSlow(Game * ptg, int n, bool show, bool here) {
    ptg->setStatesShow();
    if (show)
        cout << "Values by step" << endl;
    bool converge = valueConvergeValItSteps(ptg, n, show, here);
    ptg->showValues(here);
    if (converge)
        cout << "Value Iteration converged within " << n << " steps" << endl;
    else
        cout << "Value Iteration did not converge after " << n << " steps" << endl;
}
template<class Game, class Locations, class Edges>
void ValueIteration<Game, Locations, Edges>::getValueStateSlow(Game * ptg, const string& state, bool show, bool here) {
    ptg->setAStateShow(state);
    if (show)
        cout << "Values by step" << endl;
    valueConvergeValIt(ptg, show, here);
    cout << "Final value in : " << state;
    ptg->getAState(state)->getValueFunction()->show(here);
}
template<class Game, class Locations, class Edges>
void ValueIteration<Game, Locations, Edges>::getValueStateStepSlow(Game * ptg, const string& state, int n, bool show, bool here) {
    ptg->setAStateShow(state);
    if (show)
        cout << "Values by step" << endl;
    bool converge = valueConvergeValItSteps(ptg, n, show, here);
    cout << "Value in " << state << " after " << n << " steps : ";
    ptg->getAState(state)->getValueFunction()->show(here);
    if (converge)
        cout << "Value Iteration converged in " << n << " steps" << endl;
    else
        cout << "Value Iteration did not converge after " << n << " steps" << endl;
}


/*
 * Compute value iteration for ptg with an acceleration
 */
template<class Game, class Locations, class Edges>
void ValueIteration<Game, Locations, Edges>::getValue(Game * ptg, bool show, bool here) {
    ptg->setStatesShow();
    if (show && here)
        cout << "Values by step" << endl;
    int n = valueConverge(ptg, show, here);
    cout << "Value Iteration converged within " << n << " steps" << endl;
    if (!show || here)
        ptg->showValues(here);
}

template<class Game, class Locations, class Edges>
void ValueIteration<Game, Locations, Edges>::getValueStep(Game * ptg, int n, bool show, bool here) {
    ptg->setStatesShow();
    if (show && here)
        cout << "Values by step" << endl;
    bool converge = valueSomeSteps(ptg, n, show, here);
    if (converge)
        cout << "Value Iteration converged within " << n << " steps" << endl;
    else
        cout << "Value Iteration did not converge after " << n << " steps" << endl;
    if (here) {
        cout << "Values obtains after " << n << " steps" << endl;
        ptg->showValues(here);
    }
    else if (!show) {
        ptg->showValues(here);
    }
}
template<class Game, class Locations, class Edges>
void ValueIteration<Game, Locations, Edges>::getValueState(Game * ptg, const string& state, bool show, bool here) {
    ptg->setAStateShow(state);
    if (show)
        cout << "Values by step" << endl;
    valueConverge(ptg, show, here);
    cout << "Value Iteration done" << endl;
    cout << "Value in " << state << ":";
    ptg->getAState(state)->getValueFunction()->show(here);
}
template<class Game, class Locations, class Edges>
void ValueIteration<Game, Locations, Edges>::getValueStateStep(Game * ptg, const string& state, int n, bool show, bool here) {
    ptg->setAStateShow(state);
    if (show)
        cout << "Values by step" << endl;
    bool converge = valueSomeSteps(ptg, n, show, here);
    cout << "Value in " << state << " after " << n << " steps : ";
    ptg->getAState(state)->getValueFunction()->show(here);
    if (converge)
        cout << "Value Iteration converged in " << n << " steps" << endl;
    else
        cout << "Value Iteration did not converge after " << n << " steps" << endl;
}

template class ValueIteration<PTG, State, Transition>;
template class ValueIteration<RegionPTG, State, Transition>;
template class ValueIteration<UnfoldingPTG, UnfoldingState, UnfoldingTransition>;






