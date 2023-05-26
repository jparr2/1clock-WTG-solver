//
// Created by julie on 23/03/2021.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "./../PTG_Solvers/Guard.hpp"

Fraction frac_1 = Fraction(1);
Fraction frac_2 = Fraction(2);
Fraction frac_3 = Fraction(3);
Fraction frac_4 = Fraction(-4);
Fraction frac_5 = Fraction(3, 2);
Fraction frac_infpos = Fraction(true);
Fraction frac_infneg = Fraction(false);

Guard guard;
Guard guard_1 = Guard(frac_1, frac_2);
Guard guard_2 = Guard(frac_1, frac_1);
Guard guard_3 = Guard(frac_1, frac_2, false, false);
Guard guard_4 = Guard(frac_1, frac_2, true, false);
Guard guard_5 = Guard(frac_1, frac_2, false, true);
Guard guard_6 = Guard(frac_1, frac_3);

Region reg1 = Region(0, 1);
Region reg2 = Region(0, 2);
Region reg3 = Region(0, 3);
Region reg4 = Region(3, 4);
Region reg5 = Region(0, 0);

Guard guard1 = Guard(guard_1, reg1);
Guard guard2 = Guard(guard_1, reg2);
Guard guard3 = Guard(guard_1, reg3);
Guard guard4 = Guard(guard_6, reg2);
Guard guard5 = Guard(guard_6, reg3);
Guard guard6 = Guard(guard_6, reg4);

TEST_CASE("Constructor"){
    CHECK_THROWS_WITH(Guard(frac_2, frac_1), "Guard : ordnance bound");

    CHECK_THROWS_WITH(Guard(frac_2, frac_1, false, false), "Guard : ordnance bound");
    CHECK_THROWS_WITH(Guard(frac_2, frac_1, true, false), "Guard : ordnance bound");
    CHECK_THROWS_WITH(Guard(frac_2, frac_1, false, true), "Guard : ordnance bound");
    CHECK_THROWS_WITH(Guard(frac_2, frac_2, false, false), "Guard : bad format for singleton");
    CHECK_THROWS_WITH(Guard(frac_2, frac_2, true, false), "Guard : bad format for singleton");
    CHECK_THROWS_WITH(Guard(frac_2, frac_2, false, true), "Guard : bad format for singleton");

    CHECK_THROWS_WITH(Guard(frac_infneg, frac_1, false, false), "Guard : only for no guards");
    CHECK_THROWS_WITH(Guard(frac_infneg, frac_1), "Guard : only for no guards");
    CHECK_THROWS_WITH(Guard(frac_infpos, frac_infpos, false, false), "Guard : only for no guards");
    CHECK_THROWS_WITH(Guard(frac_infpos, frac_infpos), "Guard : only for no guards");

    CHECK_THROWS_WITH(Guard(frac_4, frac_3), "Guard : bad format for lower-bound");
    CHECK_THROWS_WITH(Guard(frac_4, frac_3, false, false), "Guard : bad format for lower-bound");
    CHECK_THROWS_WITH(Guard(frac_4, frac_3, true, false), "Guard : bad format for lower-bound");
    CHECK_THROWS_WITH(Guard(frac_4, frac_3, false, true), "Guard : bad format for lower-bound");

    CHECK_THROWS_WITH(Guard(guard_1, reg5), "Guard : empty");
    CHECK_THROWS_WITH(Guard(guard_1, reg4), "Guard : empty");
}

TEST_CASE("Getters"){
    CHECK(guard_1.getStartValue() == frac_1);
    CHECK(guard_1.getEndValue() == frac_2);
    CHECK(guard_1.isStartOpen());
    CHECK(guard_1.isEndOpen());

    CHECK(guard_4.getStartValue() == frac_1);
    CHECK(guard_4.getEndValue() == frac_2);
    CHECK(guard_4.isStartOpen());
    CHECK_FALSE(guard_4.isEndOpen());

    CHECK(guard.isEmpty());
    CHECK_FALSE(guard_1.isEmpty());

    CHECK(guard1.isStartOpen());
    CHECK(guard1.isEndOpen());
    CHECK(guard1.getStartValue() == frac_1);
    CHECK(guard1.getEndValue() == frac_1);

    CHECK(guard2.getStartValue() == frac_1);
    CHECK(guard2.getEndValue() == frac_2);

    CHECK(guard3.getStartValue() == frac_1);
    CHECK(guard3.getEndValue() == frac_2);

    CHECK(guard4.getStartValue() == frac_1);
    CHECK(guard4.getEndValue() == frac_2);

    CHECK(guard5.getStartValue() == frac_1);
    CHECK(guard5.getEndValue() == frac_3);

    CHECK(guard6.getStartValue() == frac_3);
    CHECK(guard6.getEndValue() == frac_3);
}

TEST_CASE("Guard manipulations"){
    CHECK(guard_1.isModel(frac_1));
    CHECK(guard_1.isModel(frac_2));
    CHECK_FALSE(guard_1.isModel(frac_3));
    CHECK(guard_1.isModel(frac_5));

    CHECK_FALSE(guard_3.isModel(frac_1));
    CHECK_FALSE(guard_3.isModel(frac_2));
    CHECK_FALSE(guard_3.isModel(frac_3));
    CHECK(guard_3.isModel(frac_5));

    CHECK_FALSE(guard_5.isModel(frac_1));
    CHECK(guard_5.isModel(frac_2));
    CHECK_FALSE(guard_5.isModel(frac_3));
    CHECK(guard_5.isModel(frac_5));

    Region reg1 = Region(0, 1);
    Region reg2 = Region(1, 1);
    Region reg3 = Region(1, 2);
    Region reg4 = Region(2, 2);
    Region reg5 = Region(2, 3);
    Region reg6 = Region(3, 3);

    CHECK(guard_1.isReachable(reg1));
    CHECK(guard_1.isReachable(reg2));
    CHECK(guard_1.isReachable(reg3));
    CHECK(guard_1.isReachable(reg4));
    CHECK(guard_1.isReachable(reg5));
    CHECK_FALSE(guard_1.isReachable(reg6));

    CHECK(guard_1.isInInterval(Fraction(3, 2)));
    CHECK_FALSE(guard_1.isInInterval(Fraction()));
    CHECK(guard_3.isInInterval(Fraction(3, 2)));
    CHECK_FALSE(guard_3.isInInterval(Fraction()));
    CHECK_FALSE(guard_3.isInInterval(frac_1));
    CHECK_FALSE(guard_3.isInInterval(frac_2));
}
