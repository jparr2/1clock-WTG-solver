//
// Created by julie on 18/08/22.
//

#include "UnfoldingState.h"

/*
 * Constructors
 */
UnfoldingState::UnfoldingState(){
    label = "lf";
    owner = Owner::Target;
    weight = 0;
    value = new Function(Fraction(0), Fraction(1));
    isshow = false;
    tmpValue = nullptr;
    region = nullptr;
    path = nullptr;
}
UnfoldingState::UnfoldingState(string label1, int weight1, Owner owner1, Path* path1, Fraction finalWeight) {
    label = label1;
    weight = weight1;
    owner = owner1;
    if (path1 != nullptr)
        path = new Path(path1);
    else
        path = nullptr;
    if (owner == Owner::Target)
        value = new Function(finalWeight, Fraction(1));
    else
        value = new Function(Fraction(true), Fraction(1));
    isshow = false;
    region = nullptr;
    tmpValue = nullptr;
}
UnfoldingState::UnfoldingState(string label1, int weight1, Owner owner1, Region reg, Path* path1, Fraction finalWeight) {
    label = label1;
    weight = weight1;
    owner = owner1;
    if (path1 != nullptr)
        path = new Path(path1);
    else
        path = nullptr;
    if (owner == Owner::Target)
        value = new Function(finalWeight, Fraction(1));
    else
        value = new Function(Fraction(true), Fraction(1));
    region = new Region(reg);
    isshow = false;
    tmpValue = nullptr;
}
UnfoldingState::UnfoldingState(State *state, Path* path1, string label1) {
    label = label1;
    weight = state->getWeight();
    owner = state->getOwner();
    if (path1 != nullptr)
        path = new Path(path1);
    else
        path = nullptr;
    if (owner == Owner::Target)
        value = new Function(state->getFinalWeight(), Fraction(1));
    else
        value = new Function(Fraction(true), Fraction(1));
    if (!state->isRegion()) {
        region = nullptr;
    } else {
        region = new Region(*state->getRegion());
    }
    isshow = false;
    tmpValue = nullptr;
}
UnfoldingState::UnfoldingState(UnfoldingState *ustate, string label1) {
    label = label1;
    weight = ustate->getWeight();
    owner = ustate->getOwner();
    if (ustate->path == nullptr) {
        path = nullptr;
    } else {
        path = new Path(ustate->path);
    }
    if (owner == Owner::Target)
        value = new Function(ustate->getFinalWeight(), Fraction(1));
    else
        value = new Function(Fraction(true), Fraction(1));
    if (ustate->region == nullptr) {
        region = nullptr;
    } else {
        region = new Region(*ustate->region);
    }
    isshow = false;
    tmpValue = nullptr;
}
UnfoldingState::UnfoldingState(UnfoldingState *ustate, Transition* transition, string label1) {
    label = label1;
    weight = ustate->getWeight();
    owner = ustate->getOwner();
    if (ustate->path != nullptr)
        path = new Path(ustate->getPath(), transition);
    else
        path = new Path(transition);
    if (owner == Owner::Target)
        value = new Function(ustate->getFinalWeight(), Fraction(1));
    else
        value = new Function(Fraction(true), Fraction(1));
    if (ustate->region == nullptr) {
        region = nullptr;
    } else {
        region = new Region(*ustate->region);
    }
    isshow = false;
    tmpValue = nullptr;
}
UnfoldingState::UnfoldingState(UnfoldingState *ustate) {
    label = ustate->label;
    weight = ustate->weight;
    owner = ustate->owner;
    if (ustate->path != nullptr)
        path = new Path(ustate->path);
    else
        path = nullptr;
    if (owner == Owner::Target)
        value = new Function(ustate->getFinalWeight(), Fraction(1));
    else
        value = new Function(Fraction(true), Fraction(1));
    if (ustate->region == nullptr) {
        region = nullptr;
    } else {
        region = new Region(*ustate->region);
    }
    isshow = false;
    tmpValue = nullptr;
}

/*
 * Destructor
 */
UnfoldingState::~UnfoldingState() {
    delete value;
    delete tmpValue;
    delete region;
    delete path;
    value = nullptr;
    tmpValue = nullptr;
    region = nullptr;
    path = nullptr;
}

/*
 * Getters
 */
