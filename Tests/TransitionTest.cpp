//
// Created by julie on 31/03/2021.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "./../PTG_Solvers/Transition.hpp"

Region reg0 = Region(0, 0);
Region reg1 = Region(0, 1);
Region reg2 = Region(2, 2);

State* state1 = new State("l1", Owner::Min, 14, Fraction(0));
State* state2 = new State("l2", Owner::Max, -4, Fraction(1));
State* state3 = new State("l3", Owner::Target, 0, Fraction(2));
State* rstate11 = new State(state1, &reg1);
State* rstate12 = new State(state1, &reg2);
State* rstate2 = new State(state2, &reg0);
State* rstate3 = new State(state3, &reg1);

Guard guard1 = Guard(Fraction(), Fraction(1));
Guard guard2 = Guard(Fraction(1), Fraction(2), true, false);
Guard guard3 = Guard();
Guard guard4 = Guard(Fraction(1), Fraction(1));


Transition transition1 = Transition(state1, 7, guard1, true, state2, "t1");
Transition transition2 = Transition(state1, 0, guard2, false, state3, "t2");
Transition transition3 = Transition(state2, -4, guard1, true, state3, "t3");
Transition rtransition2 = Transition(&transition1, &reg1, &reg0, "t4");
Transition rtransition3 = Transition(rstate11, 7, guard1, false, rstate12, "t4");
Transition rtransition4 = Transition(rstate11, 7, guard1, true, rstate2, "t5");
Transition rtransition5 = Transition(&transition2, &reg1, &reg1, "t5");
Transition rtransition6 = Transition(rstate11, 0, guard4, false, rstate3, "t5");

TEST_CASE("Constructor"){
    CHECK(guard3.isEmpty());
    CHECK_THROWS_WITH(Transition(state1, 0, guard1, true, state1, "t"), "Transition : no self-loop");
    CHECK_THROWS_WITH(Transition(state1, 0, guard3, true, state2, "t"), "Transition : guard must not be empty");

    CHECK_THROWS_WITH(Transition(rstate11, 0, guard1, true, rstate11,"t"), "Transition : no self-loop");
    CHECK_THROWS_WITH(Transition(rstate11, 0, guard3, true, rstate2, "t"), "Transition : guard must not be empty");
    CHECK_THROWS_WITH(Transition(rstate12, 0, guard1, false, rstate2, "t"), "Transition : no time back");

    CHECK_THROWS_WITH(Transition(&transition1, &reg2, &reg1, "t"), "Transition : reset go to null region");
    CHECK_THROWS_WITH(Transition(&transition2, &reg2, &reg1, "t"), "Transition : no time back");
}

TEST_CASE("Show"){
    state1->show();
    state2->show();
    transition1.show();
}

TEST_CASE("Getters"){
    CHECK(*transition1.getOrigin() == *state1);
    CHECK(*transition1.getDestination() == *state2);
    CHECK(transition1.getWeight() == 7);
    CHECK(transition1.getGuard() == guard1);
    CHECK(transition1.isReset());

    CHECK(*rtransition2.getOrigin() == rstate11);
    CHECK(*rtransition2.getDestination() == rstate2);
    CHECK(rtransition2.getWeight() == 7);
    CHECK(rtransition2.getGuard() == guard1);
    CHECK(rtransition2.isReset());

    CHECK(*rtransition3.getOrigin() == rstate11);
    CHECK(*rtransition3.getDestination() == rstate12);
    CHECK(rtransition3.getWeight() == 7);
    CHECK(rtransition3.getGuard() == guard1);
    CHECK_FALSE(rtransition3.isReset());

    CHECK(rtransition5 == rtransition6);

}

TEST_CASE("Transitions manipulation") {
    CHECK(transition1.isAvailable(Fraction(1, 2)));
    CHECK_FALSE(transition1.isAvailable(Fraction(2)));
    CHECK(transition2.isAvailable(Fraction(1)));
    CHECK_FALSE(transition2.isAvailable(Fraction(2)));

    CHECK(transition1 == transition1);
    CHECK_FALSE(transition1 == transition2);
    CHECK(rtransition2 == rtransition4);
}

TEST_CASE("List manipulation"){
    ListTransition list1 = ListTransition();
    list1.add(&transition1);
    list1.add(&rtransition2);
    list1.add(&rtransition3);

    ListTransition list2 = ListTransition();
    list2.add(&rtransition2);
    list2.add(&rtransition3);

    ListTransition list3 = ListTransition();
    list3.add(&transition1);
    list3.add(&rtransition2);
    list3.add(&rtransition3);

    ListTransition* list4 = list3.copy();

    list1.show(false);
    list2.show(false);
    list3.show(true);

    CHECK(list1 == list1);
    CHECK(list1 == list3);
    CHECK_FALSE(list1 == list2);
    CHECK(*list4 == list3);

    CHECK(list1.containsTransition(&transition1));
    CHECK_FALSE(list2.containsTransition(&transition1));

    CHECK(*list3.getFirstElement() == transition1);
    list3.show(true);
    list3.removeFirstElement();
    CHECK(list3 == list2);

    list1.clear();
    list2.clear();
    list3.clear();
    list4->clear();
    delete list4;
}

TEST_CASE("delete"){
    delete state1;
    delete state2;
    delete state3;
    delete rstate11;
    delete rstate2;
    delete rstate12;
    delete rstate3;
}