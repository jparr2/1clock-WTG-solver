/*
 * Author : Julie Parreaux
 */
// TODO: fuite memoire

#include "Line.hpp"

/*
 * Constructor
 */
Line::Line() {
    slope = Fraction();
    intercept = Fraction();
    start = Fraction();
    end = Fraction(true);
    keep = false;
}
Line::Line(const Fraction& slope1, const Fraction& intercept1, const Fraction& start1, const Fraction& end1) {
    if (slope1.isInfinite())
        throw "Line : a line has not an infinite slope";
    slope = slope1;
    intercept = intercept1;
    start = start1;
    end = end1;
    keep = false;
}
Line::Line(Point start1, Point end1) {
    start = start1.getClock();
    end = end1.getClock();
    slope = (end1.getValue() - start1.getValue())/(end1.getClock() - start1.getClock());
    intercept = start1.getValue() - slope * start1.getClock();
    keep = false;
}

/*
 * Getters
 */
Fraction Line::getSlope() {return slope;}
Fraction Line::getIntercept() {return intercept;}
Fraction Line::getStart() {return start;}
Fraction Line::getEnd() {return end;}
Fraction Line::getValueClock(const Fraction& clock) {
    if (clock.isInfinite() && slope.isZero()){
        return intercept;
    }
    return (slope * clock + intercept);}
bool Line::isSingletonDomain() {return start == end;}
bool Line::isKeep() {return keep;}
/*
 * Setters
 */
void Line::setStart(Fraction clock) {start = clock;}
void Line::setEnd(Fraction clock) {end = clock;}
void Line::setKeep(bool new_keep) {keep = new_keep;}
/*
 * Operators
 */
bool Line::operator==(Line line) const {
    return (line.slope == slope && line.intercept == intercept &&
    line.start == start && line.end == end);
}
bool Line::operator!=(Line line) const {return !(*this == line);}
bool Line::operator<(Line line) const {return start < line.start;}

/*
 * Comparison between lines
 */
bool Line::isSameLine(const Line& line){
    return (slope == line.slope && line.intercept == intercept);
}
bool Line::isParallel(const Line& line) {return slope == line.slope;}
bool Line::isDomainIntersect(const Line& line){
    return maxFraction(line.start, start) < minFraction(line.end, end);
}
bool Line::isInteriorDomainClock(Fraction clock){
    return (start < clock && clock < end);
}
Point Line::getIntersectionPoint(Line line) {
    Fraction lineSlope = line.getSlope();
    Fraction lineIntercept = line.getIntercept();
    if (slope == lineSlope || intercept.isInfinite() || lineIntercept.isInfinite())
        return Point(Fraction(true), Fraction(true));
    Fraction intersectionClock = (lineIntercept - intercept) / (slope - lineSlope);
    Fraction intersectionValue = slope * intersectionClock + intercept;
    return Point(intersectionClock, intersectionValue);
}
Line Line::selectLine(const Line& line, bool min) {
    if (min)
        return selectMinLine(line);
    return selectMaxLine(line);
}

/*
 * Display function
 */
void Line::show() {
    cout << "( (" ;
    if (!slope.isZero()) {
        if (slope != Fraction(1))
            slope.show();
        cout << " x ";
    }
    if (intercept.isPositive() || intercept.isZero())
        cout << "+ ";
    intercept.show();
    cout << "), ";
    start.show();
    cout << ", ";
    end.show();
    cout << ")";
}

/*
 * Private functions
 */
Line Line::selectMinLine(Line line) {
    if (getValueClock(start) < line.getValueClock(start) ||
        (getValueClock(start) == line.getValueClock(start) &&
        getValueClock(end) < line.getValueClock(end)))
        return *this;
    return line;
}
Line Line::selectMaxLine(Line line) {
    if (getValueClock(start) > line.getValueClock(start) ||
        (getValueClock(start) == line.getValueClock(start) &&
        getValueClock(end) > line.getValueClock(end)))
        return *this;
    return line;
}

bool Line::isDomainContinue(Line line) {
    return (line.getStart() <= start && start <= line.getEnd());
}

/*
 * Functions on list of points
 */
