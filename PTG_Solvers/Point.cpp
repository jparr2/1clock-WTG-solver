/*
 * Author: Julie Parreaux
 */

#include "Point.hpp"
#include "iostream"

using namespace std;

/*
 * Constructors
 */

Point::Point() : clock() ,value()
{}
Point::Point(Fraction cl, Fraction val) : clock(cl), value(val)
{}

/*
 * Getters
 */
Fraction Point::getClock() const{
	return clock;
}
Fraction Point::getValue() const {
	return value;
}
bool Point::getInfinite() const{
	return value.isInfinite();
}

/*
 * Operators
 */
Point& Point::operator=(const Point &point){
    if(&point != this){
        clock = point.getClock();
        value = point.getValue();
    }
    return *this;
}
bool Point::operator==(Point point) const {
    return (point.getClock() == clock && point.getValue() == value);
}
bool Point::operator!=(Point point) const {
    return !(*this == point);
}
bool Point::operator<(Point point) const {
    return (clock < point.getClock() || (clock == point.getClock() && value < point.getValue()));
}
bool Point::operator<=(Point point) const {
    return (*this < point) || (point == *this);
}
bool Point::operator>(Point point) const {
    return !(*this <= point);
}
bool Point::operator>=(Point point) const {
    return (*this > point) || (*this == point);
}

/*
 * Display function
 */
void Point::show() {
    cout << "(";
    clock.show();
    cout << ", ";
    value.show();
    cout << ")";
}

/*
 * Functions on list of points
 */
bool containsPoint(list<Point>* pointsList, const Point& point1){
    bool result = false;
    for (auto & point : *pointsList)
        result |= (point == point1);
    return result;
}
bool containsPointClock(list<Point>* pointsList, Fraction clock) {
    bool result = false;
    for (auto & point : *pointsList)
        result |= (point.getClock() == clock);
    return result;
}
bool equalListPoint(list<Point>* pointsList1, list<Point>* pointsList2){
    bool result = true;
    for (auto & point : *pointsList1)
        result &= containsPoint(pointsList2, point);
    for (auto & point : *pointsList2)
        result &= containsPoint(pointsList1, point);
    return result;
}
void showListPoint(list<Point>* pointsList) {
    cout << "[" ;
    //int poi(ntsListLen = pointsList->size();
    auto it = pointsList->begin();
    it->show();
    for (++it; it != pointsList->end(); it++){
        cout << "; ";
        it->show();
    }
    cout << "]" << endl;
}
