//
// Created by julie on 18/08/22.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../PTG_Solvers/UnfoldingState.h"


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

Transition transition1 = Transition(&rstate1, 7, guard1, false, &rstate2, "t1");
Transition transition2 = Transition(&rstate1, 0, guard2, false, &rstate3, "t2");
Transition transition3 = Transition(&rstate2, -4, guard1, true, &rstate4, "t3");

Path path1 = Path(&transition1);
Path path2 = Path(&path1, &transition2);
Path path3 = Path(&path2, &transition3);
Path path4 = Path(&path2);
Path path5 = Path(&path1, &transition3);
Path path6 = Path(&transition3);
Path path7 = Path(&path6, &transition2);


UnfoldingState ustate0 = UnfoldingState();
UnfoldingState ustate1 = UnfoldingState("ustate1", 0, Owner:: Max, &path5, Fraction());
UnfoldingState ustate2 = UnfoldingState("ustate2", 2, Owner::Min, reg0, &path4, Fraction());
UnfoldingState ustate3 = UnfoldingState(&rstate2, &path3, "ustate3");
UnfoldingState ustate4 = UnfoldingState(&ustate3, "ustate4");
UnfoldingState ustate5 = UnfoldingState(&ustate0, &transition3, "ustate5");
UnfoldingState ustate6 = UnfoldingState(&ustate5, &transition2, "ustate6");
UnfoldingState ustate7 = UnfoldingState(&state1, &path2, "ustate7");

TEST_CASE("Show"){
    ustate1.show();
    ustate2.show();
    ustate3.show();
    ustate4.show();
    ustate5.show();
}

TEST_CASE("Getters") {
    Function function_infinite = Function(Fraction(true), Fraction(1));
    Function function_target = Function(Fraction(0), Fraction(1));

    SUBCASE("getLabel"){
        CHECK(ustate0.getLabel() == "lf");
        CHECK(ustate1.getLabel() == "ustate1");
        CHECK(ustate2.getLabel() == "ustate2");
        CHECK(ustate3.getLabel() == "ustate3");
        CHECK(ustate4.getLabel() == "ustate4");
        CHECK(ustate5.getLabel() == "ustate5");
    }

    SUBCASE("getWeight"){
        CHECK(ustate0.getWeight() == 0);
        CHECK(ustate1.getWeight() == 0);
        CHECK(ustate2.getWeight() == 2);
        CHECK(ustate3.getWeight() == 1);
        CHECK(ustate4.getWeight() == 1);
        CHECK(ustate5.getWeight() == 0);
    }

    SUBCASE("getFinalWeight"){
        CHECK(ustate0.getFinalWeight() == Fraction(0));
        CHECK(ustate6.getFinalWeight() == Fraction(0));
        CHECK_THROWS(ustate1.getFinalWeight());
    }

    SUBCASE("getOwner"){
        CHECK(ustate0.getOwner() == Owner::Target);
        CHECK(ustate1.getOwner() == Owner::Max);
        CHECK(ustate2.getOwner() == Owner::Min);
        CHECK(ustate3.getOwner() == Owner::Min);
        CHECK(ustate4.getOwner() == Owner::Min);
        CHECK(ustate5.getOwner() == Owner::Target);
    }

    SUBCASE("getValue"){
        CHECK(*ustate0.getValueFunction() == function_target);
        CHECK(*ustate1.getValueFunction() == function_infinite);
        CHECK(*ustate2.getValueFunction() == function_infinite);
        CHECK(*ustate3.getValueFunction() == function_infinite);
        CHECK(*ustate4.getValueFunction() == function_infinite);
        CHECK(*ustate5.getValueFunction() == function_target);
    }

    SUBCASE("setValue") {
        ustate1.setValue(new Function(Fraction(true), Fraction(1)));
        CHECK(*ustate1.getValueFunction() == function_infinite);
        CHECK(ustate1.getValueFunction()->getValueClock(Fraction(1, 2)) == Fraction(true));
    }

    SUBCASE("getTmpValue"){
        CHECK(ustate0.getTmpValue() == nullptr);
        CHECK(ustate1.getTmpValue() == nullptr);
        CHECK(ustate2.getTmpValue() == nullptr);
        CHECK(ustate3.getTmpValue() == nullptr);
        CHECK(ustate4.getTmpValue() == nullptr);
        CHECK(ustate5.getTmpValue() == nullptr);
    }

    SUBCASE("getRegion"){
        CHECK_THROWS_WITH(ustate0.getRegion(), "getRegion: no region instanciate");
        CHECK_THROWS_WITH(ustate1.getRegion(), "getRegion: no region instanciate");
        CHECK(*ustate2.getRegion() == reg0);
        CHECK(*ustate3.getRegion() == reg1);
        CHECK(*ustate4.getRegion() == reg1);
        CHECK_THROWS_WITH(ustate5.getRegion(), "getRegion: no region instanciate");
    }

    SUBCASE("getPath"){
        CHECK_THROWS_WITH(ustate0.getPath(), "getPath: no path instanciate");
        CHECK(*ustate1.getPath() == path5);
        CHECK(*ustate2.getPath() == path4);
        CHECK(*ustate3.getPath() == path3);
        CHECK(*ustate4.getPath() == path3);
        CHECK(*ustate5.getPath() == path6);
        CHECK(*ustate6.getPath() == path7);
        CHECK(*ustate7.getPath() == path2);
    }
}

