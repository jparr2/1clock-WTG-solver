/*
 * Author : Julie Parreaux
 * Tests the Fraction class
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "./../PTG_Solvers/Fraction.hpp"

TEST_CASE("Constructor") {
    CHECK_THROWS_WITH(Fraction(1, 0), "Fraction constructor : do not built a fraction that divide by 0");
}

TEST_CASE("Getters") {
    Fraction frac0;
    Fraction frac1 = Fraction(2, 5);
    Fraction frac2 = Fraction(8, 16);
    Fraction frac4 = Fraction(5);
    Fraction frac5 = Fraction(11, -8);
    Fraction frac6 = Fraction(16, -8);
    Fraction fracInfPos = Fraction(true);
    Fraction fracInfNeg = Fraction(false);

    frac0.show();
    CHECK(frac0.getNumerator() == 0);
    CHECK(frac0.getDenominator() == 1);
    CHECK(!frac0.isInfinite());

    frac1.show();
    CHECK(frac1.getNumerator() == 2);
    CHECK(frac1.getDenominator() == 5);
    CHECK(!frac1.isInfinite());

    frac4.show();
    CHECK(frac4.getNumerator() == 5);
    CHECK(frac4.getDenominator() == 1);
    CHECK(!frac4.isInfinite());

    fracInfPos.show();
    CHECK(fracInfPos.getNumerator() == 1);
    CHECK(fracInfPos.getDenominator() == 1);
    CHECK(fracInfPos.isInfinite());

    fracInfNeg.show();
    CHECK(fracInfNeg.getNumerator() == -1);
    CHECK(fracInfNeg.getDenominator() == 1);
    CHECK(fracInfNeg.isInfinite());

    SUBCASE("Positif, Negatif, Zero, Integer") {
        CHECK(frac6.isInt());
        CHECK(frac0.isInt());
        CHECK(fracInfPos.isInt());
        CHECK_FALSE(frac1.isInt());
        CHECK_FALSE(frac2.isInt());

        CHECK(frac1.isPositive());
        CHECK_FALSE(frac5.isPositive());
        CHECK(fracInfPos.isPositive());
        CHECK_FALSE(fracInfNeg.isPositive());
        CHECK_FALSE(frac0.isPositive());

        CHECK_FALSE(frac1.isNegative());
        CHECK(frac5.isNegative());
        CHECK_FALSE(fracInfPos.isNegative());
        CHECK(fracInfNeg.isNegative());
        CHECK_FALSE(frac0.isNegative());

        CHECK_FALSE(frac1.isZero());
        CHECK_FALSE(frac5.isZero());
        CHECK_FALSE(fracInfPos.isZero());
        CHECK_FALSE(fracInfNeg.isZero());
        CHECK(frac0.isZero());
    }


}

TEST_CASE("Numerical operator"){
    Fraction frac;
    Fraction frac1 = Fraction(2, 5);
    Fraction frac2 = Fraction(8, 16);
    Fraction frac4 = Fraction(5);
    Fraction fracInfPos = Fraction(true);
    Fraction fracInfNeg = Fraction(false);
    Fraction frac0 = Fraction();

    SUBCASE("Addition") {
        frac = frac1 + frac2;
        CHECK(frac.getNumerator() == 9);
        CHECK(frac.getDenominator() == 10);
        CHECK(!frac.isInfinite());
        frac.show();

        frac = frac2 + frac4;
        CHECK(frac.getNumerator() == 11);
        CHECK(frac.getDenominator() == 2);
        CHECK(!frac.isInfinite());
        frac.show();

        frac = frac4 + fracInfPos;
        CHECK(frac.getNumerator() == 1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());
        frac.show();

        frac = frac4 + fracInfNeg;
        CHECK(frac.getNumerator() == -1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());
        frac.show();

        frac = fracInfPos + fracInfPos;
        CHECK(frac.getNumerator() == 1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());
        frac.show();

        frac = fracInfNeg + fracInfNeg;
        CHECK(frac.getNumerator() == -1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());
        frac.show();

        CHECK_THROWS_WITH(fracInfNeg + fracInfPos, "Fraction : Sum of infinity of different sign");
        CHECK_THROWS_WITH(fracInfPos + fracInfNeg, "Fraction : Sum of infinity of different sign");

        frac = frac2 + 5;
        CHECK(frac.getNumerator() == 11);
        CHECK(frac.getDenominator() == 2);
        CHECK(!frac.isInfinite());
        frac.show();

        frac = fracInfPos + 55;
        CHECK(frac.getNumerator() == 1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());
        frac.show();

        frac = fracInfNeg + 10;
        CHECK(frac.getNumerator() == -1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());
        frac.show();
    }

    SUBCASE("Subtraction") {
        frac = frac2 - frac1;
        CHECK(frac.getNumerator() == 1);
        CHECK(frac.getDenominator() == 10);
        CHECK(!frac.isInfinite());

        frac = frac2 - frac4;
        CHECK(frac.getNumerator() == -9);
        CHECK(frac.getDenominator() == 2);
        CHECK(!frac.isInfinite());

        frac = frac4 - fracInfPos;
        CHECK(frac.getNumerator() == -1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());

        frac = frac4 - fracInfNeg;
        CHECK(frac.getNumerator() == 1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());

        frac = fracInfPos - frac4;
        CHECK(frac.getNumerator() == 1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());

        frac = fracInfNeg - frac4;
        CHECK(frac.getNumerator() == -1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());

        frac = fracInfPos - fracInfNeg;
        CHECK(frac.getNumerator() == 1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());

        frac = fracInfNeg - fracInfPos;
        CHECK(frac.getNumerator() == -1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());

        CHECK_THROWS_WITH(fracInfPos - fracInfPos, "Fraction : Sum of infinity of different sign");
        CHECK_THROWS_WITH(fracInfNeg - fracInfNeg, "Fraction : Sum of infinity of different sign");

        frac = frac2 - 5;
        CHECK(frac.getNumerator() == -9);
        CHECK(frac.getDenominator() == 2);
        CHECK(!frac.isInfinite());

        frac = fracInfPos - 55;
        CHECK(frac.getNumerator() == 1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());

        frac = fracInfNeg - 10;
        CHECK(frac.getNumerator() == -1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());

        frac = -frac2;
        CHECK(frac.getNumerator() == -1);
        CHECK(frac.getDenominator() == 2);
        CHECK(!frac.isInfinite());

        frac = -fracInfPos;
        CHECK(frac.getNumerator() == -1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());

        frac = -fracInfNeg;
        CHECK(frac.getNumerator() == 1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());
    }

    SUBCASE("Multiplication"){
        frac = frac1 * frac2;
        CHECK(frac.getNumerator() == 1);
        CHECK(frac.getDenominator() == 5);
        CHECK(!frac.isInfinite());

        frac = frac2 * frac4;
        CHECK(frac.getNumerator() == 5);
        CHECK(frac.getDenominator() == 2);
        CHECK(!frac.isInfinite());

        frac = frac4 * fracInfPos;
        CHECK(frac.getNumerator() == 1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());

        frac = frac4 * fracInfNeg;
        CHECK(frac.getNumerator() == -1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());

        frac = fracInfPos * fracInfPos;
        CHECK(frac.getNumerator() == 1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());

        frac = fracInfNeg * fracInfNeg;
        CHECK(frac.getNumerator() == 1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());

        frac = fracInfPos * fracInfNeg;
        CHECK(frac.getNumerator() == -1);
        CHECK(frac.getDenominator() == 1);
        CHECK(frac.isInfinite());

        CHECK_THROWS_WITH(fracInfNeg * frac0, "Fraction : Product of infinity with 0");
        CHECK_THROWS_WITH(fracInfPos * frac0, "Fraction : Product of infinity with 0");
    }

    SUBCASE("Division"){
        frac = frac1 / frac2;
        CHECK(frac.getNumerator() == 4);
        CHECK(frac.getDenominator() == 5);
        CHECK(!frac.isInfinite());

        frac = frac2 / frac4;
        CHECK(frac.getNumerator() == 1);
        CHECK(frac.getDenominator() == 10);
        CHECK(!frac.isInfinite());

        frac = frac4 / fracInfPos;
        CHECK(frac.getNumerator() == 0);
        CHECK(frac.getDenominator() == 1);
        CHECK(!frac.isInfinite());

        frac = frac4 / fracInfNeg;
        CHECK(frac.getNumerator() == 0);
        CHECK(frac.getDenominator() == 1);
        CHECK(!frac.isInfinite());

        CHECK_THROWS_WITH(fracInfPos / fracInfPos, "Fraction : Divide infinity by infinite");
        CHECK_THROWS_WITH(fracInfNeg / fracInfNeg, "Fraction : Divide infinity by infinite");
        CHECK_THROWS_WITH(fracInfNeg / fracInfPos, "Fraction : Divide infinity by infinite");

        CHECK_THROWS_WITH(fracInfNeg / frac0, "Fraction : Divide by 0");
        CHECK_THROWS_WITH(frac1 / frac0, "Fraction : Divide by 0");
    }

}

TEST_CASE("Comparator operator"){
    Fraction frac1 = Fraction(2, 5);
    Fraction frac2 = Fraction(8, 16);
    Fraction frac3 = Fraction(2, 5);
    Fraction frac4 = Fraction(1, 1);
    Fraction fracInfPos = Fraction(true);
    Fraction fracInfNeg = Fraction(false);

    SUBCASE("Less"){
        CHECK(frac1 < frac2);
        CHECK_FALSE(frac4 < frac1);
        CHECK_FALSE(frac4 < frac4);
        CHECK(frac1 < fracInfPos);
        CHECK_FALSE(fracInfPos < frac1);
        CHECK_FALSE(fracInfPos < fracInfPos);
        CHECK(fracInfNeg < frac1);
        CHECK(fracInfNeg < fracInfPos);
        CHECK_FALSE(frac1 < fracInfNeg);
        CHECK_FALSE(fracInfNeg < fracInfNeg);
    }

    SUBCASE("Less or equal"){
        CHECK(frac1 <= frac2);
        CHECK_FALSE(frac4 <= frac1);
        CHECK(frac4 <= frac4);
        CHECK(frac1 <= fracInfPos);
        CHECK_FALSE(fracInfPos <= frac1);
        CHECK(fracInfPos <= fracInfPos);
        CHECK(fracInfNeg <= frac1);
        CHECK(fracInfNeg <= fracInfPos);
        CHECK_FALSE(frac1 <= fracInfNeg);
        CHECK(fracInfNeg <= fracInfNeg);
    }

    SUBCASE("Greater"){
        CHECK_FALSE(frac1 > frac2);
        CHECK(frac4 > frac1);
        CHECK_FALSE(frac4 > frac4);
        CHECK_FALSE(frac1 > fracInfPos);
        CHECK(fracInfPos > frac1);
        CHECK_FALSE(fracInfPos > fracInfPos);
        CHECK_FALSE(fracInfNeg > frac1);
        CHECK_FALSE(fracInfNeg > fracInfPos);
        CHECK(frac1 > fracInfNeg);
        CHECK_FALSE(fracInfNeg > fracInfNeg);
    }

    SUBCASE("Greater or equal") {
        CHECK_FALSE(frac1 >= frac2);
        CHECK(frac4 >= frac1);
        CHECK(frac4 >= frac4);
        CHECK_FALSE(frac1 >= fracInfPos);
        CHECK(fracInfPos >= frac1);
        CHECK(fracInfPos >= fracInfPos);
        CHECK_FALSE(fracInfNeg >= frac1);
        CHECK_FALSE(fracInfNeg >= fracInfPos);
        CHECK(frac1 >= fracInfNeg);
        CHECK(fracInfNeg >= fracInfNeg);
    }

    SUBCASE("Equality"){
        CHECK(frac1 == frac3);
        CHECK_FALSE(frac1 == frac2);
        CHECK_FALSE(frac1 == fracInfPos);
        CHECK_FALSE(frac4 == fracInfNeg);
        CHECK(fracInfPos == fracInfPos);
        CHECK(fracInfNeg == fracInfNeg);
        CHECK_FALSE(fracInfPos == fracInfNeg);
    }

    SUBCASE("Non-equality"){
        CHECK_FALSE(frac1 != frac3);
        CHECK(frac1 != frac2);
        CHECK(frac1 != fracInfPos);
        CHECK(frac4 != fracInfNeg);
        CHECK_FALSE(fracInfPos != fracInfPos);
        CHECK_FALSE(fracInfNeg != fracInfNeg);
        CHECK(fracInfPos != fracInfNeg);}
}

TEST_CASE("Cast functions"){
    Fraction frac1 = Fraction(2, 5);
    Fraction frac2 = Fraction(3);
    Fraction frac3 = Fraction(16, -8);
    Fraction fracInfPos = Fraction(true);

    SUBCASE("asInt") {
        CHECK(frac1.asInt() == 1);
        CHECK(frac2.asInt() == 3);
        CHECK(frac3.asInt() == -2);
        CHECK_THROWS_WITH(fracInfPos.asInt(), "Fraction : asInt : infinite is not an int");
    }

    SUBCASE("asDouble") {
        CHECK(frac1.asDouble() == .4);
        CHECK(frac2.asDouble() == 3.0);
        CHECK(frac3.asDouble() == -2.0);
        CHECK_THROWS_WITH(fracInfPos.asDouble(), "Fraction : asDouble : infinite is not a double");
    }

}