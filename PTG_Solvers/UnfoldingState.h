//
// Created by julie on 18/08/22.
//

#ifndef CODE_UNFOLDINGSTATE_H
#define CODE_UNFOLDINGSTATE_H

#include "State.hpp"
#include "Path.h"
#include "ValueIteration.hpp"

class UnfoldingState{
private:
    string label;
    int weight;
    Owner owner;
    Region* region;

    //Function of value attributs
    Function* value;
    Function* tmpValue;

    //Parameters attributs
    bool isshow;
    bool isused;

    // Path for unfolding
    Path* path;


public:
    UnfoldingState();
    UnfoldingState(string label, int weight, Owner owner, Path* path, Fraction finalWeight);
    UnfoldingState(string label, int weight, Owner owner, Region reg, Path* path, Fraction finalWeight);
    UnfoldingState(State* state, Path* path, string label);
    UnfoldingState(UnfoldingState* ustate, string label);
    UnfoldingState(UnfoldingState* ustate, Transition* transition, string label);
    UnfoldingState(UnfoldingState* ustate);

    ~UnfoldingState();

    // Getters
    string getLabel();
    int getWeight() const;
    Fraction getFinalWeight(); // Only if the state is a final state
    Owner getOwner();
    Function* getValueFunction();
    Function* getTmpValue();
    Region* getRegion();
    Path* getPath();

    // Tester
    bool isMin();
    bool isMax();
    bool isTarget();
    bool isShow();
    bool isUsed();
    bool isRegion();
    bool isUnfolding();

    // Setters
    void setValue(Function* newValue);
    void setTmpValue(Function* newTmpValue);
    void setShow(bool toShow);
    void setUpdateValue();
    void setUsed(bool isUsed);

    // Copy
    UnfoldingState* copy();

    // Operator
    bool operator==(const UnfoldingState& ustate) const;

    // Display function
    void show();
    string toString();
};

class ListUnfoldingState {
protected:
    list<UnfoldingState*>* states;

public:
    // Constructor
    ListUnfoldingState();

    // Destructor
    ~ListUnfoldingState();
    void clear();

    // Getter
    list<UnfoldingState*>* getListStates();
    int size();

    // Operator
    bool operator==(const ListUnfoldingState& listState) const;

    // List manipulation
    void add(UnfoldingState* state);
    void erase(UnfoldingState& state);
    bool containsState(UnfoldingState* state) const;
    UnfoldingState* find(const string& label);
    void allSetReachable(bool isReachable);

    // Display function
    void show();

    // Copy
    ListUnfoldingState* copy();
};


#endif //CODE_UNFOLDINGSTATE_H
