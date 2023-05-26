//
// Created by julie on 11/08/22.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "./../PTG_Solvers/Region.h"

TEST_CASE("Constructor") {
    CHECK_THROWS_WITH(Region(1, 0), "Region constructor : bad interval as inf <= sup");
    CHECK_THROWS_WITH(Region(-1, 0), "Region constructor : bad interval as inf >=0");
}

TEST_CASE("Getters") {
    Region reg0;
    Region reg1 = Region(2, 5);

    reg0.show();
    CHECK(reg0.getInf() == 0);
    CHECK(reg0.getSup() == 1);
    CHECK(reg0.toString() == "[0, 1]");

    reg1.show();
    CHECK(reg1.getInf() == 2);
    CHECK(reg1.getSup() == 5);
    CHECK(reg1.toString() == "[2, 5]");
}

TEST_CASE("Operator"){
    Region reg0;
    Region reg1 = Region(2, 5);
    Region reg2 = Region(0, 1);

    CHECK(reg0 == reg2);
    CHECK_FALSE(reg0 == reg1);
    CHECK(reg0 <= reg1);
    CHECK(reg0 <= reg2);
    CHECK(reg0 < reg1);
    CHECK_FALSE(reg0 < reg2);
    CHECK_FALSE(reg1 <= reg0);
}

TEST_CASE("Set of regions"){
    Region reg0;
    Region reg1 = Region(2, 5);
    Region reg2 = Region(0, 1);

    set<Region> regions1 = set<Region>();
    set<Region> regions2 = set<Region>();
    set<Region> regions3 = set<Region>();

    regions1.insert(reg0);
    regions2.insert(reg0);
    regions3.insert(reg0);
    regions2.insert(reg1);
    regions3.insert(reg1);
    regions2.insert(reg2);
    regions3.insert(reg2);

    CHECK_FALSE(equalSetRegion(regions1, regions2));
    CHECK(equalSetRegion(regions2, regions3));
}