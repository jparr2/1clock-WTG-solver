//
// Created by julie on 16/08/22.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "./../PTG_Solvers/RegionPTG.h"
#include "./../PTG_Solvers/UnfoldingPTG.h"
#include <iostream>


TEST_CASE("Simple PTG"){
    PTG* ptg1 = new PTG("./examples/SPTG1.txt");
    RegionPTG* rptg1 = new RegionPTG(ptg1);
    delete ptg1;
    rptg1->prunedPTG("(l0, [0, 0])");
    rptg1->show();
    UnfoldingPTG uptg = UnfoldingPTG(rptg1, 3, "(l0, [0, 0])");

    uptg.show();
    delete rptg1;
}

TEST_CASE("makePTG"){
    State* state1 = new State("l1", Owner::Min, 14, Fraction(0));
    State* state2 = new State("l2", Owner::Max, -4, Fraction(1));
    State* state3 = new State("l3", Owner::Target, 0, Fraction(2));

    Guard guard1 = Guard(Fraction(), Fraction(1));
    Guard guard2 = Guard(Fraction(1), Fraction(2), true, false);

    Transition transition1 = Transition(state1, 7, guard1, true, state2, "t1");
    Transition transition2 = Transition(state1, 0, guard2, false, state3, "t2");
    Transition transition3 = Transition(state2, -4, guard1, true, state3, "t3");

    MyList<Transition> list1 = MyList<Transition>();
    list1.add(&transition1);
    list1.add(&transition2);
    list1.add(&transition3);

    PTG ptg = PTG(&list1, &transition1);
    ptg.show();
    delete state1;
    delete state2;
    delete state3;
}

TEST_CASE("PTG"){
    PTG* ptg1 = new PTG("./examples/PTG0.txt");
    RegionPTG* rptg1 = new RegionPTG(ptg1);
    delete ptg1;
    rptg1->prunedPTG("(l1, [0, 0])");
    UnfoldingPTG* uptg = new UnfoldingPTG(rptg1, 3, "(l1, [0, 0])");

    rptg1->show();
    uptg->show();

    Region reg = Region(0,0);
    Region reg1 = Region(1,1);

    MyList<Transition>* transitionPTG = rptg1->getTransitions();
    Transition trans1 = transitionPTG->find("rt0");
    Transition trans2 = transitionPTG->find("rt2");
    Transition trans3 = transitionPTG->find("rt3");
    Transition trans5 = transitionPTG->find("rt5");
    Transition trans6 = transitionPTG->find("rt6");

    Path path = Path();
    Path path1 = Path(&path, &trans1);
    Path path2 = Path(&path1, &trans6);
    Path path3 = Path(&path2, &trans2);
    Path path4 = Path(&path3, &trans6);

    int sizePTG = rptg1->getSize();
    int maxWeightLoc = rptg1->getMaxWeightLoc();
    int maxWeightTrans = rptg1->getMaxWeightTrans();
    Fraction maxFinalWeight = rptg1->getMaxWeightFin();
    int maxClock = rptg1->getMaxClock();
    Fraction maxWeightFin = Fraction(sizePTG * maxWeightTrans + maxClock * maxWeightLoc) + maxFinalWeight;

    UnfoldingState lMin = UnfoldingState("lMin", 0, Owner::Target, reg, &path, Fraction(false));
    UnfoldingState lMax = UnfoldingState("lMax", 0, Owner::Target, reg, &path, Fraction(maxWeightFin));
    UnfoldingState lInfty = UnfoldingState("lInfty", 0, Owner::Target, &path, Fraction(true));
    UnfoldingState lTarget = UnfoldingState("(l3, [1, 1])", 0, Owner::Target, reg1, &path, Fraction(0));
    UnfoldingState lorigin = UnfoldingState("(l1, [0, 0])", 14, Owner::Min, reg, &path, Fraction());
    UnfoldingState ls5 = UnfoldingState("(l2, [0, 0])-s5", -4, Owner::Max, reg, &path1, Fraction());
    UnfoldingState ls6 = UnfoldingState("(l1, [1, 1])-s6", 14, Owner::Min, reg1, &path2, Fraction());
    UnfoldingState ls7 = UnfoldingState("(l2, [0, 0])-s7", -4, Owner::Max, reg, &path3, Fraction());
    UnfoldingState ls8 = UnfoldingState("(l1, [1, 1])-s8", 14, Owner::Min, reg, &path4, Fraction());

    MyList<UnfoldingState> statesU = MyList<UnfoldingState>();
    statesU.add(&lMin);
    statesU.add(&lMax);
    statesU.add(&lInfty);
    statesU.add(&lTarget);
    statesU.add(&lorigin);
    statesU.add(&ls5);
    statesU.add(&ls6);
    statesU.add(&ls7);
    statesU.add(&ls8);
    CHECK(*uptg->getStates() == statesU);

    Guard guard1 = Guard(Fraction(0), Fraction(0));
    Guard guard2 = Guard(Fraction(1), Fraction(1));

    UnfoldingTransition t1 = UnfoldingTransition(&lorigin, 7, guard1, true, &ls5, "t1");
    UnfoldingTransition t2 = UnfoldingTransition(&lorigin, 0, guard2, false, &lTarget, "t2");
    UnfoldingTransition t3 = UnfoldingTransition(&ls5, 0, guard2, false, &ls6, "t3");
    UnfoldingTransition t4 = UnfoldingTransition(&ls6, 7, guard2, true, &ls7, "t4");
    UnfoldingTransition t5 = UnfoldingTransition(&ls6, 0, guard2, false, &lTarget, "t5");
    UnfoldingTransition t6 = UnfoldingTransition(&ls7, 0, guard2, false, &ls8, "t6");
    UnfoldingTransition t7 = UnfoldingTransition(&ls8, 7, guard2, true, &lMax, "t7");
    UnfoldingTransition t8 = UnfoldingTransition(&ls8, 0, guard2, false, &lTarget, "t8");

    MyList<UnfoldingTransition> transU = MyList<UnfoldingTransition>();
    transU.add(&t1);
    transU.add(&t2);
    transU.add(&t3);
    transU.add(&t4);
    transU.add(&t5);
    transU.add(&t6);
    transU.add(&t7);
    transU.add(&t8);
    CHECK(transU == *uptg->getTransitions());

    statesU.clear();
    transU.clear();
    transitionPTG->clear();
    //delete transitionPTG;
    delete uptg;
    delete rptg1;
}

