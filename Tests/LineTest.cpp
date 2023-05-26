//
// Created by julie on 31/03/2021.
// TODO : penser à isDomain* et isInteriorDomaine* ...
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "./../PTG_Solvers/Line.hpp"

Fraction frac0 = Fraction();
Fraction frac1 = Fraction(1);
Fraction frac2 = Fraction(2);
Fraction frac3 = Fraction(1, 2);
Fraction fracInf = Fraction(true);

Point point1 = Point(frac0, frac1);  // (0, 1)
Point point2 = Point(frac1, frac0);  // (1, 0)
Point point3 = Point(frac0, frac0); // (0, 0)
Point point4 = Point(frac1, frac1);   // (1, 1)
Point point5 = Point(frac1, frac2);   // (1, 2)
Point point6 = Point(fracInf, frac0); // (+inf, 0)
Point point7 = Point(frac2, frac0); // (2, 0)

Line line1 = Line();                // 0 dans [0,+inf]
Line line2 = Line(frac1, frac0, frac0, frac2);   // x dans [0, 2]
Line line3= Line(point1, point2);   // 1- x  dans [0, 1]
Line line4 = Line(point3, point4);  // x dans [0, 1]
Line line5 = Line(point1, point5);  // x + 1 dans [0, 1]
Line line0 = Line(frac0, fracInf, frac0, frac1); // +infinite dans [0, 1]
Line line21 = Line(frac1, frac0, frac0, frac1);   // x dans [0, 1]
Line line10 = Line(point7, point6); // 0 dans [2, Inf]
Line line11 = Line(point2, point6); // 0 dans [1, Inf]

TEST_CASE("Show"){
    list<Line> list1 = {line1, line2, line3, line5};

    line1.show();
    cout << endl;
    line2.show();
    cout << endl;
    line3.show();
    cout << endl;
    line0.show();
    cout << endl;

    showListLine(&list1);

    list1.clear();
}

TEST_CASE("Getters"){
    CHECK(line0.getSlope() == frac0);
    CHECK(line1.getSlope() == frac0);
    CHECK(line2.getSlope() == frac1);
    CHECK(line3.getSlope() == -frac1);
    CHECK(line4.getSlope() == frac1);

    CHECK(line0.getIntercept() == fracInf);
    CHECK(line1.getIntercept() == frac0);
    CHECK(line2.getIntercept() == frac0);
    CHECK(line3.getIntercept() == frac1);
    CHECK(line4.getIntercept() == frac0);

    CHECK(line0.getValueClock(frac3) == fracInf);
    CHECK(line1.getValueClock(frac3) == frac0);
    CHECK(line2.getValueClock(frac3) == frac3);
    CHECK(line3.getValueClock(frac3) == frac3);
}

TEST_CASE("Comparison"){
    CHECK(line1 == line1);
    CHECK(line4 == line21);
    CHECK_FALSE(line4 == line5);

    CHECK_FALSE(line1.isParallel(line2));
    CHECK(line2.isParallel(line4));
    CHECK(line2.isParallel(line5));

    Point pointInf = Point(Fraction(true), Fraction(true));
    CHECK(line1.getIntersectionPoint(line2) == point3);
    CHECK(line2.getIntersectionPoint(line3) == Point(frac3, frac3));
    CHECK(line2.getIntersectionPoint(line5) == pointInf);
    CHECK(line2.getIntersectionPoint(line4) == pointInf);
    CHECK(line3.getIntersectionPoint(line5) == Point(Fraction(), Fraction(1)));

    Line line6 = Line(-frac1, -frac3, frac0, frac1); // -x - 1/2
    CHECK(line1.selectLine(line5, true) == line1);
    CHECK(line1.selectLine(line5, false) == line5);
    CHECK(line1.selectLine(line2, true) == line1);
    CHECK(line1.selectLine(line2, false) == line2);
    CHECK(line2.selectLine(line6, true) == line6);
    CHECK(line2.selectLine(line6, false) == line2);
}

