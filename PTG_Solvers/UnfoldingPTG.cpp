//
// Created by julie on 19/12/22.
//

#include "UnfoldingPTG.h"

UnfoldingPTG::UnfoldingPTG() {
    states = new MyList<UnfoldingState>();
    statesTarget = new MyList<UnfoldingState>();
    transitions = new MyList<UnfoldingTransition>();
    kappa = 0;
    nbTransition = 0;
    size = 0;
}
UnfoldingPTG::UnfoldingPTG(RegionPTG *ptg, int new_kappa, string origin) {
    kappa = new_kappa;
    states = new MyList<UnfoldingState>();
    transitions = new MyList<UnfoldingTransition>();
    statesTarget = new MyList<UnfoldingState>();
    size = 0;
    nbTransition = 0;
    init(ptg, origin);
}
UnfoldingPTG::UnfoldingPTG(RegionPTG *ptg, string origin) {
    int sizePTG = ptg->getSize();
    int maxWeightTrans = ptg->getMaxWeightTrans();
    kappa = pow(max(sizePTG, maxWeightTrans), 12);
    states = new MyList<UnfoldingState>();
    transitions = new MyList<UnfoldingTransition>();
    statesTarget = new MyList<UnfoldingState>();
    size = 0;
    nbTransition = 0;
    init(ptg, origin);
}

void UnfoldingPTG::init(RegionPTG* ptg, string origin) {
    MyList<Transition>* transitionsPTG = ptg->getTransitions();
    stack<UnfoldingState*>* statesToDo = new stack<UnfoldingState*>();
    addFinalStates(ptg);
    State state_origin = ptg->getAState(origin);
    Path emptyPath = Path();
    UnfoldingState* origin_ustate = new UnfoldingState(&state_origin, &emptyPath, state_origin.getLabel());
    statesToDo->push(origin_ustate);
    states->add(origin_ustate);
    size++;
    while (statesToDo->size() > 0) {
        UnfoldingState* currentState = statesToDo->top();
        statesToDo->pop();
        for (auto trans : *transitionsPTG->getList()) {
            if (currentState->getLabel().find(trans->getOrigin()->getLabel()) != string::npos) {
                next(currentState, trans, statesToDo);
            }
        }
    }
    delete statesToDo;
}
void UnfoldingPTG::addFinalStates(RegionPTG* ptg) {
    int sizePTG = ptg->getSize();
    int maxWeightLoc = ptg->getMaxWeightLoc();
    int maxWeightTrans = ptg->getMaxWeightTrans();
    Fraction maxFinalWeight = ptg->getMaxWeightFin();
    int maxClock = ptg->getMaxClock();
    Fraction maxWeightFin = Fraction(sizePTG * maxWeightTrans + maxClock * maxWeightLoc, 1) + maxFinalWeight;

    Region reg = Region(0,0);
    Path* path = new Path();
    lMin = new UnfoldingState("lMin", 0, Owner::Target, reg, path, Fraction(false));
    lMax = new UnfoldingState("lMax", 0, Owner::Target, reg, path, maxWeightFin);
    lInfty = new UnfoldingState("lInfty", 0, Owner::Target, path, Fraction(true));

    states->add(lMin);
    states->add(lMax);
    states->add(lInfty);
    size +=3;

    for (auto state : *ptg->getStates()->getList()){
        if (state->isTarget()){
            UnfoldingState* target = new UnfoldingState(state, path, state->getLabel());
            states->add(target);
            statesTarget->add(target);
            size++;
        }
    }
    delete path;
}
void UnfoldingPTG::next(UnfoldingState* currentState, Transition transition, stack<UnfoldingState*>* statesToDo) {
    State* destination = transition.getDestination();
    if (destination->isTarget()) {
        transitions->add(new UnfoldingTransition(currentState, transition.getWeight(),
                                                 transition.getGuard(), transition.isReset(),
                                                 statesTarget->getAElement(destination->getLabel()),
                                                 "u"+to_string(nbTransition)));
        nbTransition++;
        return;
    }
    if (transition.isReset()) {
        Path* path = currentState->getPath();
        if (path->contains(&transition)){
            MyList<Transition>* cycle = path->getListTransition(&transition);
            string label = cycle->getFirstElement()->getOrigin()->getLabel() + "-new";
            PTG* rptg = new PTG(cycle, transition);
            ValueIteration<PTG, State, Transition>::getValue(rptg, false, false);
            if (rptg->getAState(label)->getValueFunction()->getValueClock(Fraction(0)) >= Fraction(0)) {
                transitions->add(new UnfoldingTransition(currentState, transition.getWeight(),
                                                         transition.getGuard(), transition.isReset(),
                                                         lMax, "u"+to_string(nbTransition)));
                nbTransition++;
            }
            else {
                transitions->add(new UnfoldingTransition(currentState, transition.getWeight(),
                                                          transition.getGuard(), transition.isReset(),
                                                          lMin, "u"+to_string(nbTransition)));
                nbTransition++;
            }
            cycle->removeAll();
            cycle->clear();
            delete cycle;
            delete rptg;
            return;
        }
    }
    else {
        if (currentState->getPath()->sizeLastResetTransition() >= kappa) {
            transitions->add(new UnfoldingTransition(currentState, transition.getWeight(),
                                                     transition.getGuard(), transition.isReset(),
                                                     lInfty, "u" + to_string(nbTransition)));
            nbTransition++;
            return;
        }
    }
    Path* new_path = new Path(currentState->getPath(), &transition);
    UnfoldingState* next_state = new UnfoldingState(destination, new_path,
                                                    destination->getLabel()+"-s"+to_string(size));

    states->add(next_state);
    size++;
    transitions->add(new UnfoldingTransition(currentState, transition.getWeight(),
                                             transition.getGuard(), transition.isReset(),
                                             next_state, "u"+transition.getLabel()));
    nbTransition++;
    statesToDo->push(next_state);
    delete new_path;
    return;
}


