//
// Created by julie on 16/08/22.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "./../PTG_Solvers/PTG.hpp"
#include "./../PTG_Solvers/RegionPTG.h"
#include <iostream>

PTG ptg1 = PTG("./examples/PTG0.txt");
RegionPTG rptg1 = RegionPTG(&ptg1);
PTG ptg2 = PTG("./examples/PTG4.txt");
RegionPTG rptg2 = RegionPTG(&ptg2);
PTG ptg3= PTG("./examples/PTG5.txt");
RegionPTG rptg3 = RegionPTG(&ptg3);
PTG ptg4 = PTG("./examples/PTG6.txt");
RegionPTG rptg4 = RegionPTG(&ptg4);
PTG ptg5= PTG("./examples/PTG7.txt");
RegionPTG rptg5 = RegionPTG(&ptg5);
PTG ptg6= PTG("./examples/SPTG1.txt");
RegionPTG rptg6 = RegionPTG(&ptg6);
RegionPTG rptg7 = RegionPTG();

TEST_CASE("show"){
    ptg1.show();
    rptg1.show();
    rptg6.show();

    ptg2.show();
    rptg2.show();
}

TEST_CASE("Build closed PTG"){
    State* origin = new State("l1", Owner::Max, -1, Fraction());
    State* dest = new State("lf", Owner::Target, 0, Fraction(0));
    Region reg0 = Region(0, 0);
    Region reg1 = Region(0, 1);
    Region reg2 = Region(1,1);

    State* rstate0 = new State(origin, &reg0);
    State* rstate1 = new State(origin, &reg1);
    State* rstate2 = new State(origin, &reg2);
    State* rstate3 = new State(dest, &reg0);
    State* rstate4 = new State(dest, &reg1);
    State* rstate5 = new State(dest, &reg2);
    auto rstates = MyList<State>();
    rstates.add(rstate0);
    rstates.add(rstate1);
    rstates.add(rstate2);
    rstates.add(rstate3);
    rstates.add(rstate4);
    rstates.add(rstate5);

    CHECK(*rptg2.getStates() == rstates);
    CHECK(*rptg3.getStates() == rstates);
    CHECK(*rptg4.getStates() == rstates);
    CHECK(*rptg5.getStates() == rstates);

    Guard guard10 = Guard(Fraction(0), Fraction(0));
    Guard guard11 = Guard(Fraction(0), Fraction(1));
    Guard guard12 = Guard(Fraction(1), Fraction(1));

    Transition transition = Transition(origin, 0, Guard(Fraction(0), Fraction(1)), false, dest, "t");
    Transition* rtransition1 = new Transition(rstate0, 0, guard10, false, rstate3, "rt0");
    Transition* rtransition2 = new Transition(rstate0, 0, guard11, false, rstate4, "rt1");
    Transition* rtransition3 = new Transition(rstate0, 0, guard12, false, rstate5, "rt2");
    Transition* rtransition4 = new Transition(&transition, &reg1, &reg1, "rt3");
    Transition* rtransition5 = new Transition(&transition, &reg1, &reg2, "rt4");
    Transition* rtransition6 = new Transition(&transition, &reg2, &reg2, "rt5");
    auto rtransitions1 = MyList<Transition>();
    rtransitions1.add(rtransition1);
    rtransitions1.add(rtransition2);
    rtransitions1.add(rtransition3);
    rtransitions1.add(rtransition4);
    rtransitions1.add(rtransition5);
    rtransitions1.add(rtransition6);
    CHECK(*rptg2.getTransitions() == rtransitions1);

    auto rtransitions2 = MyList<Transition>();
    rtransitions2.add(rtransition2);
    rtransitions2.add(rtransition4);
    CHECK(*rptg3.getTransitions() == rtransitions2);

    auto rtransitions3 = MyList<Transition>();
    rtransitions3.add(rtransition2);
    rtransitions3.add(rtransition3);
    rtransitions3.add(rtransition4);
    rtransitions3.add(rtransition5);
    rtransitions3.add(rtransition6);
    CHECK(*rptg4.getTransitions() == rtransitions3);

    auto rtransitions4 = MyList<Transition>();
    rtransitions4.add(rtransition1);
    rtransitions4.add(rtransition2);
    rtransitions4.add(rtransition4);
    CHECK(*rptg5.getTransitions() == rtransitions4);

    rtransitions1.clear();
    rtransitions2.clear();
    rtransitions3.clear();
    rtransitions4.clear();
    delete rtransition1;
    delete rtransition2;
    delete rtransition3;
    delete rtransition4;
    delete rtransition5;
    delete rtransition6;
    delete rstate0;
    delete rstate1;
    delete rstate2;
    delete rstate3;
    delete rstate4;
    delete rstate5;
    rstates.clear();
    delete origin;
    delete dest;
}

