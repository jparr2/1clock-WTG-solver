/*
 * Author: Julie Parreaux
 */


#include "Fraction.hpp"
#include <iostream>

using namespace std;

/*
 * Constructors
 */
Fraction::Fraction() : num(0), den(1), infinite(false){}
Fraction::Fraction(int i, int j){
    if (j == 0) {
        throw "Fraction constructor : do not built a fraction that divide by 0";
    }
	num = i;
	den = j;
	infinite = false;
	reduce();

}
Fraction::Fraction(int n){
    num = n;
    den = 1;
    infinite = false;
}
Fraction::Fraction(bool sign){
    den = 1;
    infinite = true;
    if (sign)
        num = 1;
    else
        num = -1;
}

/*
 * Getters
 */
bool Fraction::Fraction::isInfinite() const {
    return infinite;
}
int Fraction::getDenominator() const {
    return den;
}
int Fraction::getNumerator() const {
    return num;
}
bool Fraction::isInt() const {
    return (den == 1);
}
bool Fraction::isPositive(){
    Fraction zero = Fraction();
    return (zero < *this);
}
bool Fraction::isNegative(){
    Fraction zero = Fraction();
    return (zero > *this);
}
bool Fraction::isZero(){
    Fraction zero = Fraction();
    return (zero == *this);
}

/*
 * Operators
 */
Fraction& Fraction::operator=(const Fraction &fraction){
	num = fraction.num;
	den = fraction.den;
    infinite = fraction.infinite;

	reduce();
	return *this;
}
Fraction Fraction::operator+(int i){
    Fraction add = (*this + Fraction(i));
    add.reduce();
    return add;
}
Fraction Fraction::operator+(Fraction fraction){
    Fraction sum;

	if(infinite && fraction.infinite) {
        if (num == fraction.num)
            return *this;
        else
            throw "Fraction : Sum of infinity of different sign";
    }
	if(infinite)
	    return *this;
	if (fraction.infinite)
	    return fraction;

    sum.num = fraction.num * den + fraction.den * num;
    sum.den = fraction.den * den;
    sum.reduce();

    return sum;
}
Fraction Fraction::operator-() const{
    Fraction minus;
    minus.num = -num;
    minus.den = den;
    minus.infinite = infinite;
    return minus;
}
Fraction Fraction::operator-(int n){
    Fraction minus = (*this - Fraction(n));
    minus.reduce();
    return minus;
}
Fraction Fraction::operator-(Fraction fraction){
	Fraction minus;
    if(infinite && fraction.infinite) {
        if (num == -fraction.num)
            return *this;
        else
            throw "Fraction : Sum of infinity of different sign";
    }
    if(infinite)
        return *this;
    if(fraction.infinite) {
        minus.num = -fraction.num;
        minus.infinite = true;

        minus.reduce();
        return minus;
    }

    minus.num = num * fraction.den - den * fraction.num;
    minus.den = fraction.den * den;
    minus.reduce();

    return minus;
}
Fraction Fraction::operator*(Fraction fraction) const{
    Fraction product;
    if ((infinite || fraction.infinite) && (fraction.num == 0 || num == 0))
        throw "Fraction : Product of infinity with 0";
    if (infinite || fraction.infinite) {
        product.num = num * fraction.num / abs(num * fraction.num);
        product.infinite = true;
        return  product;
    }

    product.den = den * fraction.den;
    product.num = num * fraction.num;

    product.reduce();
    return product;
}
Fraction Fraction::operator/(Fraction fraction) const{
	Fraction product = Fraction();

    if(infinite && fraction.infinite) {
        throw "Fraction : Divide infinity by infinite";
    }
    if(fraction.num == 0)
        throw "Fraction : Divide by 0";
    if(infinite){
        product.num = num * product.num;
        product.infinite = true;
        return product;
    }
    if(fraction.infinite)
        return product;

    product.num = num * fraction.den;
    product.den = den * fraction.num;

    product.reduce();
    return product;
}

bool Fraction::operator<(Fraction fraction) const{
    if (infinite && fraction.infinite)
        return (num < fraction.num);
    if  (infinite)
        return (num == -1);
    if (fraction.infinite)
        return (fraction.num == 1);
    return (num /(double) den) < (fraction.num /(double) fraction.den);
}
bool Fraction::operator <=(Fraction fraction) const{
    return (*this < fraction || *this == fraction);
}
bool Fraction::operator>(Fraction fraction) const{
   return !(*this <= fraction);
}
bool Fraction::operator >=(Fraction fraction) const{
    return (*this > fraction || *this == fraction);
}
bool Fraction::operator==(Fraction fraction) const{
    return ((num == fraction.num) && (den == fraction.den) && (infinite == fraction.infinite));
}
bool Fraction::operator!=(Fraction fraction) const{
    return !(*this == fraction);
}

/*
 * Cast functions
 */
int Fraction::asInt() const {
    if(infinite)
        throw "Fraction : asInt : infinite is not an int";
   if (den == 1)
       return num;
    return num/den + 1;
}
double Fraction::asDouble() const{
    if(infinite)
        throw "Fraction : asDouble : infinite is not a double";
    return num /(double) den;
}

/*
 * Display function
 */
void Fraction::show() const {
    if (infinite) {
        if (num > 0)
            cout << "+ infinite";
        else
            cout << "- infinite";
    }
    else {
        if (den == 1)
            cout << num;
        else
            cout << num << "/" << den;
    }
}
string Fraction::toString() {
    string result;
    if (infinite) {
        if (num == 1)
            result = "+ infinite";
        else
            result = "- infinite";
    }
    else {
        if (den == 1)
            result = num;
        else
            result = num + "/" + den;
    }
    return result;
}

/*
 * Private functions
 */
int Fraction::gcd(int i, int j){
    int tmp;
    if(i < j)
    {
        tmp = i;
        i = j;
        j = tmp;
    }
    while(j != 0)
    {
        tmp = i % j;
        i = j;
        j = tmp;
    }
    return i;
}
void Fraction::reduce(){
	int g = gcd(num,den);
	if(g != 0){
		num /= g;
		den /= g;
	}
	upperSign();
}
void Fraction::upperSign(){
	if(den < 0){
		num = - num;
		den = - den;
	}
}



/*
 * Comparators function
 */
Fraction minFraction(Fraction fraction1, Fraction fraction2){
    if (fraction1 < fraction2)
        return fraction1;
    return fraction2;
}
Fraction maxFraction(Fraction fraction1, Fraction fraction2){
    if (fraction1 > fraction2)
        return fraction1;
    return fraction2;
}

bool containsFraction(list<Fraction>* fractions, Fraction fraction){
    bool result = false;
    for (auto frac : *fractions){
        result |= (frac == fraction);
    }
    return result;
}
bool equalListFrac(list<Fraction>* fractions1, list<Fraction>* fractions2){
    for (auto fraction : *fractions1){
        if (!containsFraction(fractions2, fraction))
            return false;
    }
    for (auto fraction : *fractions2){
        if (!containsFraction(fractions1, fraction))
            return false;
    }
    return true;
}
void showListFrac(list<Fraction>* fractions){
    cout << "{";
    for (auto fraction : *fractions){
        fraction.show();
        cout << ",";
    }
    cout << "}" << endl;
}



