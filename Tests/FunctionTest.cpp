//
// Created by julie on 25/03/2021.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "./../PTG_Solvers/Function.hpp"

Fraction frac_nul = Fraction(); // 0
Fraction frac_2_5 = Fraction(2, 5); // 2/5
Fraction frac_1_2 = Fraction(8, 16); // 1/2
Fraction frac_4_5 = Fraction(4, 5); // 4/5
Fraction frac_1 = Fraction(1); //1
Fraction frac_8_5 = Fraction(8, 5); // 8/5
Fraction frac_2 = Fraction(2); // 2
Fraction frac_infpos = Fraction(true); // +infty

Point point1 = Point(frac_2_5, frac_1_2); // (2/5, 1/2)
Point point2 = Point(frac_4_5, frac_1); // (4/5, 1)
Point point3 = Point(frac_1, frac_2); // (1, 2)
Point point4 = Point(frac_nul, frac_2_5); // (0, 2/5)
Point point5 = Point(frac_8_5, frac_nul); // (8/5, 0)
Point point6 = Point(frac_8_5, frac_2); // (8/5, 2)
Point point_inf = Point(frac_infpos, frac_infpos); // (+infty, +infty)

Line line1 = Line(frac_1, frac_nul, frac_nul, frac_1); // x
Line line2 = Line(-frac_1, frac_1, frac_nul, frac_1); // 1 - x
Line line3 = Line(); // 0
Line line4 = Line(-frac_2, frac_1_2, frac_nul, frac_1); // 1/2 - 2x

list<Point> list1 = {point1, point2, point3, point4};
list<Point> list2 = {point1, point5, point3, point4};
list<Line> list3 = {line1, line2, line3, line4};

Function function0 = Function();
Function function1 = Function(&list1, true);
Function function2 = Function(&list2, false);
//Function function3 = Function(&list3, frac_nul, frac_1, true);
//Function function4 = Function(&list3, frac_nul, frac_8_5, false);
Function function5 = Function(&list1, true);
Function function6 = Function(&list1, false);


TEST_CASE("Show"){
    function1.show(true);
    function2.show(true);
//    function3.show();
//    function4.show();
    function5.show(false);
    function6.show(false);
}
TEST_CASE("Constructors and getters") {

    SUBCASE("getFunctionPoint") {
        list<Point> list4 = {Point(frac_nul, frac_1), Point(frac_1_2, frac_1_2), Point(frac_8_5, frac_8_5)};
        list<Point> list5 = {Point(frac_nul, frac_nul), Point(Fraction(1, 4), frac_nul),
                             Point(frac_1, -Fraction(3, 2))};

        list<Point> points_tmp = function1.getFunctionPoint();
        CHECK(equalListPoint(&points_tmp, &list1));
    }

    SUBCASE("getFunctionLine") {
        Line line5 = Line(Fraction(1, 4), frac_2_5, frac_nul, frac_1);
        Line line6 = Line(Fraction(5, 4), frac_nul, frac_nul, frac_1);
        Line line7 = Line(Fraction(5), -Fraction(3), frac_nul, frac_1);
        Line line8 = Line(-Fraction(10, 3), Fraction(16, 3), frac_nul, frac_1);
        Line line9 = Line(Fraction(5, 2), -frac_1_2, frac_nul, frac_1);
        list<Line> list4 = {line5, line6, line7};
        list<Line> list5 = {line5, line8, line9};
        list<Line> list6 = {line3, line4};

        list<Line> lines_tmp = function1.getFunctionLine();
        CHECK(equalListLine(&lines_tmp, &list4));
        lines_tmp = function2.getFunctionLine();
        CHECK(equalListLine(&lines_tmp, &list5));
    }

    SUBCASE("getStart and getEnd") {
        CHECK(function1.getStart() == point4);
        CHECK(function2.getStart() == point4);

        CHECK(function1.getEnd() == point3);
        CHECK(function2.getEnd() == point5);
    }
}
TEST_CASE("Others getters"){
    SUBCASE("getPointClock") {
        CHECK(function1.getPointClock(frac_1) == point3);
        CHECK_THROWS_WITH(function1.getPointClock(frac_8_5), "Function : any point with this clock");
    }

    SUBCASE("getValue") {
        CHECK_THROWS_WITH(function1.getValueClock(-frac_2), "Function : clock is not in the domain");
        CHECK_THROWS_WITH(function1.getValueClock(frac_2), "Function : clock is not in the domain");
    }


}
TEST_CASE("Function manipulation"){
    Point point_tmp = function1.nextPoint(Fraction(2, 5));
    CHECK(point_tmp == point2);
    CHECK(function1.nextPoint(frac_1) == point_inf);
    CHECK(function1.nextPoint(frac_infpos) == point_inf);

    CHECK(function1.containsPoint(frac_1));
    CHECK_FALSE(function1.containsPoint(frac_8_5));

    list<Point> list = {Point(Fraction(0), Fraction(-1)), Point(Fraction(1), Fraction(0))};
    Function function8 = Function(&list, true);
}
TEST_CASE("Min/Max functions"){
    Line line5 = Line(Fraction(2, 3), Fraction(), frac_nul, frac_1); // 2/3x
    Line line6 = Line(-Fraction(1, 3), Fraction(1), frac_nul, frac_1); // 1 - 1/3x

    list<Line> list4 = {line1, line2};
    list<Line> list5 = {line5, line6};
    list<Line> list6 = {line5, line2, line6};
    list<Line> list7 = {line6, line1};

    Function function7 = Function(&list4, true);
    Function function8 = Function(&list5, true);
    Function function9 = Function(&list6, true);
    Function function10 = Function(&list7, false);

    Function* min = minFunction(&function7, &function8);
    CHECK(*min == function9);

    Function* max = maxFunction(&function7, &function8);
    CHECK(*max == function10);

}

