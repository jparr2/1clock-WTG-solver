//
// Created by julie on 31/03/2021.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "./../PTG_Solvers/UnfoldingTransition.h"

Region reg0= Region(0, 0);
Region reg2;
Region reg1 = Region(2, 5);

State state0;
State state1 = State("label", Owner::Min, 1, Fraction());
State rstate1 = State(&state1, &reg2);
State rstate2 = State("label", Owner::Min, 1, Fraction(), &reg1);
State rstate3 = State(&state1, &reg1);
State rstate4 = State(&state1, &reg0);

Guard guard1 = Guard(Fraction(), Fraction(1));
Guard guard2 = Guard(Fraction(1), Fraction(2), true, false);
Guard guard3 = Guard();

Transition transition1 = Transition(&rstate1, 7, guard1, false, &rstate2, "t1");
Transition transition2 = Transition(&rstate1, 0, guard2, false, &rstate3, "t2");
Transition transition3 = Transition(&rstate2, -4, guard1, true, &rstate4, "t3");

Path path1 = Path(&transition1);
Path path2 = Path(&path1, &transition2);
Path path3 = Path(&path2, &transition3);

UnfoldingState ustate0 = UnfoldingState();
UnfoldingState ustate1 = UnfoldingState("ustate1", 0, Owner:: Max, &path1, Fraction());
UnfoldingState ustate2 = UnfoldingState("ustate2", 2, Owner::Min, reg0, &path2, Fraction());
UnfoldingState ustate3 = UnfoldingState(&rstate2, &path3, "ustate3");
UnfoldingState ustate4 = UnfoldingState(&rstate1, &path1, "(label, [0, 1])");
UnfoldingState ustate5 = UnfoldingState(&rstate3, &path2, "(label, [2, 5])");

UnfoldingTransition utransition0 = UnfoldingTransition();
UnfoldingTransition utransition1 = UnfoldingTransition(&ustate1, -2, guard1, false, &ustate3, "utrans1");
UnfoldingTransition utransition2 = UnfoldingTransition(&transition2, &path1, "utrans2");
UnfoldingTransition utransition3 = UnfoldingTransition(&utransition1);
UnfoldingTransition utransition4 = UnfoldingTransition(&transition3, &path1, "utrans4");


TEST_CASE("Constructor") {
    CHECK(guard3.isEmpty());
    CHECK_THROWS_WITH(UnfoldingTransition(&ustate1, 0, guard1, true, &ustate1, "t"), "Transition : no self-loop");
    CHECK_THROWS_WITH(UnfoldingTransition(&ustate1, 0, guard3, true, &ustate2, "t"),
                      "Transition : guard must not be empty");
}

TEST_CASE("Show"){
    utransition0.show();
    cout << endl;
    utransition1.show();
    cout << endl;
    utransition2.show();
    cout << endl;
    utransition3.show();
    cout << endl;
}

TEST_CASE("Getters"){
    CHECK(*utransition1.getOrigin() == ustate1);
    CHECK(*utransition1.getDestination() == ustate3);
    CHECK(utransition1.getWeight() == -2);
    CHECK(utransition1.getGuard() == guard1);
    CHECK_FALSE(utransition1.isReset());

    CHECK(*utransition2.getOrigin() == ustate4);
    CHECK(*utransition2.getDestination() == ustate5);
    CHECK(utransition2.getWeight() == 0);
    CHECK(utransition2.getGuard() == guard2);
    CHECK_FALSE(utransition2.isReset());

    CHECK(*utransition3.getOrigin() == ustate1);
    CHECK(*utransition3.getDestination() == ustate3);
    CHECK(utransition3.getWeight() == -2);
    CHECK(utransition3.getGuard() == guard1);
    CHECK_FALSE(utransition3.isReset());


}

TEST_CASE("Transitions manipulation") {
    CHECK(utransition1.isAvailable(Fraction(1, 2)));
    CHECK_FALSE(utransition1.isAvailable(Fraction(2)));
    CHECK(utransition2.isAvailable(Fraction(1)));
    CHECK_FALSE(utransition2.isAvailable(Fraction(2)));

    CHECK(utransition1 == utransition1);
    CHECK_FALSE(utransition1 == utransition2);
    CHECK(utransition3 == utransition1);
}

TEST_CASE("List manipulation"){
    ListUnfoldingTransition list1 = ListUnfoldingTransition();
    list1.add(&utransition1);
    list1.add(&utransition2);
    list1.add(&utransition4);

    ListUnfoldingTransition list2 = ListUnfoldingTransition();
    list2.add(&utransition2);
    list2.add(&utransition4);

    ListUnfoldingTransition list3 = ListUnfoldingTransition();
    list3.add(&utransition1);
    list3.add(&utransition2);
    list3.add(&utransition4);

    ListUnfoldingTransition* list4 = list3.copy();

    ListUnfoldingTransition list5 = ListUnfoldingTransition();
    list5.add(&utransition3);
    list5.add(&utransition1);

    list1.show();
    list2.show();
    list3.show();
    CHECK(list1.size() == 3);
    CHECK(list5.size() == 1);

    CHECK(list1 == list1);
    CHECK(list1 == list3);
    CHECK_FALSE(list1 == list2);
    CHECK(*list4 == list3);

    CHECK(list1.containsTransition(&utransition1));
    CHECK_FALSE(list2.containsTransition(&utransition1));

    CHECK(*list3.getFirstElement() == utransition1);
    list3.removeFirstElement();
    list3.show();
    CHECK(list3 == list2);

    list1.clear();
    list2.clear();
    list3.clear();
    list4->clear();
    list5.clear();
    delete list4;
}