TEST_CASE("Pruned PTG"){
    State* origin = new State("l1", Owner::Max, -1, Fraction());
    State* dest = new State("lf", Owner::Target, 0, Fraction(0));
    Region reg0 = Region(0, 0);
    Region reg1 = Region(0, 1);
    Region reg2 = Region(1,1);

    rptg2.prunedPTG("(l1, [0, 0])");
    rptg3.prunedPTG("(l1, [0, 0])");
    rptg4.prunedPTG("(l1, [0, 0])");
    rptg5.prunedPTG("(l1, [0, 0])");

    SUBCASE("States") {
        cout << "States" << endl;
        State *rstate0 = new State(origin, &reg0);
        State *rstate3 = new State(dest, &reg0);
        State *rstate4 = new State(dest, &reg1);
        State *rstate5 = new State(dest, &reg2);
        auto rstates1 = MyList<State>();
        rstates1.add(rstate0);
        rstates1.add(rstate3);
        rstates1.add(rstate4);
        rstates1.add(rstate5);
        auto rstates2 = MyList<State>();
        rstates2.add(rstate0);
        rstates2.add(rstate4);
        auto rstates3 = MyList<State>();
        rstates3.add(rstate0);
        rstates3.add(rstate4);
        rstates3.add(rstate5);
        auto rstates4 = MyList<State>();
        rstates4.add(rstate0);
        rstates4.add(rstate3);
        rstates4.add(rstate4);

        rptg2.getStates()->show();
        CHECK(*rptg2.getStates() == rstates1);
        CHECK(*rptg3.getStates() == rstates2);
        CHECK(*rptg4.getStates() == rstates3);
        CHECK(*rptg5.getStates() == rstates4);

        delete rstate0;
        delete rstate3;
        delete rstate4;
        delete rstate5;
        rstates1.clear();
        rstates2.clear();
        rstates3.clear();
        rstates4.clear();
    }

    SUBCASE("Transitions") {
        Transition transition = Transition(origin, 0, Guard(Fraction(0), Fraction(1)), false, dest, "t1");
        Transition *rtransition1 = new Transition(&transition, &reg0, &reg0, "rt0");
        Transition *rtransition2 = new Transition(&transition, &reg0, &reg1, "rt1");
        Transition *rtransition3 = new Transition(&transition, &reg0, &reg2, "rt2");

        auto rtransitions1 = MyList<Transition>();
        rtransitions1.add(rtransition1);
        rtransitions1.add(rtransition2);
        rtransitions1.add(rtransition3);
        auto rtransitions2 = MyList<Transition>();
        rtransitions2.add(rtransition2);
        auto rtransitions3 = MyList<Transition>();
        rtransitions3.add(rtransition2);
        rtransitions3.add(rtransition3);
        auto rtransitions4 = MyList<Transition>();
        rtransitions4.add(rtransition1);
        rtransitions4.add(rtransition2);


        CHECK(*rptg2.getTransitions() == rtransitions1);
        CHECK(*rptg3.getTransitions() == rtransitions2);
        CHECK(*rptg4.getTransitions() == rtransitions3);
        CHECK(*rptg5.getTransitions() == rtransitions4);

        rtransitions1.clear();
        rtransitions2.clear();
        rtransitions3.clear();
        rtransitions4.clear();
        delete rtransition1;
        delete rtransition2;
        delete rtransition3;
    }

    delete origin;
    delete dest;
}
