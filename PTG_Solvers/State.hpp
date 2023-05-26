/*
 * Author : Julie Parreaux
 */

#ifndef CODE_STATE_HPP
#define CODE_STATE_HPP

#include <string>
#include "Function.hpp"
#include "Region.h"
#include "Owner.h"

using namespace std;


/*
 * Class State
 * Define a state with an unique name, a weight and an owner.
 * Moreover, all states have an associated value function.
 */
class State{

private:
    string label;
    Owner owner;
    Region* region;
    int weight;

    //Function of value attributs
    Function* value;
    Function* tmpValue;

    //Parameters attributs
    bool isshow;
    bool isused;

public:
    // Constructors

    // Default constructor to define a target state named lf.
    State();
    /*
     * Constructor to define a state where parameters give attributes of the State.
     * Each type of State has an initial value (0 if Target, +infinite otherwise).
     */
    State(string label, Owner owner, int weight, Fraction finalWeight);
    State(State* state);

    //Constructors to define a region state, i.e. a state where the region is not [0, +\infty)
    State(string label, Owner owner, int weight, Fraction finalWeight, Region* region);
    State(State* state, Region* reg);


    // Destructor
    ~State();

    // Getters
    string getLabel();
    int getWeight() const;
    Fraction getFinalWeight(); // Only if the state is a final state
    Owner getOwner();
    Function* getValueFunction();
    Function* getTmpValue();
    Region* getRegion();

    // Tester
    bool isMin();
    bool isMax();
    bool isTarget();
    bool isShow();
    bool isUsed();
    bool isRegion();


    // Setters
    void setValue(Function* newValue);
    void setTmpValue(Function* newTmpValue);
    void setShow(bool toShow);
    void setUpdateValue();
    void setUsed(bool isUsed);

    // Copy
    State* copy();

    // Operator
    bool operator==(const State&) const;

    // Display function
    void show();
    string toString();
};



#endif //CODE_STATE_HPP
