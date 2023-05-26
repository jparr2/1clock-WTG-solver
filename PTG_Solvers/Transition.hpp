/*
 * Author: Julie Parreaux
 */


#ifndef TRANSITION_HPP_
#define TRANSITION_HPP_

#include "Fraction.hpp"
#include "State.hpp"
#include "Guard.hpp"
#include "MyList.h"
#include <list>
#include <string>

using namespace std;

/*
 * Class Transition
 * To define a transition with two states (origin and destination), a guard, a weight and
 * a bool to indicate if the clock is reset.
 */
class Transition{
private:
	State* origin;
	State* destination;
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
	Transition();
    Transition(Transition* transition);
    // Constructor to build a transition from origin to destination with parameter attributes.
	Transition(State* origin, int weight, Guard guard, bool reset, State* destination, string label);
    // Constructor to constraint a transition to a region (and create region state if is need)
    Transition(Transition* transition, Region* reg_orign, Region* reg_dest, string new_label);

    // Destructors
	~Transition();


	// Getters
	State* getOrigin();
	State* getDestination();
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
    Transition* copy();


	// Operators
    bool operator==(const Transition& fraction) const;


    // Display function
    void show();
    string toString();
};

#endif
