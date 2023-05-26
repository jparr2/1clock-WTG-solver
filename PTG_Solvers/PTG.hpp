/*
 * Author: Julie Parreaux
 */


#ifndef PTG_HPP_
#define PTG_HPP_

#include "Fraction.hpp"
#include "Guard.hpp"
#include "State.hpp"
#include "Transition.hpp"
#include "Region.h"
#include <iostream>
#include <fstream>
#include <set>
#include "MyList.h"

using namespace std;

/*
 * Class PTG
 * To define Priced Timed Games with lists of states and transitions.
 */
class PTG{
protected:
    MyList<State>* states;
    MyList<Transition>* transitions;
    int size;
    int nb_transition;

private:
    // Auxilary function for constructor : parse
    static int removeWhite(string::iterator itString, string line);
    static pair<int, string> getString(string::iterator itString, const string& line);
    static pair<int, int> getInt(string::iterator itString, const string& line, char c);
    static pair<int, Guard> getGuard(string::iterator itString, const string& line);
    static pair<int, bool> getBool(string::iterator itString, const string& line);
    static pair<int, Fraction> getFraction(string::iterator itString, const string& line);

    static State* buildState(string::iterator itString, const string& line);
    Transition* buildTransition(string::iterator itString, const string& line);

    set<int>* getConstantClock();

public:
    // Constructors

    // Default constructor to build an empty PTG.
	PTG();
    /*
     * Constructor to build a PTG from a txt file.
     * If the file doesn't exist, do nothing.
     */
	PTG(const string& f);
    PTG(MyList<Transition>* cycle, Transition trans);

	// Destructor
    ~PTG();


    // Getters
    MyList<State>* getStates();
    // Get the state named label if exist.
    State* getAState(const string& label);
    // Test if a state named label exist.
    bool containsState(const string& label) const;

    MyList<Transition>* getTransitions();
    // Get the transition from origin to destination if exist.
    Transition getATransition(const string& origin, const string& destination);
    // Test if a transition from origin to destination exist.
    bool containsTransitions(const string& origin, const string& destination);
    // Get the list of transitions from origin.
    MyList<Transition>* getTransitionsState(const string& origin);

    int getSize() const;
    int getMaxClock();
    set<Region>* getRegions();
    int getMaxWeightLoc();
    int getMaxWeightTrans();
    Fraction getMaxWeightFin();

    // Setters
	void addState(State* state);
	void addTransition(Transition* transition);
	// Allow all states to be show.
	void setStatesShow();
	// Allow state named stateLabel to be show.
	void setAStateShow(const string& stateLabel);
	// Copy the temporal value in the current value.
	void updateValueStates();


	// Display functions
	void show();
	// Display all value functions.
	void showValues(bool here);


};

#endif
