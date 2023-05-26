//
// Created by julie on 23/03/2021.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "./../PTG_Solvers/Point.hpp"
#include <iostream>


TEST_CASE("Display functions"){
    Fraction clock = Fraction(1, 2);
    Fraction valNeg = Fraction(-1, 4);
    Fraction valPos = Fraction(4);
    Fraction valInfNeg = Fraction(false);

    Point point1 = Point(clock, valPos);
    Point point2 = Point(clock, valNeg);
    Point point4 = Point(clock, valInfNeg);
    list<Point> pointsList1 = {point1, point2, point4};
    list<Point>* pointsList2 = new list<Point>;

    point1.show();
    std::cout << std::endl;
    point2.show();
    std::cout << std::endl;
    point4.show();
    std::cout << std::endl;
    showListPoint(&pointsList1);
    showListPoint(pointsList2);

    pointsList1.clear();
    pointsList2->clear();
    delete pointsList2;
}

TEST_CASE("Getters"){
    Fraction clock = Fraction(1, 2);
    Fraction valNeg = Fraction(-1, 4);
    Fraction valInfNeg = Fraction(false);
    Fraction valInfPos = Fraction(true);
    Fraction valPos = Fraction(4);

    Point point1 = Point(clock, valPos);
    Point point2 = Point(clock, valNeg);
    Point point3 = Point(clock, valInfPos);
    Point point4 = Point(clock, valInfNeg);
    Point p;

    p = point1;
    CHECK(p.getClock() == clock);
    CHECK(p.getValue() == valPos);
    CHECK_FALSE(p.getInfinite());

    CHECK(point2.getValue() == valNeg);
    CHECK(point3.getValue() == valInfPos);
    CHECK(point4.getValue() == valInfNeg);
    CHECK(point4.getInfinite());

}

TEST_CASE("Comparator operations"){
    Fraction clock1 = Fraction(1, 2);
    Fraction clock2 = Fraction(2);
    Fraction valNeg = Fraction(-1, 4);
    Fraction valPos = Fraction(4);
    Fraction valInfPos = Fraction(true);

    Point point1 = Point(clock1, valPos);
    Point point2 = Point(clock1, valNeg);
    Point point3 = Point(clock1, valInfPos);
    Point point6 = Point(clock2, valPos);
    Point point7 = Point(clock2, valNeg);
    Point point8 = Point(clock2, valInfPos);

    SUBCASE("Equality or not"){
        CHECK(point1 == point1);
        CHECK_FALSE(point1 == point2);
        CHECK_FALSE(point1 == point6);
        CHECK_FALSE(point1 == point7);

        CHECK_FALSE(point1 != point1);
        CHECK(point1 != point2);
        CHECK(point1 != point6);
        CHECK(point1 != point7);
    }

    SUBCASE("Less (or equal) than"){
        CHECK_FALSE(point1 < point1);
        CHECK(point2 < point1);
        CHECK(point1 < point3);
        CHECK(point1 < point6);
        CHECK(point1 < point8);
        CHECK_FALSE(point6 < point1);
        CHECK_FALSE(point7 < point1);

        CHECK(point1 <= point1);
        CHECK(point2 <= point1);
        CHECK(point1 <= point3);
        CHECK(point1 <= point6);
        CHECK(point1 <= point8);
        CHECK_FALSE(point6 <= point1);
        CHECK_FALSE(point7 <= point1);
    }

    SUBCASE("Greater (or equal) than"){
        CHECK_FALSE(point1 > point1);
        CHECK_FALSE(point2 > point1);
        CHECK_FALSE(point1 > point3);
        CHECK_FALSE(point1 > point6);
        CHECK_FALSE(point1 > point8);
        CHECK(point6 > point1);
        CHECK(point7 > point1);
        CHECK(point6 > point7);

        CHECK(point1 >= point1);
        CHECK_FALSE(point2 >= point1);
        CHECK_FALSE(point1 >= point3);
        CHECK_FALSE(point1 >= point6);
        CHECK_FALSE(point1 >= point8);
        CHECK(point6 >= point1);
        CHECK(point7 >= point1);
        CHECK(point6 >= point7);
    }

}

TEST_CASE("List of points manipulation"){
    Fraction clock = Fraction(1, 2);
    Fraction valNeg = Fraction(-1, 4);
    Fraction valPos = Fraction(4);
    Fraction valInfNeg = Fraction(false);
    Fraction valInfPos = Fraction(true);

    Point point1 = Point(clock, valPos);
    Point point2 = Point(clock, valNeg);
    Point point3 = Point(clock, valInfPos);
    Point point4 = Point(clock, valInfNeg);

    list<Point> pointsList1 = {point1, point2, point3};
    list<Point> pointsList2 = {point1, point2};
    list<Point> pointsList3 = {point1, point2, point3, point4};
    list<Point> pointsList4 = {};
    list<Point> pointsList5 = {point1, point2, point3};

    CHECK_FALSE(containsPoint(&pointsList1, point4));
    CHECK_FALSE(containsPoint(&pointsList4, point2));
    CHECK(containsPoint(&pointsList1, point2));

    CHECK(equalListPoint(&pointsList1, &pointsList1));
    CHECK(equalListPoint(&pointsList1, &pointsList5));
    CHECK_FALSE(equalListPoint(&pointsList1, &pointsList2));
    CHECK_FALSE(equalListPoint(&pointsList1, &pointsList3));
    CHECK_FALSE(equalListPoint(&pointsList1, &pointsList4));

    CHECK(containsPointClock(&pointsList1, clock));
    CHECK_FALSE(containsPointClock(&pointsList4, clock));
    CHECK_FALSE(containsPointClock(&pointsList1, Fraction()));

}