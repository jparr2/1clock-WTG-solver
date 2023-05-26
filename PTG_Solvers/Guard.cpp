/*
 * Author : Julie Parreaux
 */

#include "Guard.hpp"

/*
 * Constructors
 */
Guard::Guard() {
    startValue = Fraction(false);
    endValue = Fraction(true);
    startType = true;
    endType = true;
}
Guard::Guard(Fraction start, Fraction end) {
    if(start.isInfinite() && !end.isInfinite())
        throw "Guard : only for no guards";
    if(!start.isInfinite() && end.isInfinite())
        throw "Guard : only for no guards";
    if(start.isInfinite() && end.isInfinite() && start == end)
        throw "Guard : only for no guards";
    if(start > end)
        throw "Guard : ordnance bound";
    if(start.isNegative())
        throw "Guard : bad format for lower-bound";
    startValue = start;
    endValue = end;
    startType = true;
    endType = true;
}
Guard::Guard(Fraction valueStart, Fraction valueEnd, bool typeStart, bool typeEnd) {
    if(valueStart.isInfinite() && !valueEnd.isInfinite())
        throw "Guard : only for no guards";
    if(!valueStart.isInfinite() && valueEnd.isInfinite())
        throw "Guard : only for no guards";
    if(valueStart.isInfinite() && valueEnd.isInfinite() && valueStart == valueEnd)
        throw "Guard : only for no guards";
    if(valueStart > valueEnd)
        throw "Guard : ordnance bound";
    if(valueStart == valueEnd && (!typeStart || !typeEnd))
        throw "Guard : bad format for singleton";
    if(valueStart.isNegative())
        throw "Guard : bad format for lower-bound";
    startValue = valueStart;
    endValue = valueEnd;
    startType = typeStart;
    endType = typeEnd;
}
Guard::Guard(Guard guard, Region dest_region) {
    if (guard.getEndValue().asInt() < dest_region.getInf() ||
        guard.getStartValue().asInt() > dest_region.getSup())
        throw "Guard : empty";
    startType = true;
    endType = true;
    if (guard.getStartValue() < Fraction(dest_region.getInf())) {
        startValue = Fraction(dest_region.getInf());
        if (guard.getEndValue() < Fraction(dest_region.getSup()))
            endValue = guard.getEndValue();
        else
            endValue = Fraction(dest_region.getSup());
    }
    else {
        startValue = guard.getStartValue();
        if (guard.getEndValue() < Fraction(dest_region.getSup()))
            endValue = guard.getEndValue();
        else
            endValue = Fraction(dest_region.getSup());
    }
}

/*
 * Getters
 */
Fraction Guard::getStartValue() {
    return startValue;
}
Fraction Guard::getEndValue() {
    return endValue;
}
bool Guard::isStartOpen() const {
    return startType;
}
bool Guard::isEndOpen() const {
    return endType;
}
bool Guard::isEmpty() {
    return startValue.isInfinite();
}
bool Guard::isModel(Fraction clock) {
    bool model = true;
    if (startType)
        model &= (clock >= startValue);
    else
        model &= (clock > startValue);
    if (endType)
        model &= (endValue >= clock);
    else
        model &= (endValue > clock);
    return model;
}
bool Guard::isInClosedInterval(Fraction clock) {
    return startValue <= clock && clock <= endValue;
}
bool Guard::isInInterval(Fraction clock) {
    bool result = true;
    if (startType){result &= (startValue <= clock);}
    else {result &= (startValue < clock);}
    if (endType){result &= (clock <= endValue);}
    else {result &= (clock < endValue);}
    return result;
}


/*
 * Operator
 */
bool Guard::operator==(Guard guard) const {
    return (startValue == guard.startValue && startType == guard.startType &&
            endValue == guard.endValue && endType == guard.endType);
}

/*
 * Display function
 */
void Guard::show() {
    if (startType)
        cout << "[";
    else
        cout << "(";
    startValue.show();
    cout << "; ";
    endValue.show();
    if (endType)
        cout << "]";
    else
        cout << ")";
}
string Guard::toString() {
    string result = "";
    if (startType)
        result += "[";
    else
        result += "(";
    result += startValue.toString() < "; " + endValue.toString();
    if (endType)
        result += "]";
    else
        result += ")";
    return  result;
}

bool Guard::isReachable(Region region) {
    return (Fraction(region.getInf()) <= endValue);
}



