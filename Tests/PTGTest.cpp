//
// Created by julie on 24/03/2021.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//TODO: fuite mémoire à l'instanciation
#include "doctest.h"
#include "./../PTG_Solvers/PTG.hpp"

PTG ptg1 = PTG("./examples/PTG0.txt");
PTG ptg2 = PTG();
Fraction fraction = Fraction();
Owner Min = Owner::Min;
Owner Max = Owner::Max;
Owner Target = Owner::Target;

TEST_CASE("Transitions list manipulation"){
    State state1 = State("l1", Min, 14, fraction);
    State state2 = State("l2", Max, -4, fraction);
    State state3 = State("l3", Target, 0, fraction);
    Guard guard1 = Guard(Fraction(), Fraction(1));
    Guard guard2 = Guard(Fraction(1), Fraction(1));
    Transition transition1 = Transition(&state1, 7, guard1, true, &state2, "t1");
    Transition transition2 = Transition(&state1, 0, guard2, false, &state3, "t2");
    Transition transition3 = Transition(&state2, -4, guard1, true, &state3, "t3");

    auto list_transitions1 = MyList<Transition>();
    list_transitions1.add(&transition1);
    list_transitions1.add(&transition2);
    auto list_transitions2 = MyList<Transition>();
    list_transitions2.add(&transition2);
    list_transitions2.add(&transition1);
    auto list_transitions3 = MyList<Transition>();
    list_transitions3.add(&transition1);
    list_transitions3.add(&transition3);
    auto list_transitions4 = MyList<Transition>();
    list_transitions4.add(&transition1);

    CHECK(list_transitions1.contains(&transition1));
    CHECK_FALSE(list_transitions1.contains(&transition3));

    CHECK(list_transitions1 == list_transitions2);
    CHECK_FALSE(list_transitions1 == list_transitions3);
    CHECK_FALSE(list_transitions1 == list_transitions4);

    list_transitions1.clear();
    list_transitions2.clear();
    list_transitions3.clear();
    list_transitions4.clear();
}

TEST_CASE("States manipulation"){
    ptg1.show();

    State state1 = State("l1", Min, 14, fraction);
    State state2 = State("l3", Max, -4, fraction);
    State state3 = State("l2", Max, -4, fraction);

    auto result1 = ptg1.getAState("l1");
    auto result2 = ptg1.getAState("l2");
    CHECK(*result1 == state1);
    CHECK_FALSE(*result2 == state2);
    CHECK(*result2== state3);
    CHECK_THROWS_WITH(ptg1.getAState("lf"), "PTG: state not contains");

    CHECK(ptg1.containsState("l2"));
    CHECK_FALSE(ptg1.containsState("lf"));
}

TEST_CASE("Transitions manipulation") {
    State state1 = State("l1", Min, 14, fraction);
    State state2 = State("l2", Max, -4, fraction);
    State state3 = State("l3", Target, 0, fraction);

    Guard guard1 = Guard(Fraction(), Fraction(1));
    Guard guard2 = Guard(Fraction(1), Fraction(1));

    Transition transition1 = Transition(&state1, 7, guard1, true, &state2, "t0");
    Transition transition2 = Transition(&state1, 0, guard2, false, &state3, "t1");

    auto transitions = MyList<Transition>();
    transitions.add(&transition1);
    transitions.add(&transition2);

    CHECK(ptg1.getATransition("l1", "l2") == transition1);
    CHECK_THROWS_WITH(ptg1.getATransition("l3", "l1"), "PTG: transition not exists");
    CHECK_THROWS_WITH(ptg1.getATransition("l3", "lf"), "PTG: transition not exists");

    CHECK(ptg1.containsTransitions("l1", "l2"));
    CHECK_FALSE(ptg1.containsTransitions("l3", "l1"));
    CHECK_FALSE(ptg1.containsTransitions("l3", "lf"));

    auto transitions_list2 = ptg1.getTransitionsState("l1");
    CHECK(*transitions_list2 == transitions);

    MyList<Transition> transitions1 = MyList<Transition>();
    Transition* transition3 = new Transition(&state2, 0, guard2, false, &state1, "t2");
    transitions1.add(transition3);
    auto transitions_list3 = ptg1.getTransitionsState("l2");
    CHECK(*transitions_list3 == transitions1);

    transitions.clear();
    transitions1.clear();
    transitions_list2->clear();
    transitions_list3->clear();
    delete transitions_list2;
    delete transitions_list3;
    delete transition3;
}

TEST_CASE("Others constants") {
CHECK(ptg1.getMaxClock() == 1);
CHECK(ptg2.getMaxClock() == 0);

CHECK(ptg1.getSize() == 3);
CHECK(ptg2.getSize() == 0);

set <Region> regions = set<Region>();
regions.insert(Region(0, 0));
regions.insert(Region(0, 1));
regions.insert(Region(1, 1));
auto *regions1 = ptg1.getRegions();
CHECK(equalSetRegion(*regions1, regions));

regions.clear();
regions1->clear();
delete regions1;

ptg1.show();
}