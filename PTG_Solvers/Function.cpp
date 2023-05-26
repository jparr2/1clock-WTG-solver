/*
 * Author : Julie Parreaux
 */

#include "Function.hpp"
#include "iostream"

using namespace std;

/*
 * Constructors
 */
Function::Function(){
    affineLine = new list<Line>();
    cutpoints = new list<Point>();
    start = Point();
    end = Point();
    min = true;
}
Function::Function(Fraction intercept, Fraction maxClock) {
    min = true;

    cutpoints = new list<Point>();
    cutpoints->push_back(Point(Fraction(), intercept));
    cutpoints->push_back(Point(maxClock, intercept));

    affineLine = new list<Line>();
    Line line = Line(Fraction(), intercept, Fraction(), maxClock);
    affineLine->push_back(line);

    start = cutpoints->front();
    end = cutpoints->back();
}
Function::Function(list<Line>* function1, bool min1) {
    min = min1;
    affineLine = selectLine(function1, min1);
    affineLine->sort();
    cutpoints = getIntersectionLines();
    getBoundLines();
    start = cutpoints->front();
    end = cutpoints->back();
}
Function::Function(list<Point>* cutpoints1, bool min1) {
    cutpoints1->sort();
    cutpoints = choicePoint(cutpoints1, min1);
    affineLine = getLinePoint();
    start = cutpoints1->front();
    end = cutpoints1->back();
    min = min1;
}

/*
 * Destructor
 */
Function::~Function() {
    if (affineLine != nullptr) {
        affineLine->clear();
        delete affineLine;
    }
    if (cutpoints != nullptr) {
        cutpoints->clear();
        delete cutpoints;
    }
    affineLine = nullptr;
    cutpoints = nullptr;
}

/*
 * Getters
 */
list<Point>* Function::getFunctionPoint() const {return cutpoints;}
list<Line>* Function::getFunctionLine() {return affineLine;}
Point Function::getStart() {return start;}
Point Function::getEnd() {return end;}

Point Function::getPointClock(const Fraction& clock) {
    for(auto & point : *cutpoints){
        if(point.getClock() == clock)
            return point;
    }
    throw "Function : any point with this clock";
}
Fraction Function::getValueClock(const Fraction& clock) {
    if(clock < start.getClock() || clock > end.getClock()) {
        start.show();
        clock.show();
        end.show();
        throw "Function : getValue : clock is not in the domain : ";
    }
    else {
        if (min)
            return minValue(clock);
        else
            return maxValue(clock);
    }
}
Point Function::nextPoint(Fraction clock) {
    auto it=cutpoints->begin();
    while(it->getClock() <= clock && it!=cutpoints->end())
        ++it;
    if (it->getClock() <= clock)
        return Point(Fraction(true), Fraction(true));
    return *it;
}
Line Function::getLinePoint(Fraction clock) {
    if (min)
        return getLineMinPoint(clock);
    return getLineMaxPoint(clock);
}

/*
 * Operators
 */
Function& Function::operator=(const Function &function) = default;
bool Function::operator==(const Function& function) const {
    for(auto & point : *cutpoints){
        if(!function.containsValuePoint(point))
            return false;
    }
    for(auto & point : *function.getFunctionPoint()) {
        if (!this->containsValuePoint(point))
            return false;
    }
    return true;
}
bool Function::operator!=(const Function & function) const {
    for(Point point : *cutpoints){
        if(!function.containsValuePoint(point))
            return true;
    }
    for(Point point : *function.getFunctionPoint()) {
        if (!this->containsValuePoint(point))
            return true;
    }
    return false;
}

/*
 * Test element functions
 */
bool Function::containsPoint(Fraction clock) const {
    for(auto& point : *cutpoints){
        if(point.getClock() == clock) {
            return true;
        }
    }
    return false;
}
bool Function::containsValuePoint(Point &point) const {
    for(Point cutpoint : *cutpoints){
        if(point == cutpoint) {
            return true;
        }
    }
    return false;
}

/*
 * Display function
 */
void Function::show(bool here) {
    if (here) {
        if (cutpoints != nullptr) {
            cout << "Function : " << endl << "cutpoints : ";
            showListPoint(cutpoints);
        }
        else
            cout << "cutpoints empty";
        if (affineLine != nullptr) {
            cout << "lines : ";
            showListLine(affineLine);
        }
        else
            cout << "line empty";
    } else {
        if (cutpoints != nullptr)
            showListPoint(cutpoints);
    }
}

/*
 * Functions to constructors
 */
