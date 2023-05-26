//
// Created by julie on 19/08/22.
//

#ifndef CODE_UNFOLDINGTRANSITION_H
#define CODE_UNFOLDINGTRANSITION_H

#include "UnfoldingState.h"
#include "Guard.hpp"
#include <list>

class UnfoldingTransition {
private:
    UnfoldingState* origin;
    UnfoldingState* destination;
    int weight;
    Guard guard;
    bool reset;
    string label; // Label is supposed unique: equality are test in this label

    // Attribut of manipulation
    bool used;
    bool newStates;

public:
    // Constructors

    // Default constructor to build a self-loop on target state lf with no guard, a reset and a weight 0.
    UnfoldingTransition();
    UnfoldingTransition(UnfoldingTransition* transition);
    // Constructor to build a transition from origin to destination with parameter attributes.
    UnfoldingTransition(UnfoldingState* origin, int weight, Guard guard, bool reset, UnfoldingState* destination, string label);
    // Constructor to constraint a transition to a region (and create region state if is need)
    UnfoldingTransition(Transition* transition, Path* path, string new_label);

    // Destructors
    ~UnfoldingTransition();


    // Getters
    UnfoldingState* getOrigin();
    UnfoldingState* getDestination();
    int getWeight() const;
    Guard getGuard();
    string getLabel();

    // Tester
    bool isReset() const;
    bool isUsed();

    // Setter
    void setUsed(bool use);

    // Test if clock satisfies the guard
    bool isAvailable(Fraction clock);
    bool isReachable(Fraction clock);

    // Copy
    UnfoldingTransition* copy();

    // Operators
    bool operator==(const UnfoldingTransition& transition) const;


    // Display function
    void show();
    string toString();
};

// Functions on list of transitions
class ListUnfoldingTransition{
protected:
    list<UnfoldingTransition*>* transitions;

public:
    ListUnfoldingTransition();
    ~ListUnfoldingTransition();
    void clear();

    list<UnfoldingTransition*>* getListTransition();
    UnfoldingTransition* getFirstElement();
    ListUnfoldingTransition* copy();
    void removeFirstElement();
    int size();

    void show();
    string toString();

    bool containsTransition(UnfoldingTransition* transition) const;
    bool operator==(const ListUnfoldingTransition& listTransition) const;


    void add(UnfoldingTransition* transition);
    void erase(UnfoldingTransition& transition);
    UnfoldingTransition* find(const string& label);
    UnfoldingTransition* findLabel(const string& label);
    ListUnfoldingTransition findTransitionsState(const string& state);

    void allSetUsed(bool isUsed);

};


#endif //CODE_UNFOLDINGTRANSITION_H
