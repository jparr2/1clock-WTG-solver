//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

// Created by julie on 31/03/2021.
//
#include "doctest.h"
#include "./../PTG_Solvers/Path.h"

State state1 = State("l1", Owner::Min, 14, Fraction(0));
State state2 = State("l2", Owner::Max, -4, Fraction(1));
State state3 = State("l3", Owner::Target, 0, Fraction(2));

Guard guard1 = Guard(Fraction(), Fraction(1));
Guard guard2 = Guard(Fraction(1), Fraction(2), true, false);

Transition transition1 = Transition(&state1, 7, guard1, true, &state2, "t1");
Transition transition2 = Transition(&state1, 0, guard2, false, &state3, "t2");
Transition transition3 = Transition(&state2, -4, guard1, true, &state3, "t3");

Path path0 = Path();
Path path1 = Path(&transition1);
Path path2 = Path(&path1, &transition2);
Path path3 = Path(&path2, &transition3);
Path path4 = Path(&path2);
Path path5 = Path(&path1, &transition3);

TEST_CASE("show"){
    path1.show();
    cout << endl;
    path2.show();
    cout << endl;
    path3.show();
    cout << endl;
    path4.show();
    cout << endl;
}

TEST_CASE("Getters") {
    CHECK(state1 == *path1.getOrigin());
    CHECK(state1 == *path2.getOrigin());

    MyList<Transition> list1 = MyList<Transition>();
    list1.add(&transition1);
    MyList<Transition> list2 = MyList<Transition>();
    list2.add(&transition1);
    list2.add(&transition2);
    MyList<Transition> list3 = MyList<Transition>();
    list3.add(&transition1);
    list3.add(&transition2);
    list3.add(&transition3);

    CHECK(list1 == *path1.getPath());
    CHECK(list2 == *path2.getPath());
    CHECK(list3 == *path3.getPath());

    CHECK(path1.size() == 1);
    CHECK(path2.size() == 2);
}

TEST_CASE("Operator") {
    CHECK(path2 == path4);
    CHECK_FALSE(path1 == path2);
    CHECK_FALSE(path3 == path2);
}

TEST_CASE("getListTransition"){
    MyList<Transition>* list1 = path3.getListTransition(&transition2);
    MyList<Transition>* list2 = new MyList<Transition>();
    list2->add(&transition3);

    CHECK(*list1 == *list2);
    list1->removeAll();
    list1->clear();
    delete list1;
    //list2->removeAll();
    list2->clear();
    delete list2;
}

TEST_CASE("getSizeResetTranstion"){
    CHECK(path2.sizeLastResetTransition() == 1);
}