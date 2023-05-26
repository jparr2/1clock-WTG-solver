//
// Created by julie on 03/04/2021.
//


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "./../PTG_Solvers/ValueIteration.hpp"
#include "./../PTG_Solvers/PTG.hpp"
#include "./../PTG_Solvers/RegionPTG.h"
#include "./../PTG_Solvers/UnfoldingPTG.h"


ValueIteration<PTG, State, Transition> valueIteration;
ValueIteration<RegionPTG, State, Transition> regionValueIteration;
ValueIteration<UnfoldingPTG, UnfoldingState, UnfoldingTransition> unfoldingValueIteration;

Point point1 = Point(Fraction(0), Fraction(-1));
Point point2 = Point(Fraction(1), Fraction(0));
Point point3 = Point(Fraction(0), Fraction(1));
Point point4 = Point(Fraction(0), Fraction(-16));
Point point5 = Point(Fraction(0), Fraction(-4));
Point point6 = Point(Fraction(1), Fraction(-7));
Point point7 = Point(Fraction(0), Fraction(-10));
Point point8 = Point(Fraction(6, 19), Fraction(-94, 19));
Point point9 = Point(Fraction(0), Fraction(2));
Point point10 = Point(Fraction(1), Fraction(6));
Point point11 = Point(Fraction(0), Fraction(-11));
Point point12 = Point(Fraction(0), Fraction(10));
Point point13 = Point(Fraction(0), Fraction(14));
list<Point> points1 = {point1, point2};
list<Point> points2 = {point3, point2};
list<Point> points3 = {point4, point2};
list<Point> points4 = {point5, point6};
list<Point> points5 = {point7, point8, point6};
list<Point> points6 = {point9, point10};
list<Point> points7 = {point11, point6};
list<Point> points8 = {point12, point10};
list<Point> points9 = {point13, point2};

Function expected0 = Function(Fraction(0), Fraction(1));
Function expected1 = Function(&points1, true);
Function expected2 = Function(&points2, false);
Function expected3 = Function(Fraction(1, 10), Fraction(1));
Function expected4 = Function(&points3, true);
Function expected5 = Function(&points4, false);
Function expected6 = Function(&points5, true);
Function expected7 = Function(&points6, false);
Function expected8 = Function(&points7, false);
Function expected9 = Function(&points8, false);
Function expected10 = Function(&points9, true);

TEST_CASE("One transition without reset"){
    PTG* sptg0 = new PTG("./examples/SPTG0.txt");
    sptg0->show();
    cout << "**** Obtained final value for SPTG0 ****" << endl;
    valueIteration.getValue(sptg0, false, true);
    CHECK(*sptg0->getAState("lf")->getValueFunction() == expected0);
    delete sptg0;

    PTG* sptg1 = new PTG("./examples/SPTG1.txt");
    sptg1->show();
    cout << "**** Obtained final value for SPTG1 ****" << endl;
    valueIteration.getValue(sptg1, false, true);
    CHECK(*sptg1->getAState("lf")->getValueFunction() == expected0);
    CHECK(*sptg1->getAState("l0")->getValueFunction() == expected1);
    delete sptg1;

    PTG* sptg2 = new PTG("./examples/SPTG2.txt");
    sptg2->show();
    cout << "**** Obtained final value for SPTG2 ****" << endl;
    valueIteration.getValue(sptg2, false, true);
    CHECK(*sptg2->getAState("lf")->getValueFunction() == expected3);
    CHECK(*sptg2->getAState("l0")->getValueFunction() == expected3);
    delete sptg2;

    PTG* sptg3 = new PTG("./examples/SPTG3.txt");
    sptg3->show();
    cout << "**** Obtained final value for SPTG3 ****" << endl;
    valueIteration.getValue(sptg3, false, true);
    CHECK(*sptg3->getAState("lf")->getValueFunction() == expected0);
    CHECK(*sptg3->getAState("l0")->getValueFunction() == expected0);
    delete sptg3;

    PTG* sptg4 = new PTG("./examples/SPTG4.txt");
    sptg4->show();
    cout << "**** Obtained final value for SPTG4 ****" << endl;
    valueIteration.getValue(sptg4, false, true);
    CHECK(*sptg4->getAState("lf")->getValueFunction() == expected0);
    CHECK(*sptg4->getAState("l0")->getValueFunction() == expected2);
    delete sptg4;
}

