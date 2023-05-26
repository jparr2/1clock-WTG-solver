/*
 * Author: Julie Parreaux
 */

#include "UnfoldingTransition.h"

/*
 * Constructors
 */
UnfoldingTransition::UnfoldingTransition() {
    origin = new UnfoldingState();
    destination = new UnfoldingState();
    weight = 0;
    guard = Guard();
    reset = true;
    label = "t";
    used = false;
    newStates=false;
}
UnfoldingTransition::UnfoldingTransition(UnfoldingTransition *transition) {
    origin = transition->origin;
    destination = transition->destination;
    weight = transition->weight;
    guard = transition->guard;
    reset = transition->reset;
    label = transition->label + "-copy";
    used = transition->used;
    newStates = false;
}
UnfoldingTransition::UnfoldingTransition(UnfoldingState* origin1, int weight1, Guard guard1, bool reset1, UnfoldingState* destination1, string new_label){
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
UnfoldingTransition::UnfoldingTransition(Transition *transition, Path *path, string new_label) {
    origin = new UnfoldingState(transition->getOrigin(), path,
                                transition->getOrigin()->getLabel());
    Path* dest_path = new Path(path, transition);
    destination = new UnfoldingState(transition->getDestination(), dest_path,
                                     transition->getDestination()->getLabel());
    guard = transition->getGuard();
    weight = transition->getWeight();
    reset = transition->isReset();
    label = new_label;
    used = false;
    newStates = true;
    delete dest_path;
}


/*
 * Destructor
 */
UnfoldingTransition::~UnfoldingTransition() {
    if (newStates) {
        delete origin;
        delete destination;
    }
}



/*
 * Getters
 */
UnfoldingState* UnfoldingTransition::getOrigin() {return origin;}
UnfoldingState* UnfoldingTransition::getDestination() {return destination;}
int UnfoldingTransition::getWeight() const {return weight;}
Guard UnfoldingTransition::getGuard() {return guard;}
string UnfoldingTransition::getLabel() {return label;}

/*
 * Tester
 */
bool UnfoldingTransition::isReset() const {return reset;}
bool UnfoldingTransition::isUsed() {return used;}
bool UnfoldingTransition::isAvailable(Fraction clock) {return guard.isModel(clock);}
bool UnfoldingTransition::isReachable(Fraction clock) {return guard.isInClosedInterval(clock);}


/*
 * Setter
 */
void UnfoldingTransition::setUsed(bool use) {used = use;}

/*
 * Operator
 */
bool UnfoldingTransition::operator==(const UnfoldingTransition& transition) const {
    return (*transition.origin == *origin && transition.weight == weight &&
            transition.reset == reset && transition.guard == guard &&
            *transition.destination == *destination);
}


/*
 * Display function
 */
void UnfoldingTransition::show() {
    cout << "(" << origin->getLabel() << ", " << weight << ", ";
    guard.show();
    cout << ",  " << reset << ", " << destination->getLabel() << ")";
}
string UnfoldingTransition::toString() {
    string result = "(" + origin->getLabel() + ", " + to_string(weight) + ", " +
                    guard.toString() + ",  ";
    if (reset)
        result += "1";
    else
        result += "0";
    result += ", "  + destination->getLabel() + ")";
    return result;
}

UnfoldingTransition *UnfoldingTransition::copy() {
    return new UnfoldingTransition(origin, weight, guard, reset,
                          destination, label);
}




/*
 * Class listTransition
 */
ListUnfoldingTransition::ListUnfoldingTransition() {
    transitions = new list<UnfoldingTransition*>();
}
ListUnfoldingTransition::~ListUnfoldingTransition() {delete transitions;}

void ListUnfoldingTransition::show() {
    cout << "Transitions " << endl;
    for (auto &transition: *transitions) {
        transition->show();
        cout << endl;
    }
}
string ListUnfoldingTransition::toString() {
    string result = "";
    for (auto & transition : *transitions){
        result += transition->toString();
    }
    return result;
}
bool ListUnfoldingTransition::containsTransition(UnfoldingTransition* transition) const {
    bool result = false;
    for (auto list_transition : *transitions)
        result |= (*transition == *list_transition);
    return result;
}
bool ListUnfoldingTransition::operator==(const ListUnfoldingTransition &listTransition) const {
    bool result = true;
    for (auto transition : *transitions)
        result &= listTransition.containsTransition(transition);
    for (auto & transition : *listTransition.transitions)
        result &= containsTransition(transition);
    return result;
}

list<UnfoldingTransition*>* ListUnfoldingTransition::getListTransition() {return transitions;}
UnfoldingTransition* ListUnfoldingTransition::getFirstElement() {return transitions->front();}
void ListUnfoldingTransition::removeFirstElement() {transitions->pop_front();}

void ListUnfoldingTransition::add(UnfoldingTransition *transition) {
    if (!containsTransition(transition))
        transitions->push_back(transition);
}
void ListUnfoldingTransition::erase(UnfoldingTransition& transition) {
    auto it = transitions->begin();
    while (it != transitions->end()) {
        auto current = *it;
        if (transition == *current){
            transitions->erase(it);
            return;
        }
        it++;
    }
}

UnfoldingTransition* ListUnfoldingTransition::find(const string &label) {
    auto it = transitions->begin();
    while (it != transitions->end()) {
        auto current = *it;
        if (current->getLabel() == label){
            auto copy = current->copy();
            transitions->erase(it);
            return copy;
        }
        it++;
    }
    return nullptr;
}
UnfoldingTransition* ListUnfoldingTransition::findLabel(const string &label) {
    auto it = transitions->begin();
    while (it != transitions->end()) {
        auto current = *it;
        if (label == current->getLabel()){
            auto copy = current->copy();
            transitions->erase(it);
            return copy;
        }
        it++;
    }
    return nullptr;
}
ListUnfoldingTransition ListUnfoldingTransition::findTransitionsState(const string &state) {
    ListUnfoldingTransition state_transitions = ListUnfoldingTransition();
    for (auto transition : *transitions) {
        if (state == transition->getOrigin()->getLabel()){
            state_transitions.add(transition);
        }
    }
    return state_transitions;
}

void ListUnfoldingTransition::clear() {transitions->clear();}
int ListUnfoldingTransition::size(){return transitions->size();}

void ListUnfoldingTransition::allSetUsed(bool isUsed){
    for (auto transition : *transitions){
        transition->setUsed(isUsed);
    }
}

ListUnfoldingTransition* ListUnfoldingTransition::copy() {
    ListUnfoldingTransition* result = new ListUnfoldingTransition();
    for (auto transition : *transitions)
        result->add(transition);
    return result;
}

