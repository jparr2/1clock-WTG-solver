/*
 * Author: Julie Parreaux
 */

#include "Transition.hpp"

/*
 * Constructors
 */
Transition::Transition() {
    origin = new State();
    destination = new State();
    weight = 0;
    guard = Guard();
    reset = true;
    label = "t";
    used = false;
    newStates=false;
}
Transition::Transition(Transition *transition) {
    origin = transition->origin;
    destination = transition->destination;
    weight = transition->weight;
    guard = transition->guard;
    reset = transition->reset;
    label = transition->label + "-copy";
    used = transition->used;
    newStates = false;
}
Transition::Transition(State* origin1, int weight1, Guard guard1, bool reset1, State* destination1, string new_label){
    if (guard1.isEmpty())
        throw "Transition : guard must not be empty";
    if (*origin1 == *destination1)
        throw "Transition : no self-loop";
    if (destination1->isRegion()){
        Region reg0 = Region(0, 0);
        if (reset1 && !(reg0 == *destination1->getRegion()))
            throw "Transition : reset go to null region";
        if (!reset1 && origin1->isRegion() && (*destination1->getRegion() < *origin1->getRegion()))
            throw "Transition : no time back";
    }
    origin = origin1;
    destination = destination1;
    weight = weight1;
    guard = guard1;
    reset = reset1;
    label = new_label;
    used = false;
    newStates=false;
}
Transition::Transition(Transition* transition, Region* reg_origin, Region* reg_dest, string new_label) {
    Region reg0 = Region(0, 0);
    if (transition->isReset() && !(reg0 == *reg_dest)){
        throw "Transition : reset go to null region";
    }
    if (!transition->isReset() && reg_dest < reg_origin){
        throw "Transition : no time back";
    }
    origin = new State(transition->getOrigin(), reg_origin);
    destination = new State(transition->getDestination(), reg_dest);
    weight = transition->getWeight();
    reset = transition->isReset();
    if (reset)
        guard = transition->getGuard();
    else
        guard = Guard(transition->getGuard(), *reg_dest);
    used = transition->isUsed();
    label = new_label;
    newStates=true;
}


/*
 * Destructor
 */
Transition::~Transition() {
    if (newStates) {
        delete origin;
        delete destination;
        origin = nullptr;
        destination = nullptr;
    }
}



/*
 * Getters
 */
State* Transition::getOrigin() {return origin;}
State* Transition::getDestination() {return destination;}
int Transition::getWeight() const {return weight;}
Guard Transition::getGuard() {return guard;}
string Transition::getLabel() {return label;}

/*
 * Tester
 */
bool Transition::isReset() const {return reset;}
bool Transition::isUsed() {return used;}
bool Transition::isAvailable(Fraction clock) {return guard.isModel(clock);}
bool Transition::isReachable(Fraction clock) {return guard.isInClosedInterval(clock);}


/*
 * Setter
 */
void Transition::setUsed(bool use) {used = use;}

/*
 * Operator
 */
bool Transition::operator==(const Transition& transition) const {
    return (*transition.origin == *origin && transition.weight == weight &&
            transition.reset == reset && transition.guard == guard &&
            *transition.destination == *destination);
}


/*
 * Display function
 */
void Transition::show() {
    cout << "(" << origin->getLabel() << ", " << weight << ", ";
    guard.show();
    cout << ",  " << reset << ", " << destination->getLabel() << ")";
 }
string Transition::toString() {
    string result = "(" + origin->getLabel() + ", " + to_string(weight) + ", " +
            guard.toString() + ",  ";
    if (reset)
        result += "1";
    else
        result += "0";
    result += ", "  + destination->getLabel() + ")";
    return result;
}

Transition *Transition::copy() {
    return new Transition(origin, weight, guard, reset,
                                            destination, label);
}

