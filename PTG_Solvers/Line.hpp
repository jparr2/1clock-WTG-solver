//
// Author : Julie Parreaux
//

#ifndef CODE_LINE_H
#define CODE_LINE_H

#include <list>
#include "Point.hpp"

/*
 * Class Line
 * Define affine line with a slope and an intercept or given by two points
 * between two points.
 */
class Line{
private:
    Fraction slope;
    Fraction intercept;
    Fraction start;
    Fraction end;
    bool keep;

    /*
     * Choose the minimal line between this and line.
     * We suppose that line and this do not intersect on an interval from 0.
     */
    Line selectMinLine(Line line);
    /*
    * Choose the maximal line between this and line.
    * We suppose that line and this do not intersect on an interval from 0.
    */
    Line selectMaxLine(Line);

public:
    // Constructors

    // Default constructor to build the zero line between 0 and +infinite
    Line();
    // Constructor to build the line : slope * x + intercept, between start and end
    Line(const Fraction& slope, const Fraction& intercept, const Fraction& start, const Fraction& end);
    // Constructor to build the line between start and end points
    Line(Point start, Point end);


    // Getters
    Fraction getSlope();
    Fraction getIntercept();
    Fraction getStart();
    Fraction getEnd();
    Fraction getValueClock(const Fraction& clock);
    bool isSingletonDomain();
    bool isKeep();


    // Setters
    void setStart(Fraction clock);
    void setEnd(Fraction clock);
    void setKeep(bool keep);


    // Operators
    bool operator==(Line line) const;
    bool operator!=(Line line) const;
    bool operator<(Line line) const;


    // Comparison between lines

    // Test if two lines are the same (with a different domain)
    bool isSameLine(const Line& line);
    // Test if two lines are parallels
    bool isParallel(const Line& line);
    // Test if the domain of the two lines are an intersection (is no a singleton).
    bool isDomainIntersect(const Line& line);
    bool isInteriorDomainClock(Fraction clock);
    // Test if the domain of this is in the continuity of the domain of line.
    bool isDomainContinue(Line line);
    /*
     * Compute the intersection point between the two lines.
     * If lines are parallels, the function returns the point (+infinity, +infinity).
     */
    Point getIntersectionPoint(Line line);
    /*
     * Choose between line and this the minimal line (if min) or the maximal line (otherwise).
     * We suppose that line and this do not intersect on an interval from start to end.
     */
    Line selectLine(const Line& line, bool min);

    // Display function
    void show();

};

// Functions on list of lines

// Test if line is in linesList.
bool containsLine(list<Line>* linesList, Line& line);
// Test if all line of linesList1 is in linesList2 and vise-versa.
bool equalListLine(list<Line>* linesList1, list<Line>* linesList2);
// Display a list of lines.
void showListLine(list<Line>* linesList);

// Choose minimal/maximal (according min) lines in linesList.
list<Line>* selectLine(list<Line>* linesList, bool min);
// Divide lines in linesList according the bound of all elements of linesList.
list<Line>* divideLine(list<Line>* linesList);
// Give all clock bounds of linesList
list<Fraction>* getBoundListLines(list<Line>* linesList);
// Merge domain of two elements of linesList when the lines are the same and their domains are continuous.
list<Line>* mergeListLine(list<Line>* linesList);

// Test if all lines in lineList are infinite (the sign is given by sign)
bool isAllInfinite(list<Line>* lineList, bool sign);
// Test if there exists a line in lineList such that is infinite (the sign is given by sign)
bool isExistInfinite(list<Line>* lineList, bool sign);

void cleanListLine(list<Line>* lineList);
void setAllNotKeep(list<Line>* lineList);
#endif //CODE_LINE_H
