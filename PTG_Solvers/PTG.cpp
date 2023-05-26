/*
 * Author: Julie Parreaux
 */


#include "PTG.hpp"

/*
 * Constructors
 */
PTG::PTG(){
	states = new MyList<State>();
	transitions = new MyList<Transition>();
	size = 0;
    nb_transition = 0;
}
PTG::PTG(const string& f){

    states = new MyList<State>();
    transitions = new MyList<Transition>();
    size = 0;
    nb_transition = 0;

    ifstream file(f);
    if (!file) {
        delete states;
        delete transitions;
        throw "PTG: the file does not exis";
    }

    string line;
    bool state = false;
    bool transition = false;


    //cout << "Reading file..." << endl;
    while(getline(file, line)){
        string::iterator it = line.begin();
        it += removeWhite(it, line);

        if(line.find("Transitions") != std::string::npos) {
            state = false;
        }

        // Reading state
        if (state && it != line.end()){
            try {
                states->add(buildState(it, line));
                size++;
            }
            catch (const char* msg)  {
                cerr << msg << endl;
                delete transitions;
                states->clear();
                delete states;
                throw "PTG : bad format file";
            }
        }

        // Reading Transitions
        if (transition && it != line.end()) {
            try {
                transitions->add(buildTransition(it, line));
                nb_transition++;
            }
            catch (const char* msg)  {
                cerr << msg << endl;
                transitions->clear();
                delete transitions;
                states->clear();
                delete states;
                throw "PTG : bad format file";
            }
        }

        if(line.find("States") != std::string::npos) {
            state = true;
        }
        if(line.find("Transitions") != std::string::npos) {
            transition = true;
        }
    }
    file.close();
}
PTG::PTG(MyList<Transition>* cycle, Transition transition) {
    states = new MyList<State>();
    transitions = new MyList<Transition>();
    State* origin;
    State* dest;
    State* new_origin;
    State* new_dest;
    Transition* new_trans;
    for (Transition* trans : *cycle->getList()) {
        origin = trans->getOrigin();
        dest = trans->getDestination();
        new_origin = new State(origin->getLabel()+"-new", origin->getOwner(),
                                      origin->getWeight(), Fraction());
        new_dest = new State(dest->getLabel()+"-new", dest->getOwner(),
                                    dest->getWeight(), Fraction());
        new_trans = new Transition(new_origin, trans->getWeight(), trans->getGuard(),
                                               trans->isReset(),new_dest, "u");
        addTransition(new_trans);
        delete new_trans;
    }
    origin = transition.getOrigin();
    dest = transition.getDestination();
    new_origin = new State(origin->getLabel()+"-new", origin->getOwner(),
                                  origin->getWeight(), Fraction());
    new_dest = new State(dest->getLabel()+"-target", Owner::Target,
                                origin->getWeight(), Fraction(0));
    new_trans = new Transition(new_origin, transition.getWeight(), transition.getGuard(),
                                           transition.isReset(),new_dest, "u");
    addTransition(new_trans);
    delete new_trans;
}



/*
 * Destructor
 */
PTG::~PTG() {
    if (transitions != nullptr) {
        transitions->removeAll();
        transitions->clear();
        delete transitions;
    }
    if (states != nullptr) {
        states->removeAll();
        states->clear();
        delete states;
    }
}

/*
 * Getters
 */
MyList<State>* PTG::getStates() {return states;}
State* PTG::getAState(const string& label) {
    for(auto state : *states->getList()) {
        if (state->getLabel() == label)
            return state;
    }
    //std::string error = "PTG: not contains a state label by " + label;
    //cerr << error << endl;
    throw "PTG: state not contains";
}
bool PTG::containsState(const string& label) const {
    for(auto state : *states->getList()){
        if (state->getLabel() == label)
            return true;
    }
    return false;
}

MyList<Transition>* PTG::getTransitions() {return transitions;}
Transition PTG::getATransition(const string& origin, const string& destination) {
    for (auto & transition : *transitions->getList()) {
        if (transition->getOrigin()->getLabel() == origin &&
            transition->getDestination()->getLabel() == destination) {
            return *transition;
        }
    }
    throw "PTG: transition not exists";
}
bool PTG::containsTransitions(const string& origin, const string& destination) {
    for (auto & transition : *transitions->getList()) {
        if (transition->getOrigin()->getLabel() == origin &&
            transition->getDestination()->getLabel() == destination)
            return true;
    }
    return false;
}
MyList<Transition>* PTG::getTransitionsState(const string& origin) {
    auto result = new MyList<Transition>();
    for(auto & transition : *transitions->getList()){
        if (transition->getOrigin()->getLabel() == origin)
            result->add(transition);
    }
    return result;
}

