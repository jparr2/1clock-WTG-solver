/*
 * Author : Julie Parreaux
 */

#ifndef CODE_FONCTION_H
#define CODE_FONCTION_H

#include <list>
#include <vector>
#include "Line.hpp"

/*
 * Class Function
 * Define piecewise affine function as a list of affine line and a list of cutpoints.
 */
class Function{
private:
    list<Line>* affineLine;
    list<Point>* cutpoints;
    Point start;
    Point end;
    bool min;


    // Functions to constructors

    // Compute the list of intersection points given by affineLine.
    list<Point>* getIntersectionLines();
    // Compute the list of affine lines given by the list of cutpoints.
    list<Line>* getLinePoint();
    /*
     * Choose the minimal/maximal value point for each clock value from pointsList.
     * We suppose that pointsList is sorted
     */
    static list<Point>* choicePoint(list<Point>* pointsList, bool min);
    // Compute the value on clock of the function according to min without see the bounds
    Point getPointStart();
    Point getPointEnd();
    void getBoundLines();

    // Functions to getValue
    Fraction minValue(const Fraction& clock);
    Fraction maxValue(const Fraction& clock);

    // Functions to getLinePoint
    Line getLineMinPoint(Fraction fraction);
    Line getLineMaxPoint(Fraction fraction);

public:
    // Constructors

    // Default constructor to build a function with any affine line and any cutpoints.
    Function();
    // Constructor to build a function f such that f(x) = intercept
    explicit  Function(Fraction intercept, Fraction maxClock);
    /*
     * Constructor to build the function from start to end describe by lines contain in
     * function according to min/max.
    */
    Function(list<Line>* function, bool min);
    // Constructor to build the function from a list of cutpoints according to min/max
    Function(list<Point>* cutpoints, bool min);

    // Destructor
    ~Function();

    // Getters
    list<Point>* getFunctionPoint() const;
    list<Line>* getFunctionLine();
    Point getStart();
    Point getEnd();

    // Get the point in cutpoints with clock as x-coordinate, if exist
    Point getPointClock(const Fraction& clock);
    // Compute the value for clock by this
    Fraction getValueClock(const Fraction& clock);
    /*
     * Compute the next cutpoint for this
     * If clock is greater than clock, it returns the point (+infinite, +infinite)
    */
    Point nextPoint(Fraction clock);
    // Get the line which compute the value in clock.
    Line getLinePoint(Fraction clock);

    // Operators
    Function& operator=(const Function& function);
    bool operator==(const Function& function) const;
    bool operator!=(const Function& function) const;


    // Test element functions

    // Test if cutpoints contains a point with clock as x-coordinate
    bool containsPoint(Fraction clock) const;
    // Test if cutpoints contains point
    bool containsValuePoint(Point &point) const;

    // Display function
    void show(bool here);

};

// Comparison of two functions

// Compute the function that is the minimum between function1 and function2
Function* minFunction(Function* function1, Function* function2);
// Compute the function that is the maximum between function1 and function2
Function* maxFunction(Function* function1, Function* function2);

#endif //CODE_FONCTION_H
