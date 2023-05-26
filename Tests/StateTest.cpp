/*
 * Author : Julie parreaux
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "./../PTG_Solvers/State.hpp"

Function function_infinite = Function(Fraction(true), Fraction(1));
Region reg0;
Region reg1 = Region(2, 5);
Region reg2 = Region(2, 5);


State state1 = State();
State state2 = State("l1", Owner::Min, 0, Fraction(0));
State state3 = State("l1", Owner::Max, -2, Fraction(5));
State state4 = State("l3", Owner::Target, 6, Fraction(10));
State rstate1 = State(&state2, &reg1);
State rstate2 = State("label", Owner::Min, 1, Fraction(), &reg2);
State rstate3 = State(&state2, &reg0);
State rstate4 = State("(l1, [0, 1])", Owner::Min, 0, Fraction(0), &reg0);

TEST_CASE("Show"){
    state1.show();
    cout <<  endl;
    state2.show();
    cout <<  endl;
    state3.show();
    cout <<  endl;
    state4.show();
    cout <<  endl;
    rstate1.show();
    cout <<  endl;
    rstate2.show();
    cout <<  endl;
    rstate3.show();
    cout <<  endl;
    rstate4.show();
    cout << endl;
}

TEST_CASE("Getters"){
    CHECK(state1.getLabel().compare("lf") == 0);
    CHECK(state2.getLabel().compare("l1") == 0);

    CHECK(state1.getWeight() == 0);
    CHECK(state2.getWeight() == 0);

    CHECK_FALSE(state1.isMin());
    CHECK_FALSE(state1.isMax());
    CHECK(state1.isTarget());

    CHECK(state2.isMin());
    CHECK_FALSE(state2.isMax());
    CHECK_FALSE(state2.isTarget());

    CHECK_FALSE(state3.isMin());
    CHECK(state3.isMax());
    CHECK_FALSE(state3.isTarget());

    CHECK_FALSE(state4.isMin());
    CHECK_FALSE(state4.isMax());
    CHECK(state4.isTarget());

    state1.setShow(true);
    CHECK_FALSE(state2.isShow() == state1.isShow());

    CHECK(*rstate3.getRegion() == reg0);
    CHECK(*rstate1.getRegion() == reg1);
    CHECK(*rstate2.getRegion() == reg1);

    CHECK_THROWS(state1.getRegion());
}

TEST_CASE("Value manipulations"){
    Function function_0 = Function(Fraction(0), Fraction(1));
    Function function_10 = Function(Fraction(10), Fraction(1));

    SUBCASE("getValue") {
        CHECK(*state2.getValueFunction() == function_infinite);
        CHECK(*state1.getValueFunction() == function_0);
        CHECK(*state4.getValueFunction() == function_10);
        CHECK(*state3.getValueFunction() == function_infinite);
        CHECK(*rstate2.getValueFunction() == function_infinite);
    }
    SUBCASE("getValueClock") {
        CHECK(state1.getValueFunction()->getValueClock(Fraction(1, 2)) == Fraction(0));
        CHECK(state2.getValueFunction()->getValueClock(Fraction(1, 2)) == Fraction(true));
        CHECK(state3.getValueFunction()->getValueClock(Fraction(1, 2)) == Fraction(true));
        CHECK(state4.getValueFunction()->getValueClock(Fraction(1, 2)) == Fraction(10));
    }
    SUBCASE("setValue") {
        state1.setValue(new Function(Fraction(true), Fraction(1)));
        CHECK(*state1.getValueFunction() == function_infinite);
        CHECK(state1.getValueFunction()->getValueClock(Fraction(1, 2)) == Fraction(true));
    }
}

TEST_CASE("State comparison"){
    CHECK(state3 == state2);
    CHECK_FALSE(state1 == state3);

    CHECK(rstate3 == rstate4);
    CHECK_FALSE(rstate1 == rstate3);
}

TEST_CASE("List manipulation"){
    ListState list1 = ListState();
    list1.add(&state1);
    list1.show();
    list1.erase(state1);
    list1.clear();

    ListState list2 = ListState();
    list2.add(&rstate1);
    list2.add(&rstate3);
    list2.show();
    CHECK(list2.containsState(&rstate1));
    CHECK(list2.containsState(&rstate3));
    list2.clear();
}