list<Point>* Function::getIntersectionLines() {
    auto* result = new list<Point>();
    for(auto it1=affineLine->begin(); it1 != affineLine->end(); ++it1){
        Fraction line1Start = it1->getStart();
        auto it2=it1;
        for(++it2; it2!=affineLine->end(); ++it2){
            Fraction line2Start = it2->getStart();
            Point tmp = it1->getIntersectionPoint(*it2);
            if (it1->isInteriorDomainClock(tmp.getClock()) &&
                it2->isInteriorDomainClock(tmp.getClock())){
                result->push_back(tmp);
                if (min){
                    if (it1->getValueClock(line1Start) < it2->getValueClock(line2Start)){
                        it1->setEnd(tmp.getClock());
                        it2->setStart(tmp.getClock());
                    }
                    else {
                        it1->setStart(tmp.getClock());
                        it2->setEnd(tmp.getClock());
                    }
                }
                else {
                    if (it1->getValueClock(line1Start) > it2->getValueClock(line2Start)){
                        it1->setEnd(tmp.getClock());
                        it2->setStart(tmp.getClock());
                    }
                    else {
                        it1->setStart(tmp.getClock());
                        it2->setEnd(tmp.getClock());
                    }
                }
            }
        }
    }
    return result;
}
list<Line>* Function::getLinePoint() {
    auto* result = new list<Line>();
    for(auto it1=cutpoints->begin(); it1 != --(cutpoints->end()); ++it1){
        auto it2 = it1;
        Line tmp = Line(*it1, *(++it2));
        result->push_front(tmp);
    }
    return result;
}
list<Point>* Function::choicePoint(list<Point>* pointsList, bool min1) {
    auto* result = new list<Point>();
    if (!min1)
        pointsList->reverse();
    for (auto &point: *pointsList) {
        if (!(containsPointClock(result, point.getClock())))
            result->push_back(point);
    }
    result->sort();
    return result;
}
Point Function::getPointStart() {
    Fraction tmpStart = Fraction(true);
    Fraction tmpValue = Fraction(true);
    for (auto & line : *affineLine) {
        if (line.getStart() < tmpStart) {
            tmpStart = line.getStart();
            tmpValue = line.getValueClock(line.getStart());
        }
    }
    return Point(tmpStart, tmpValue);
}
Point Function::getPointEnd() {
    Fraction tmpEnd = Fraction(false);
    Fraction tmpValue = Fraction(false);
    for (auto & line : *affineLine) {
        if (line.getEnd() > tmpEnd) {
            tmpEnd = line.getEnd();
            tmpValue = line.getValueClock(line.getEnd());
        }
    }
    return Point(tmpEnd, tmpValue);
}
void Function::getBoundLines() {
    for (auto& line : *affineLine){
        if(!containsPointClock(cutpoints, line.getStart())) {
            Point tmp = Point(line.getStart(), line.getValueClock(line.getStart()));
            cutpoints->push_front(tmp);
        }
        if(!containsPointClock(cutpoints, line.getEnd())) {
            cutpoints->push_front(Point(line.getEnd(), line.getValueClock(line.getEnd())));
        }
    }
    cutpoints->sort();
}

/*
 * Functions to getValue
 */
Fraction Function::minValue(const Fraction& clock) {
    Fraction fracMin = Fraction(true);
    for(auto & line : *affineLine){
        if (line.getStart() <= clock && clock <= line.getEnd()) {
            Fraction tmp = line.getValueClock(clock);
            Fraction minTmp = minFraction(tmp, fracMin);
            fracMin = minTmp;
        }
    }
    return fracMin;
}
Fraction Function::maxValue(const Fraction& clock) {
    Fraction fracMax = Fraction(false);
    for(auto & line : *affineLine){
        if (line.getStart() <= clock && clock <= line.getEnd()) {
            Fraction tmp = line.getValueClock(clock);
            Fraction maxTmp = maxFraction(tmp, fracMax);
            fracMax = maxTmp;
        }
    }
    return fracMax;
}

/*
 * Functions to getLinePoint
 */
Line Function::getLineMinPoint(Fraction clock) {
    Fraction valueMin = Fraction(true);
    Line lineMin = Line();
    for (auto & line : *affineLine) {
        if (valueMin > line.getValueClock(clock)) {
            valueMin = line.getValueClock(clock);
            lineMin = line;
        }
        if (valueMin == line.getValueClock(clock) && line.getSlope() < lineMin.getSlope())
            lineMin = line;
    }
    return lineMin;
}
Line Function::getLineMaxPoint(Fraction clock) {
    Fraction valueMax = Fraction(false);
    Line lineMax = Line();
    for (auto & line : *affineLine) {
        if (valueMax < line.getValueClock(clock)) {
            valueMax = line.getValueClock(clock);
            lineMax = line;
        }
        if (valueMax == line.getValueClock(clock) && line.getSlope() > lineMax.getSlope())
            lineMax = line;
    }
    return lineMax;
}

/*
 * Comparison of two functions
 */
Function* minFunction(Function* function1, Function* function2) {
    list<Line>* functionTmp = function1->getFunctionLine();
    for (auto& line : *function2->getFunctionLine())
        functionTmp->push_front(line);
    delete function2;
    auto* result = new Function(functionTmp, true);
    functionTmp->clear();
    //delete functionTmp;
    return result;
}
Function* maxFunction(Function* function1, Function* function2) {
    list<Line>* functionTmp = function1->getFunctionLine();
    for (auto& line : *function2->getFunctionLine())
        functionTmp->push_front(line);
    delete function2;
    //delete function1;
    auto* result = new Function(functionTmp, false);
    functionTmp->clear();
    //delete functionTmp;
    return result;
}





