/*
 * Author : Julie Parreaux
 */

#include "State.hpp"

/*
 * Constructors
 */
State::State() {
    label = "lf";
    owner = Owner::Target;
    weight = 0;
    value = new Function(Fraction(0), Fraction(1));
    isshow = false;
    tmpValue = nullptr;
    region = nullptr;
}
State::State(string label1, Owner owner1, int weight1, Fraction finalWeight) {
    label = std::move(label1);
    owner = owner1;
    if (owner == Owner::Target) {
        value = new Function(finalWeight, Fraction(1));
    }
    else{
        value = new Function(Fraction(true), Fraction(1));
    }
    weight = weight1;
    isshow = false;
    tmpValue = nullptr;
    region= nullptr;
}
State::State(State *new_state) {
    label = new_state->label;
    owner = new_state->owner;
    weight = new_state->weight;
    isshow = false;
    tmpValue = nullptr;
    if (owner == Owner::Target) {
        value = new Function(new_state->getFinalWeight(), Fraction(1));
    }
    else{
        value = new Function(Fraction(true), Fraction(1));
    }
    if (new_state->region != nullptr) {
        region = new Region(new_state->region->getInf(), new_state->region->getSup());
    }
    else
        region = nullptr;
}

/*
 * Constructor to region state
 */
State::State(string new_label, Owner new_owner, int new_weight, Fraction new_finalWeight, Region* new_region) {
    label = std::move(new_label);
    owner = new_owner;
    if (owner == Owner::Target) {
        value = new Function(new_finalWeight, Fraction(1));
    }
    else{
        value = new Function(Fraction(true), Fraction(1));
    }
    weight = new_weight;
    isshow = false;
    tmpValue = nullptr;
    region = new Region(new_region->getInf(), new_region->getSup());
}
State::State(State* new_state, Region* reg){
    label = "(" + new_state->label + ", " + reg->toString() + ")";
    owner = new_state->owner;
    weight = new_state->weight;
    isshow = false;
    tmpValue = nullptr;
    if (owner == Owner::Target) {
        Fraction finWeight = new_state->getFinalWeight();
        value = new Function( finWeight, Fraction(1));
    }
    else{
        value = new Function(Fraction(false), Fraction(1));
    }
    region = new Region(reg->getInf(), reg->getSup());
}


/*
 * Destructor
 */
State::~State() {
    if (value != nullptr) {
        delete value;
    }
    if (tmpValue != nullptr) {
        delete tmpValue;
    }
    if (region != nullptr)
        delete region;
    value = nullptr;
    tmpValue = nullptr;
    region = nullptr;
}

/*
 * Getters
 */
string State::getLabel() {return label;}
int State::getWeight() const {return weight;}
Fraction State::getFinalWeight() {
    if (owner == Owner::Target)
        return value->getStart().getValue();
    throw "getFinalWeight: no final weight in Min/Max state";
}
Function* State::getValueFunction() {return value;}
Function* State::getTmpValue() {return tmpValue;}
Region* State::getRegion() {
    if (region != nullptr)
        return region;
    throw "getRegion: no region instanciate";
}
Owner State::getOwner() {return owner;}


/*
 * Tester
 */
bool State::isMin() {return owner == Owner::Min;}
bool State::isMax() {return owner == Owner::Max;}
bool State::isTarget() {return owner == Owner::Target;}
bool State::isShow() {return isshow;}
bool State::isUsed() {return isused;}
bool State::isRegion() {return region != nullptr;}

/*
 * Setters
 */
void State::setValue(Function* value1) {delete value; value = value1;}
void State::setTmpValue(Function* tmpValue1) {delete tmpValue; tmpValue = tmpValue1;}
void State::setShow(bool show) {isshow = show;}
void State::setUpdateValue() {
    if (tmpValue != nullptr) {
        delete value;
        value = tmpValue;
        tmpValue = nullptr;
    }
}
void State::setUsed(bool isUsed) {isused = isUsed;}


/*
 * Operator
 */
bool State::operator==(const State& state) const {
    return (label == state.label);
}

/*
 * Display function
 */
void State::show() {
    cout << "(" << label << ", ";
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
    cout << ")";
}
string State::toString() {
    string result = "(" + label + ", ";
    if (owner == Owner::Min)
        result += "Min";
    if (owner == Owner::Max)
        result += "Max";
    if (owner == Owner::Target) {
        result += "Target";
    }
    else
        result += ", " + to_string(weight);
    return result += ")";
}

/*
 * Copy
 */
State* State::copy() {
    if (owner == Owner::Target){
        if (region == nullptr)
            return (new State(label, owner, weight,value->getValueClock(Fraction(0))));
        return (new State(label, owner, weight,value->getValueClock(Fraction(0)), region));
    }
    if (region == nullptr)
        return (new State(label, owner, weight,Fraction(0)));
    return (new State(label, owner, weight, Fraction(0), region));
}

