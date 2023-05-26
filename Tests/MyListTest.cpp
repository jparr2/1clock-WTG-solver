//
// Created by julie on 31/03/2021.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "./../PTG_Solvers/MyList.h"
#include "./../PTG_Solvers/State.hpp"
#include "./../PTG_Solvers/Transition.hpp"
#include "./../PTG_Solvers/UnfoldingState.h"
#include "./../PTG_Solvers/UnfoldingTransition.h"

Region reg0 = Region(0, 0);
Region reg1 = Region(0, 1);
Region reg2 = Region(2, 2);

State state1 = State("l1", Owner::Min, 14, Fraction(0));
State state2 = State("l2", Owner::Max, -4, Fraction(1));
State state3 = State("l3", Owner::Target, 0, Fraction(2));

Guard guard1 = Guard(Fraction(), Fraction(1));
Guard guard2 = Guard(Fraction(1), Fraction(2), true, false);
Guard guard3 = Guard();
Guard guard4 = Guard(Fraction(1), Fraction(1));

Transition transition1 = Transition(&state1, 7, guard1, true, &state2, "t1");
Transition transition2 = Transition(&state1, 0, guard2, false, &state3, "t2");
Transition transition3 = Transition(&state2, -4, guard1, true, &state3, "t3");

Path path1 = Path(&transition1);
Path path2 = Path(&path1, &transition2);
Path path3 = Path(&path2, &transition3);

UnfoldingState ustate1 = UnfoldingState("ustate1", 0, Owner:: Max, &path1, Fraction());
UnfoldingState ustate3 = UnfoldingState(&state2, &path3, "ustate3");

UnfoldingTransition utransition1 = UnfoldingTransition(&ustate1, -2, guard1, false, &ustate3, "utrans1");
UnfoldingTransition utransition2 = UnfoldingTransition(&transition2, &path1, "utrans2");
UnfoldingTransition utransition3 = UnfoldingTransition(&transition3, &path1, "utrans4");

TEST_CASE("State"){
    MyList<State> list1 = MyList<State>();
    list1.add(&state1);
    list1.show();
    list1.erase(state1);
    list1.clear();

    MyList<State> list2 = MyList<State>();
    list2.add(&state1);
    list2.add(&state3);
    list2.show();
    CHECK(list2.contains(&state1));
    CHECK(list2.contains(&state3));
    list2.clear();
}

TEST_CASE("Transition"){
    MyList<Transition> list1 = MyList<Transition>();
    list1.add(&transition1);
    list1.add(&transition2);
    list1.add(&transition3);

    MyList<Transition> list2 = MyList<Transition>();
    list2.add(&transition2);
    list2.add(&transition3);

    MyList<Transition> list3 = MyList<Transition>();
    list3.add(&transition1);
    list3.add(&transition2);
    list3.add(&transition3);

    MyList<Transition>* list4 = list3.copy();

    list1.show();
    list2.show();
    list3.showInline();

    CHECK(list1 == list1);
    CHECK(list1 == list3);
    CHECK_FALSE(list1 == list2);
    CHECK(*list4 == list3);

    CHECK(list1.contains(&transition1));
    CHECK_FALSE(list2.contains(&transition1));

    CHECK(*list3.getFirstElement() == transition1);
    list3.showInline();
    list3.removeFirstElement();
    CHECK(list3 == list2);

    list1.clear();
    list2.clear();
    list3.clear();
    list4->clear();
    delete list4;
}