Owner UnfoldingState::getOwner() {return owner;}
int UnfoldingState::getWeight() const {return weight;}
string UnfoldingState::getLabel() {return label;}
Function* UnfoldingState::getValueFunction() {return value;}
Function*  UnfoldingState::getTmpValue() {return tmpValue;}
Fraction  UnfoldingState::getFinalWeight() {
    if (owner == Owner::Target)
        return value->getStart().getValue();
    throw "getFinalWeight: no final weight in Min/Max state";
}
Region*  UnfoldingState::getRegion() {
    if (region != nullptr)
        return region;
    throw "getRegion: no region instanciate";
}
Path* UnfoldingState::getPath() {
    if (path != nullptr)
        return path;
    throw "getPath: no path instanciate";
}

/*
 * Tester
 */
bool UnfoldingState::isMin() {return owner == Owner::Min;}
bool UnfoldingState::isMax() {return owner == Owner::Max;}
bool UnfoldingState::isTarget() {return owner == Owner::Target;}
bool UnfoldingState::isShow() {return isshow;}
bool UnfoldingState::isUsed() {return isused;}
bool UnfoldingState::isRegion() {return region != nullptr;}
bool UnfoldingState::isUnfolding() {return path != nullptr;}

/*
 * Setters
 */
void UnfoldingState::setValue(Function* value1) {delete value; value = value1;}
void UnfoldingState::setTmpValue(Function* tmpValue1) {delete tmpValue; tmpValue = tmpValue1;}
void UnfoldingState::setShow(bool show) {isshow = show;}
void UnfoldingState::setUpdateValue() {
    if (tmpValue != nullptr) {
        value = tmpValue;
        tmpValue = nullptr;
    }
}
void UnfoldingState::setUsed(bool isUsed) {isused = isUsed;}


/*
 * Operator
 */
bool UnfoldingState::operator==(const UnfoldingState& ustate) const {
    return (label == ustate.label && *path == *ustate.path);
}

/*
 * Display function
 */
void UnfoldingState::show() {
    cout << "[(" << label << ", ";
    if (owner == Owner::Min)
        cout << "Min";
    if (owner == Owner::Max)
        cout << "Max";
    if (owner == Owner::Target) {
        cout << "Target" << ", ";
        getFinalWeight().show();
    }
    else
        cout << ", " << weight;
    cout << ") - ";
    path->show();
    cout << "]";
}
string UnfoldingState::toString() {
    string result = "[(" + label +", ";
    if (owner == Owner::Min)
        result += "Min";
    if (owner == Owner::Max)
        result += "Max";
    if (owner == Owner::Target) {
        result += "Target";
    }
    else
        result += ", " + to_string(weight);
    return result + ")]";
}

/*
 * Copy
 */
UnfoldingState* UnfoldingState::copy() {
    return new UnfoldingState(this, label);
}

/*
 * Class ListUnfoldingState
 */
ListUnfoldingState::ListUnfoldingState()  {
    states = new list<UnfoldingState*>();
}
ListUnfoldingState::~ListUnfoldingState(){delete states;}
void ListUnfoldingState::clear() {states->clear();}

list<UnfoldingState*>* ListUnfoldingState::getListStates() {return states;}
int ListUnfoldingState::size() {return states->size();}

void ListUnfoldingState::add(UnfoldingState* state) {
    if (!containsState(state)){
        states->push_back(state);
    }
}
void ListUnfoldingState::erase(UnfoldingState& state) {
    auto it = states->begin();
    while (it != states->end()) {
        auto current = *it;
        if (state == *current){
            states->erase(it);
            return;
        }
        it++;
    }
}
bool ListUnfoldingState::containsState(UnfoldingState* state) const {
    bool result = false;
    for (auto ustate : *states){result |= (*ustate == *state);}
    return result;
}
UnfoldingState* ListUnfoldingState::find(const string& label) {
    auto it = states->begin();
    while (it != states->end()) {
        auto current = *it;
        if (label == current->getLabel()){
            //auto copy = current->copy();
            states->erase(it);
            return current;
        }
        it++;
    }
    return nullptr;
}
void ListUnfoldingState::allSetReachable(bool isReachable) {
    for (UnfoldingState* state : *states){
        state->setUsed(isReachable);
    }
}

bool ListUnfoldingState::operator==(const ListUnfoldingState &listState) const {
    bool result = true;
    for (auto ustate : *states){result &= listState.containsState(ustate);}
    for (auto ustate : *listState.states){result &= containsState(ustate);}
    return result;
}

ListUnfoldingState* ListUnfoldingState::copy() {
    ListUnfoldingState* result = new ListUnfoldingState();
    for (auto state : *states)
        result->add(state);
    return result;
}

void ListUnfoldingState::show() {
    cout << "UnfoldingStates " << endl;
    for (auto state : *states) {
        state->show();
    }
}