int PTG::getSize() const {return size;}
int PTG::getMaxClock() {
    int max = 0;
    for (auto & transition : *transitions->getList()) {
        int tmp = transition->getGuard().getEndValue().asInt();
        if(tmp > max)
            max = tmp;
    }
    return max;
}
set<int>* PTG::getConstantClock(){
    auto* constants = new set<int>();
    for (auto & transition : *transitions->getList()) {
        int inf = transition->getGuard().getStartValue().asInt();
        int sup = transition->getGuard().getEndValue().asInt();
        constants->insert(inf);
        constants->insert(sup);
    }
    return constants;
}

/*
 * Setters
 */
void PTG::addState(State* state) {
    size++;
    states->add(state);
}
void PTG::addTransition(Transition* transition){
    State* origin_trans = transition->getOrigin();
    State* dest_trans = transition->getDestination();
    State* origin = states->find(transition->getOrigin()->getLabel());
    State* dest = states->find(transition->getDestination()->getLabel());
    if (origin == nullptr) {
        origin = origin_trans;
        addState(origin);
    } else {
        delete origin_trans;
    }
    if (dest == nullptr) {
        dest = dest_trans;
        addState(dest);
    } else {
        delete dest_trans;
    }
    transitions->add(new Transition(origin, transition->getWeight(), transition->getGuard(),
                                    transition->isReset(), dest, transition->getLabel()));
    nb_transition++;
}
void PTG::setStatesShow() {
    for (auto & state : *states->getList()){
        state->setShow(true);
    }
}
void PTG::setAStateShow(const string& stateLabel){
    getAState(stateLabel)->setShow(true);
}
void PTG::updateValueStates() {
    for (auto state : *states->getList())
        state->setUpdateValue();
}

/*
 * Display functions
 */
void PTG::show(){
	cout << "====PTG===" << endl;
    states->show();
    transitions->show();
	cout << endl;
}
void PTG::showValues(bool here) {
    for (auto state : *states->getList()){
        cout << "Value in " << state->getLabel() << " : ";
        state->getValueFunction()->show(here);
    }
}

int PTG::removeWhite(string::iterator itString, string line) {
    int size = 0;
    while (*itString == ' ' && itString != line.end()) {
        ++itString;
        size++;
    }
    return size;
}

pair<int, string> PTG::getString(string::iterator itString, const string& line) {
    string result;
    int size = 0;
    while (*itString != ' ' && *itString != ' ' && itString < line.end()) {
        if (*itString == ' ')
            cout << "oups" << endl;
        result += *itString;
        ++itString;
        size++;
    }
    return std::make_pair(size, result);
}

pair<int, int> PTG::getInt(string::iterator itString, const string& line, char c) {
    string result;
    int size = 0;
    while (*itString != c && itString != line.end()) {
        result += *itString;
        ++itString;
        size++;
    }
    int result_int = atoi(result.c_str());
    return make_pair(size, result_int);
}

pair<int, Guard> PTG::getGuard(string::iterator itString, const string &line) {
    bool typeOpen;

    bool typeEnd = false;
    int intEnd;
    string tmp;
    int size = 0;
    if(itString != line.end()){
        typeOpen = '[' == *itString;
        ++itString;
        size++;
    }
    pair<int, int> tmpInt = getInt(itString, line, ',');
    itString += tmpInt.first + 1;
    size += tmpInt.first + 1;
    int intOpen = tmpInt.second;
    while (*itString != ')' && *itString != ']' && itString != line.end()) {
        tmp += *itString;
        ++itString;
        size++;
    }
    intEnd = atoi(tmp.c_str());
    if(itString != line.end()){
        typeEnd = ']' == *itString;
        ++itString;
        size++;
    }
    return make_pair(size, Guard(Fraction(intOpen), Fraction(intEnd), typeOpen, typeEnd));
}

