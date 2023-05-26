//
// Created by julie on 12/08/22.
//

#include "RegionPTG.h"

RegionPTG::RegionPTG(){}
RegionPTG::RegionPTG(PTG* ptg) {
    set <Region> *constant = ptg->getRegions();
    buildRegionStates(ptg->getStates(), constant);
    size = states->size();
    nb_transition = 0;
    buildRegionTransitions(ptg->getTransitions());
    delete constant;
}

void RegionPTG::buildRegionStates(MyList<State>* ptg_states, set<Region>* regions){
    for (auto state : *ptg_states->getList()){
        for (auto region: *regions) {
            states->add(new State(state, &region));
        }
    }
}
void RegionPTG::buildRegionTransitions(MyList<Transition>* ptg_transitions){
    for (auto transition : *ptg_transitions->getList()){
        State* origin = transition->getOrigin();
        State*  dest = transition->getDestination();
        auto guard = transition->getGuard();
        for (State* rstate : *states->getList()){
            auto reg_origin = rstate->getRegion();
            if (rstate->getLabel().find(origin->getLabel()) != string::npos
                && guard.isReachable(*reg_origin)) {
                for (auto rstate1 : *states->getList()) {
                    auto reg_dest = rstate1->getRegion();
                    if (rstate1->getLabel().find(dest->getLabel()) != string::npos) {
                        if ((!transition->isReset() && *reg_origin <= *reg_dest) &&
                            guard.isInInterval(reg_dest->getMiddelValue())) {
                                string label = "rt" + to_string(nb_transition);
                                transitions->add(new Transition(rstate, transition->getWeight(),
                                                                Guard(guard, *reg_dest),
                                                                transition->isReset(), rstate1,
                                                                label));
                                nb_transition++;
                        }
                        if ((transition->isReset() && *reg_dest == Region(0, 0)) &&
                            guard.isInInterval(reg_dest->getMiddelValue())) {
                                string label = "rt" + to_string(nb_transition);
                                transitions->add(new Transition(rstate, transition->getWeight(),
                                                                Guard(guard, *reg_origin),
                                                                transition->isReset(), rstate1,
                                                                label));
                                nb_transition++;
                        }
                    }
                }
            }
        }
    }
}

RegionPTG::~RegionPTG() {}


void RegionPTG::setPruned(string label){
    stack<State*> rstate_todo = stack<State*>();
    State* origin = getAState(label);
    rstate_todo.push(origin);
    origin->setUsed(true);
    while (!rstate_todo.empty()){
        State* current_state = rstate_todo.top();
        rstate_todo.pop();
        MyList<Transition>* state_transitions = getTransitionsState(current_state->getLabel());
        for (auto* rtransition : *state_transitions->getList()){
            State* dest = rtransition->getDestination();
            if (!dest->isUsed()) {
                dest->setUsed(true);
                rstate_todo.push(dest);
            }
            rtransition->setUsed(true);
        }
        state_transitions->clear();
        delete state_transitions;
    }
}
void RegionPTG::prunedPTG(string label){
    setPruned(label);
    cleaning();
}

void RegionPTG::cleaning() {
    auto it = transitions->getList()->begin();
    while (it != transitions->getList()->end()) {
        Transition* courrant = *it;
        if (!courrant->isUsed()) {
            it = transitions->getList()->erase(it);
            delete courrant;
        }
        else
            it ++;
    }
    auto it1 = states->getList()->begin();
    while (it1 != states->getList()->end()) {
        State* courrant = *it1;
        if (!courrant->isUsed()) {
            it1 = states->getList()->erase(it1);
            delete courrant;
        }
        else
            it1 ++;
    }
    states->allSetUsed(false);
    transitions->allSetUsed(false);
}