TEST_CASE("One transition with reset"){
    PTG* ptg1 = new PTG("./examples/PTG1.txt");
    cout << "**** Obtained final value for PTG1 ****" << endl;
    ptg1->show();
    valueIteration.getValue(ptg1, false, true);
    CHECK(*ptg1->getAState("lf")->getValueFunction() == expected0);
    CHECK(*ptg1->getAState("l1")->getValueFunction() == expected0);
    delete ptg1;

    PTG* ptg2 = new PTG("./examples/PTG2.txt");
    cout << "**** Obtained final value for PTG2 ****" << endl;
    ptg2->show();
    valueIteration.getValue(ptg2, false, true);
    CHECK(*ptg2->getAState("lf")->getValueFunction() == expected0);
    CHECK(*ptg2->getAState("l1")->getValueFunction() == expected1);
    delete ptg2;

    PTG* ptg3 = new PTG("./examples/PTG3.txt");
    cout << "**** Obtained final value for PTG3 ****" << endl;
    ptg3->show();
    valueIteration.getValue(ptg3, false, true);
    CHECK(*ptg3->getAState("lf")->getValueFunction() == expected0);
    CHECK(*ptg3->getAState("l1")->getValueFunction() == expected2);
    delete ptg3;

    PTG* ptg4 = new PTG("./examples/PTG4.txt");
    cout << "**** Obtained final value for PTG4 ****" << endl;
    ptg4->show();
    valueIteration.getValue(ptg4, false, true);
    CHECK(*ptg4->getAState("lf")->getValueFunction() == expected0);
    CHECK(*ptg4->getAState("l1")->getValueFunction() == expected0);
    delete ptg4;
}

TEST_CASE("Acyclic PTG without reset"){
    PTG* sptg5 = new PTG("./examples/SPTG5.txt");
    cout << "**** Obtained final value for SPTG5 ****" << endl;
    sptg5->show();
    valueIteration.getValue(sptg5, false, true);
    CHECK(*sptg5->getAState("lf")->getValueFunction() == expected0);
    CHECK(*sptg5->getAState("l3")->getValueFunction() == expected4);
    CHECK(*sptg5->getAState("l2")->getValueFunction() == expected5);
    CHECK(*sptg5->getAState("l1")->getValueFunction() == expected6);
    delete sptg5;

    PTG* sptg6 = new PTG("./examples/SPTG6.txt");
    cout << "**** Obtained final value for SPTG6 ****" << endl;
    sptg6->show();
    valueIteration.getValue(sptg6, false, true);
    CHECK(*sptg6->getAState("lf")->getValueFunction() == expected0);
    CHECK(*sptg6->getAState("l3")->getValueFunction() == expected4);
    CHECK(*sptg6->getAState("l2")->getValueFunction() == expected5);
    CHECK(*sptg6->getAState("l1")->getValueFunction() == expected7);
    delete sptg6;

    PTG* sptg7 = new PTG("./examples/SPTG7.txt");
    cout << "**** Obtained final value for SPTG7 ****" << endl;
    sptg7->show();
    valueIteration.getValue(sptg7, false, true);
    CHECK(*sptg7->getAState("lf")->getValueFunction() == expected0);
    CHECK(*sptg7->getAState("l3")->getValueFunction() == expected4);
    CHECK(*sptg7->getAState("l2")->getValueFunction() == expected5);
    CHECK(*sptg7->getAState("l1")->getValueFunction() == expected8);
    delete sptg7;

    PTG* sptg8 = new PTG("./examples/SPTG8.txt");
    cout << "**** Obtained final value for SPTG8 ****" << endl;
    sptg8->show();
    valueIteration.getValue(sptg8, false, true);
    CHECK(*sptg8->getAState("lf")->getValueFunction() == expected0);
    CHECK(*sptg8->getAState("l3")->getValueFunction() == expected4);
    CHECK(*sptg8->getAState("l2")->getValueFunction() == expected5);
    CHECK(*sptg8->getAState("l1")->getValueFunction() == expected9);
    delete sptg8;

}


TEST_CASE("RegionPTG"){
    PTG* sptg1 = new PTG("./examples/SPTG1.txt");
    RegionPTG* rptg1 = new RegionPTG(sptg1);
    rptg1->prunedPTG("(l0, [0, 0])");
    rptg1->show();
    regionValueIteration.getValue(rptg1, false, true);
    CHECK(*rptg1->getAState("(lf, [0, 0])")->getValueFunction() == expected0);
    CHECK(*rptg1->getAState("(lf, [0, 1])")->getValueFunction() == expected0);
    CHECK(*rptg1->getAState("(lf, [1, 1])")->getValueFunction() == expected0);
    CHECK(*rptg1->getAState("(l0, [0, 0])")->getValueFunction() == expected1);
    delete sptg1;
    delete rptg1;
}

TEST_CASE("UnfoldingPTG"){
    PTG* ptg1 = new PTG("./examples/PTG0.txt");
    RegionPTG* rptg1 = new RegionPTG(ptg1);
    delete ptg1;

    rptg1->prunedPTG("(l1, [0, 0])");
    UnfoldingPTG* uptg = new UnfoldingPTG(rptg1, 3, "(l1, [0, 0])");
    delete rptg1;

    unfoldingValueIteration.getValue(uptg, false, true);
    CHECK(*uptg->getAState("(l1, [0, 0])")->getValueFunction() == expected10);
    delete uptg;
}