TEST_CASE("List manipulation"){
    Line line6 = Line(frac3, frac2, frac0, frac1); // 1/2x + 2
    list<Line> list1 = {line1, line2, line3, line5};
    list<Line> list21 = {line1, line21, line3, line5};
    list<Line> list2 = {};

    SUBCASE("Contains and equal"){
        CHECK(containsLine(&list1, line3));
        CHECK(containsLine(&list21, line4));
        CHECK_FALSE(containsLine(&list1, line6));
        CHECK_FALSE(containsLine(&list2, line6));

        CHECK_FALSE(equalListLine(&list1, &list2));
        CHECK(equalListLine(&list1, &list1));
        CHECK(equalListLine(&list2, &list2));
    }

    list<Line> list3 = {line1, line2};
    list<Line> list4 = {line1};
    list<Line> list5 = {line2};
    list<Line> list6 = {line5};
    list<Line> list7 = {line1, line3};
    list<Line> list8 = {line10, line2};
    list<Line> list9 = {line5, line11};


    SUBCASE("getBoundListLine"){
        list<Fraction> listattenidng1 = {frac0, frac1, frac2, fracInf};
        list<Fraction> listattenidng2 = {frac0, frac2, fracInf};
        list<Fraction> listattenidng3 = {frac0, frac1, fracInf};
        list<Fraction> listattending4 = {};

        auto* listBound1 = getBoundListLines(&list1);
        CHECK(equalListFrac(listBound1, &listattenidng1));
        listBound1->clear();
        delete listBound1;

        auto* listBound2 = getBoundListLines(&list3);
        CHECK(equalListFrac(listBound2, &listattenidng2));
        listBound2->clear();
        delete listBound2;

        auto* listBound3 = getBoundListLines(&list7);
        showListFrac(listBound3);
        CHECK(equalListFrac(listBound3, &listattenidng3));
        listBound3->clear();
        delete listBound3;

        auto* listBound4 = getBoundListLines(&list2);
        CHECK(equalListFrac(listBound4, &listattending4));
        listBound4->clear();
        delete listBound4;

        listattenidng1.clear();
        listattenidng2.clear();
        listattenidng3.clear();
        listattending4.clear();
    }

    SUBCASE("divideLine"){
        Line line11 = Line(point3, point2);
        Line line12 = Line(point2, point7);
        Line line13 = Line(point7, point6);
        Line line14 = Line(point2, point6);
        Line line23 = Line(frac1, frac0, frac0, frac1);
        Line line22 = Line(frac1, frac0, frac1, frac2);
        list<Line> listAttending1 = {line3, line11, line14};
        list<Line> listAttending2 = {};
        list<Line> listAttending3 = {line3, line5, line11, line12, line13, line23, line22};

        list<Line>* divide1 = divideLine(&list7);
        CHECK(equalListLine(divide1, &listAttending1));
        divide1->clear();
        delete divide1;

        list<Line>* divide2 = divideLine(&list2);
        CHECK(equalListLine(divide2, &listAttending2));
        divide2->clear();
        delete divide2;

        list<Line>* divide3 = divideLine(&list1);
        CHECK(equalListLine(divide3, &listAttending3));
        divide3->clear();
        delete divide3;

        listAttending1.clear();
        listAttending2.clear();
        listAttending3.clear();
    }

    SUBCASE("mergeListLine"){
        Line line11 = Line(point3, point2);
        Line line12 = Line(point2, point7);
        Line line13 = Line(point7, point6);
        Line line14 = Line(point2, point6);
        Line line23 = Line(frac1, frac0, frac0, frac1);
        Line line22 = Line(frac1, frac0, frac1, frac2);
        list<Line> listAttending1 = {line3, line11, line14};
        list<Line> listAttending2 = {};
        list<Line> listAttending3 = {line3, line5, line11, line12, line13, line23, line22};

        list<Line>* merge1 = mergeListLine(&listAttending1);
        CHECK(equalListLine(merge1, &list7));
        merge1->clear();
        delete merge1;

        list<Line>* merge2 = mergeListLine(&listAttending2);
        CHECK(equalListLine(merge2, &list2));
        merge2->clear();
        delete merge2;

        list<Line>* merge3 = mergeListLine(&listAttending3);
        CHECK(equalListLine(merge3, &list1));
        merge3->clear();
        delete merge3;

        listAttending1.clear();
        listAttending2.clear();
        listAttending3.clear();
    }

    SUBCASE("selectListLine"){
        list<Line>* result1 = selectLine(&list3, true);
        CHECK(equalListLine(result1, &list4));
        result1->clear();
        delete result1;

        list<Line>* result2 = selectLine(&list3, false);
        CHECK(equalListLine(result2, &list8));
        result2->clear();
        delete result2;

        list<Line>* result3 = selectLine(&list21, true);
        CHECK(equalListLine(result3, &list4));
        result3->clear();
        delete result3;

        auto result4 = selectLine(&list21, false);
        CHECK(equalListLine(result4, &list9));
        result4->clear();
        delete result4;
    }
}