/*
 * Destructor
 */
UnfoldingPTG::~UnfoldingPTG() {
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
   if (statesTarget != nullptr) {
       statesTarget->clear();
       delete statesTarget;
   }
}

/*
 * Getters
 */
MyList<UnfoldingState>* UnfoldingPTG::getStates() {return states;}
UnfoldingState* UnfoldingPTG::getAState(const string& label) {
    return states->getAElement(label);
}
bool UnfoldingPTG::containsState(const string& label) const {
    return states->containsString(label);
}

MyList<UnfoldingTransition>* UnfoldingPTG::getTransitions() {return transitions;}
UnfoldingTransition UnfoldingPTG::getATransition(const string& origin, const string& destination) {
    for (auto transition : *transitions->getList()) {
        if (transition->getOrigin()->getLabel() == origin &&
            transition->getDestination()->getLabel() == destination) {
            return *transition;
        }
    }
    throw "PTG: transition not exists";
}
bool UnfoldingPTG::containsTransitions(const string& origin, const string& destination) {
    for (auto & transition : *transitions->getList()) {
        if (transition->getOrigin()->getLabel() == origin &&
            transition->getDestination()->getLabel() == destination)
            return true;
    }
    return false;
}
MyList<UnfoldingTransition>* UnfoldingPTG::getTransitionsState(const string& origin) {
    auto result = new MyList<UnfoldingTransition>();
    for(UnfoldingTransition* transition : *transitions->getList()){
        if (transition->getOrigin()->getLabel() == origin)
            result->add(transition);
    }
    return result;
}

int UnfoldingPTG::getSize() const {return size;}
int UnfoldingPTG::getMaxClock() {
    int max = 0;
    for (auto & transition : *transitions->getList()) {
        int tmp = transition->getGuard().getEndValue().asInt();
        if(tmp > max)
            max = tmp;
    }
    return max;
}

/*
 * Setters
 */
void UnfoldingPTG::addState(UnfoldingState* state) {
    size++;
    states->add(state);
}
void UnfoldingPTG::addTransition(UnfoldingTransition* transition){
    if (!this->containsState(transition->getOrigin()->getLabel()))
        addState(transition->getOrigin());
    if (!this->containsState(transition->getDestination()->getLabel()))
        addState(transition->getDestination());
    transitions->add(transition);
    nbTransition++;
}
void UnfoldingPTG::setStatesShow() {
    for (auto & state : *states->getList()){
        state->setShow(true);
    }
}
void UnfoldingPTG::setAStateShow(const string& stateLabel){
    getAState(stateLabel)->setShow(true);
}
void UnfoldingPTG::updateValueStates() {
    for (auto state : *states->getList())
        state->setUpdateValue();
}

/*
 * Display functions
 */
void UnfoldingPTG::show(){
    cout << "====Unfolding PTG===" << endl;
    cout << "States" << endl;
    states->show();
    cout << "Transitions" << endl;
    transitions->show();
    cout << endl;
}
void UnfoldingPTG::showValues(bool here) {
    for (auto state : *states->getList()){
        cout << "Value in " << state->getLabel() << " : ";
        state->getValueFunction()->show(here);
    }
}

Fraction UnfoldingPTG::getMaxWeightFin() {
    Fraction maxWeight = Fraction(false);
    for (auto state : *states->getList()) {
        if (state->isTarget()){
            Fraction currentWeight = state->getFinalWeight();
            if (!currentWeight.isInfinite() && maxWeight > currentWeight){
                maxWeight = currentWeight;
            }
        }
    }
    return maxWeight;
}
int UnfoldingPTG::getMaxWeightLoc() {
    int maxWeight = 0;
    for (UnfoldingState* state : *states->getList()){
        if (!state->isTarget() && maxWeight < abs(state->getWeight()))
            maxWeight = state->getWeight();
    }
    return  maxWeight;
}
int UnfoldingPTG::getMaxWeightTrans() {
    int maxWeight = 0;
    for (auto transition : *transitions->getList()){
        if (maxWeight < abs(transition->getWeight()))
            maxWeight = transition->getWeight();
    }
    return maxWeight;
}