TEST_CASE("Tester"){
    SUBCASE("isMin"){
        CHECK_FALSE(ustate0.isMin());
        CHECK_FALSE(ustate1.isMin());
        CHECK(ustate2.isMin());
        CHECK(ustate3.isMin());
        CHECK(ustate4.isMin());
        CHECK_FALSE(ustate5.isMin());
    }

    SUBCASE("isMax"){
        CHECK_FALSE(ustate0.isMax());
        CHECK(ustate1.isMax());
        CHECK_FALSE(ustate2.isMax());
        CHECK_FALSE(ustate3.isMax());
        CHECK_FALSE(ustate4.isMax());
        CHECK_FALSE(ustate5.isMax());
    }

    SUBCASE("isTarget"){
        CHECK(ustate0.isTarget());
        CHECK_FALSE(ustate1.isTarget());
        CHECK_FALSE(ustate2.isTarget());
        CHECK_FALSE(ustate3.isTarget());
        CHECK_FALSE(ustate4.isTarget());
        CHECK(ustate5.isTarget());
    }

    SUBCASE("isShow"){
        CHECK_FALSE(ustate0.isShow());
        CHECK_FALSE(ustate1.isShow());
        CHECK_FALSE(ustate2.isShow());
        CHECK_FALSE(ustate3.isShow());
        CHECK_FALSE(ustate4.isShow());
        CHECK_FALSE(ustate5.isShow());
    }

    SUBCASE("isUsed"){
        CHECK_FALSE(ustate0.isUsed());
        CHECK_FALSE(ustate1.isUsed());
        CHECK_FALSE(ustate2.isUsed());
        CHECK_FALSE(ustate3.isUsed());
        CHECK_FALSE(ustate4.isUsed());
        CHECK_FALSE(ustate5.isUsed());
    }

    SUBCASE("isRegion"){
        CHECK_FALSE(ustate0.isRegion());
        CHECK_FALSE(ustate1.isRegion());
        CHECK(ustate2.isRegion());
        CHECK(ustate3.isRegion());
        CHECK(ustate4.isRegion());
        CHECK_FALSE(ustate5.isRegion());
    }

    SUBCASE("isUnfolding"){
        CHECK_FALSE(ustate0.isUnfolding());
        CHECK(ustate1.isUnfolding());
        CHECK(ustate2.isUnfolding());
        CHECK(ustate3.isUnfolding());
        CHECK(ustate4.isUnfolding());
        CHECK(ustate5.isUnfolding());
    }
}

TEST_CASE("Operator"){
    CHECK(ustate1 == ustate1);
    CHECK_FALSE(ustate1 == ustate3);
    CHECK_FALSE(ustate2 == ustate1);
    CHECK_FALSE(ustate0 == ustate1);
    CHECK_FALSE(ustate1 == ustate4);

    UnfoldingState* ustate8 = ustate2.copy();
    CHECK(ustate2 == *ustate8);
    delete ustate8;
}

TEST_CASE("List of unfolding states") {
    ListUnfoldingState list2 = ListUnfoldingState();
    list2.add(&ustate1);
    list2.add(&ustate4);
    ListUnfoldingState list3 = ListUnfoldingState();
    list3.add(&ustate2);
    ListUnfoldingState list4 = ListUnfoldingState();
    list4.add(&ustate5);
    list4.add(&ustate3);
    ListUnfoldingState* list1 = list4.copy();

    list2.show();

    SUBCASE("size"){
        CHECK(list2.size() == 2);
        CHECK(list3.size() == 1);
        CHECK(list4.size() == 2);
    }

    SUBCASE("containState"){
        CHECK(list2.containsState(&ustate1));
        CHECK_FALSE(list3.containsState(&ustate1));
        CHECK(list1->containsState(&ustate5));
        CHECK_FALSE(list1->containsState(&ustate1));
    }

    SUBCASE("operator"){
        CHECK(*list1 == list4);
        CHECK(list2 == list2);
        CHECK_FALSE(*list1 == list2);
    }

    SUBCASE("find"){
        CHECK(*list1->find("ustate5") == ustate5);
        CHECK(*list2.find("ustate1") == ustate1);
        CHECK(list3.find("lf") == nullptr);
    }

    list2.clear();
    list3.clear();
    list4.clear();
    list1->clear();
    delete list1;
}