bool containsLine(list<Line>* linesList, Line& line1){
    bool result = false;
    for (Line& line : *linesList)
        result |= (line == line1);
    return result;
}
bool equalListLine(list<Line>* linesList1, list<Line>* linesList2){
    bool result = true;
    for (auto& line : *linesList1){
        result &= containsLine(linesList2, line);
    }
    for (auto& line : *linesList2){
        result &= containsLine(linesList1, line);
    }
    return result;
}
void showListLine(list<Line>* linesList) {
    cout << "{";
    for (auto line : *linesList){
        line.show();
        cout << ", ";
    }
    cout << "}" << endl;
}

list<Line>* selectLine(list<Line>* linesList, bool min) {
    auto result = new list<Line>();
    if ((min && isAllInfinite(linesList, true)) || (!min && isExistInfinite(linesList, true))){
        result->push_front(linesList->front());
        return result;
    }
    if ((min && isExistInfinite(linesList, false)) || (!min && isAllInfinite(linesList, false))){
        result->push_front(linesList->front());
        return result;
    }
    auto* tmp = divideLine(linesList);
    for (auto line1 : *tmp){
        if (!line1.isSingletonDomain()) {
            bool applicant = !line1.getIntercept().isInfinite();
            for (auto line2 : *tmp) {
                if (line2 != line1 && line1.isDomainIntersect(line2)) {
                    Point pointTmp = line1.getIntersectionPoint(line2);
                    if (!line1.isInteriorDomainClock(pointTmp.getClock()))
                        applicant &= (line1.selectLine(line2, min) == line1);
                }
            }
            if (applicant && !containsLine(result, line1)){
                result->push_front(line1);
                line1.setKeep(true);
            }
        }
    }
    //cleanListLine(tmp);
    //setAllNotKeep(tmp);
    tmp->clear();
    delete tmp;
    result->sort();
    auto* result2 = mergeListLine(result);
    result->clear();
    delete result;
    return result2;
}
list<Line>* divideLine(list<Line> *linesList) {
    auto* result = new list<Line>();
    auto* listBound = getBoundListLines(linesList);
    for (auto & line : *linesList){
        Line line_copy = Line(line.getSlope(), line.getIntercept(), line.getStart(), line.getEnd());
        for (auto & bound : *listBound){
            if (line_copy.getStart() < bound && bound <= line_copy.getEnd()){
                Line tmp = Line(line_copy.getSlope(), line_copy.getIntercept(), line_copy.getStart(), bound);
                if (!containsLine(result, tmp))
                    result->push_front(tmp);
                line_copy.setStart(bound);
            }
        }
    }
    listBound->clear();
    delete listBound;
    return result;
}
list<Fraction>* getBoundListLines(list<Line> *linesList) {
    auto* result = new list<Fraction>();
    for (auto& line : *linesList){
        if(!containsFraction(result, line.getStart()))
            result->push_front(line.getStart());
        if(!containsFraction(result, line.getEnd()))
            result->push_front(line.getEnd());
    }
    result->sort();
    return  result;
}
list<Line>* mergeListLine(list<Line>* linesList) {
    auto* result = new list<Line>();
    for (auto& line1 : * linesList){
        for (auto& line2 : * linesList){
            if (line1.isSameLine(line2) && (line1.isDomainContinue(line2) || line2.isDomainContinue(line1))){
                line1.setStart(minFraction(line1.getStart(), line2.getStart()));
                line1.setEnd(maxFraction(line1.getEnd(), line2.getEnd()));
            }
        }
        if (!containsLine(result, line1)) {
            result->push_front(line1);
            line1.setKeep(true);
        }
    }
    //cleanListLine(linesList);
    //setAllNotKeep(linesList);
    return result;
}

bool isAllInfinite(list<Line>* lineList, bool sign){
    Fraction infinite = Fraction(sign);
    bool result = true;
    for (auto & line : *lineList)
        result &= line.getIntercept() == infinite;
    return result;
}
bool isExistInfinite(list<Line>* lineList, bool sign){
    Fraction infinite = Fraction(sign);
    bool result = false;
    for (auto & line : *lineList)
        result |= line.getIntercept() == infinite;
    return result;
}

void cleanListLine(list<Line>* lineList){
    for (auto line : *lineList){
        if (line.isKeep())
            lineList->remove(line);
    }
}
void setAllNotKeep(list<Line>* lineList){
    for (auto line : *lineList){
       line.setKeep(false);
    }
}