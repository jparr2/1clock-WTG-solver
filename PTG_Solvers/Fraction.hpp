/*
 * Author: Julie Parreaux
 */

#ifndef CODE_FRACTION_HPP
#define CODE_FRACTION_HPP

#include <iostream>
#include <list>
using namespace std;

/*
 * Class Fraction
 * Define elements of Q with +/- infinite, and their operators.
*/
class Fraction{
private:
    // If the fraction is infinite, num = +/-1 in function of its sign.
    int num;
    int den;
    bool infinite;

    // Compute the greatest common divisor between i and j
    static int gcd(int i, int j);
    // Compute the simple fraction
    void reduce();
    // Make a fraction with its sign on the numerator
    void upperSign();


public:
    // Constructors

    // Default constructor to build 0
	Fraction();
	// Constructor to build num / den
	Fraction(int num, int den);
	// Constructor to build n
	explicit Fraction(int n);
	/*
	 * Constructor to build an infinite fraction.
	 * Parameter : sign gives the sign of the infinite fraction that is positive
	 *                  when sign is true and negative otherwise
	*/
    explicit Fraction(bool sign);

	// Getters
	bool isInfinite() const;
    int getDenominator() const;
    int getNumerator() const;
    /*
     * Indicate if the fraction is an integer.
     * Remark: we consider infinite fraction as an integer.
     */
	bool isInt() const;
    bool isPositive();
    bool isNegative();
    bool isZero();

    // Operators (assignation, numerical, comparator)
	Fraction& operator=(const Fraction& fraction);
    Fraction operator+(int n);
	Fraction operator+(Fraction fraction);
    Fraction operator-() const;
    Fraction operator-(int n);
	Fraction operator-(Fraction fraction);
	Fraction operator*(Fraction fraction) const;
	Fraction operator/(Fraction fraction) const;
	bool operator<(Fraction fraction) const;
	bool operator<=(Fraction fraction) const;
	bool operator>(Fraction fraction) const;
	bool operator>=(Fraction fraction) const;
	bool operator==(Fraction fraction) const;
	bool operator!=(Fraction fraction) const;


	// Cast functions

	// Compute the closest greater integer for finite fraction
    int asInt() const;
    // Compute the double value corresponding to a finite fraction
    double asDouble() const;

    // Display function
    void show() const;
    string toString();
};

//Comparators function

// Compute the minimum between two fractions
Fraction minFraction(Fraction fraction1, Fraction fraction2);
// Compute the maximum between two fractions
Fraction maxFraction(Fraction fraction1, Fraction fraction2);

// List manipulation
bool containsFraction(list<Fraction>* fractions, Fraction fraction);
bool equalListFrac(list<Fraction>* fractions1, list<Fraction>* fractions2);
void showListFrac(list<Fraction>* fractions);

#endif