pair<int, bool> PTG::getBool(string::iterator itString, const string &line) {
    string result;
    int size = 0;
    while (*itString != ' ' && itString != line.end()) {
        result += *itString;
        ++itString;
        size++;
    }
    return make_pair(size, result == "true");
}

pair<int, Fraction> PTG::getFraction(string::iterator itString, const string& line) {
    int size = 0;
    pair<int, int> tmpInt = getInt(itString, line, '/');
    itString += tmpInt.first;
    size += tmpInt.first;
    int num = tmpInt.second;
    int den = 1;
    if (itString != line.end()) {
        ++itString;
        tmpInt = getInt(itString, line, ' ');
        size += tmpInt.first + 1;
        den = tmpInt.second;
    }
    return make_pair(size, Fraction(num, den));
}

State* PTG::buildState(string::iterator it, const string& line) {
    // Reading the label
    pair<int, string> tmpString = getString(it, line);
    it += tmpString.first;
    string label = tmpString.second;

    it += removeWhite(it, line);

    // Reading the owner
    tmpString = getString(it, line);
    it += tmpString.first;
    string owner = tmpString.second;

    it += removeWhite(it, line);

    if (it == line.end())
        throw "Building PTG : bad format line for the state " + line;

    // Reading the weight
    pair<int, int> tmpInt = getInt(it, line, ' ');
    it += tmpInt.first;
    int weight = tmpInt.second;

    it += removeWhite(it, line);
    Fraction finalWeight = Fraction();

    // Reading the final weight if exist
    if (owner == "Target")
        finalWeight = getFraction(it, line).second;

    // Building the State
    return (new State(label, getOwner(owner), weight, finalWeight));
}

Transition* PTG::buildTransition(string::iterator it, const string& line) {
    // Reading the origin label
    pair<int, string> tmpOrigin = getString(it, line);
    it += tmpOrigin.first;
    string labelOrigin = tmpOrigin.second;

    it += removeWhite(it, line);

    // Reading the weight
    pair<int, int> tmpInt = getInt(it, line, ' ');
    it += tmpInt.first;
    int weight = tmpInt.second;

    it += removeWhite(it, line);

    // Reading the guard
    pair<int, Guard> tmpGuard = getGuard(it, line);
    it += tmpGuard.first;
    Guard guard = tmpGuard.second;

    it += removeWhite(it, line);

    // Reading the reset
    pair<int, bool> tmpBool = getBool(it, line);
    it += tmpBool.first;
    bool reset = tmpBool.second;

    it += removeWhite(it, line);

    if (it == line.end())
        throw "Build PTG : bad format line for a transition " + line;

    // Reading the destination label
    pair<int, string> tmpDestination = getString(it, line);
    //it += tmpDestination.first;
    string labelDestination = tmpDestination.second;

    // Building the transition
    try {
        string label = "t" + to_string(nb_transition);
        return (new Transition(getAState(labelOrigin), weight, guard, reset,
                                           getAState(labelDestination), label));
    }
    catch  (const char* msg) {
        cerr << msg << endl;
        throw "Build PTG : not found state in PTG";
    }
}

set<Region>* PTG::getRegions() {
    auto* regions = new set<Region>();
    auto* constants = getConstantClock();
    auto it = constants->begin();
    while(it != constants->end()){
        auto it1 = it++;
        if (it != constants->end()){
            auto region = Region(*it1, *it);
            regions->insert(region);
        }
        auto region1 = Region(*it1, *it1);
        regions->insert(region1);
    }
    constants->clear();
    delete constants;
    return regions;
}


Fraction PTG::getMaxWeightFin() {
    Fraction maxWeight = Fraction(false);
    for (auto state : *states->getList()) {
        if (state->isTarget()){
            Fraction currentWeight = state->getFinalWeight();
            if (!currentWeight.isInfinite() && maxWeight < currentWeight){
                maxWeight = currentWeight;
            }
        }
    }
    return maxWeight;
}
int PTG::getMaxWeightLoc() {
    int maxWeight = 0;
    for (State* state : *states->getList()){
        if (!state->isTarget() && maxWeight < abs(state->getWeight()))
            maxWeight = abs(state->getWeight());
    }
    return  maxWeight;
}
int PTG::getMaxWeightTrans() {
    int maxWeight = 0;
    for (auto transition : *transitions->getList()){
        if (maxWeight < abs(transition->getWeight()))
            maxWeight = transition->getWeight();
    }
    return maxWeight;
}
















