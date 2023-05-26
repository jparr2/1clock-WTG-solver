/*
 * Author : Julie Parreaux
 */

#ifndef CODE_GUARDE_H
#define CODE_GUARDE_H

#include "Fraction.hpp"
#include "Region.h"

/*
 * Class Guard:
 * To define a guard as two Fraction value for start and end the guard, and two
 * bool to indicate if the guard is open or not.
 * If there are no guard, we use infinite value.
 */
class Guard {
private:
    Fraction startValue;
    Fraction endValue;
    bool startType;
    bool endType;

public:
    // Constructors

    // Default constructor to build an empty guard
    Guard();
    // Constructor to build a guard as a close interval from start to end
    Guard(Fraction start, Fraction end);
    /*
     * Constructor to build a gard as an interval from start to end with bound according
     * to typeStart et typeEnd.
     */
    Guard(Fraction valueStart, Fraction valueEnd, bool typeStart, bool typeEnd);
    Guard(Guard guard, Region dest_region);

    // Getters
    Fraction getStartValue();
    Fraction getEndValue();
    bool isStartOpen() const;
    bool isEndOpen() const;
    bool isEmpty();
    // Test if clock satisfies the guard.
    bool isModel(Fraction clock);
    bool isInClosedInterval(Fraction clock);
    bool isInInterval(Fraction clock);
    bool isReachable(Region region);

    // Operator
    bool operator==(Guard guard) const;

    // Display function
    void show();
    string toString();
};





#endif //CODE_GUARDE_H
