/*
 * Author: Julie Parreaux
 */


#ifndef POINT_HPP_
#define POINT_HPP_

#include "Fraction.hpp"
#include <list>

/*
 * Class Point :
 * Defined points in R^2 with Fraction coordinates.
 * It modelled cutpoint of value function
 */
class Point{
private:
	Fraction clock;
	Fraction value;

public:
    //Constructors

    // Default constructor to build (0, 0)
	Point();
    // Constructor to build (cl, val)
	Point(Fraction cl, Fraction val);

	// Getters
    Fraction getClock() const;
    Fraction getValue() const;
    bool getInfinite() const;

    // Operators
	Point& operator=(const Point& point);
    bool operator==(Point point) const;
    bool operator!=(Point point) const;
    bool operator <(Point point) const;
    bool operator <=(Point point) const;
    bool operator >(Point point) const;
    bool operator >=(Point point) const;

    // Display function
	void show();
};


//Functions on list of points

// Test if point is in pointsList
bool containsPoint(list<Point>* pointsList, const Point& point1);
// Test if there exists a point with clock as x-coordinate in pointsList
bool containsPointClock(list<Point>* pointsList, Fraction clock);
// Test if all elements of pointsList1 are in pointsList2 and vise-versa
bool equalListPoint(list<Point>* pointsList1, list<Point>* pointsList2);
// Display a list of points
void showListPoint(list<Point>* points);


#endif
