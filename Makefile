all:
	make ValIt

ValIt: Fraction.o State.o Guard.o Transition.o PTG.o Point.o Line.o Function.o ValueIteration.o main.o Region.o RegionPTG.o Path.o MyList.o UnfoldingPTG.o UnfoldingTransition.o UnfoldingState.o Owner.o
	g++ -W -Wextra -Wall -pedantic -o valIt Fraction.o State.o Guard.o Transition.o PTG.o Point.o Line.o Function.o ValueIteration.o main.o Region.o RegionPTG.o Path.o MyList.o UnfoldingPTG.o UnfoldingTransition.o UnfoldingState.o Owner.o

solver: Region.o
	g++ -W -Wextra -Wall -pedantic -o valIt Region.o

MyList.o: PTG_Solvers/MyList.cpp PTG_Solvers/MyList.h
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/MyList.cpp

Fraction.o: PTG_Solvers/Fraction.cpp PTG_Solvers/Fraction.hpp
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/Fraction.cpp

Point.o: PTG_Solvers/Point.cpp PTG_Solvers/Point.hpp
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/Point.cpp

Line.o: PTG_Solvers/Line.cpp PTG_Solvers/Line.hpp
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/Line.cpp

Function.o: PTG_Solvers/Function.hpp PTG_Solvers/Function.hpp
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/Function.cpp

State.o: PTG_Solvers/State.cpp PTG_Solvers/State.hpp
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/State.cpp

Owner.o: PTG_Solvers/Owner.cpp PTG_Solvers/Owner.h
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/Owner.cpp

Guard.o: PTG_Solvers/Guard.cpp PTG_Solvers/Guard.hpp
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/Guard.cpp

Transition.o: PTG_Solvers/Transition.cpp PTG_Solvers/Transition.hpp
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/Transition.cpp

PTG.o: PTG_Solvers/PTG.cpp PTG_Solvers/PTG.hpp
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/PTG.cpp

ValueIteration.o: PTG_Solvers/ValueIteration.cpp PTG_Solvers/ValueIteration.hpp
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/ValueIteration.cpp

Path.o: PTG_Solvers/Path.cpp PTG_Solvers/Path.h
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/Path.cpp

Region.o: PTG_Solvers/Region.h PTG_Solvers/Region.cpp
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/Region.cpp

RegionPTG.o: PTG_Solvers/RegionPTG.cpp PTG_Solvers/RegionPTG.h
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/RegionPTG.cpp

UnfoldingState.o: PTG_Solvers/UnfoldingState.cpp PTG_Solvers/UnfoldingState.h
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/UnfoldingState.cpp

UnfoldingTransition.o: PTG_Solvers/UnfoldingTransition.cpp PTG_Solvers/UnfoldingTransition.h
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/UnfoldingTransition.cpp

UnfoldingPTG.o: PTG_Solvers/UnfoldingPTG.h PTG_Solvers/UnfoldingPTG.cpp
	g++ -c -W -Wextra -Wall -pedantic PTG_Solvers/UnfoldingPTG.cpp

main.o: main.cpp
	g++ -c -W -Wextra -Wall -pedantic main.cpp

debug: Fraction.o State.o Guard.o Transition.o PTG.o Point.o Line.o Function.o ValueIteration.o main.o
	 g++ -W -Wextra -Wall -pedantic -g Fraction.o State.o Guard.o Transition.o PTG.o Point.o Line.o Function.o ValueIteration.o main.o

clean:
	rm -f *.o test output.txt


FractionTest.o: clean Tests/FractionTest.cpp Fraction.o
	g++ -c -W -Wextra -Wall -pedantic Tests/FractionTest.cpp
	g++ -W -Wextra -pedantic -o test Fraction.o FractionTest.o
	./test

PathTest.o: clean Tests/PathTest.cpp Path.o Transition.o State.o Region.o Guard.o Fraction.o Function.o Point.o Line.o MyList.o UnfoldingTransition.o UnfoldingState.o
	g++ -c -W -Wextra -Wall -pedantic Tests/PathTest.cpp
	g++ -W -Wextra -pedantic -o test Path.o PathTest.o Transition.o State.o Region.o Guard.o Fraction.o Function.o Point.o Line.o MyList.o UnfoldingTransition.o UnfoldingState.o
	./test

PointTest.o : clean Tests/PointTest.cpp Point.o Fraction.o
	g++ -c -W -Wextra -Wall -pedantic Tests/PointTest.cpp
	g++ -W -Wextra -pedantic -o test Fraction.o Point.o PointTest.o
	./test

LineTest.o: clean Tests/LineTest.cpp Line.o Fraction.o Point.o
	g++ -c -W -Wextra -Wall -pedantic Tests/LineTest.cpp
	g++ -W -Wextra -pedantic -o test Fraction.o Point.o Line.o LineTest.o
	./test

FunctionTest.o: clean Tests/FunctionTest.cpp Function.o Fraction.o Line.o Point.o
	g++ -c -W -Wextra -Wall -pedantic Tests/FunctionTest.cpp
	g++ -W -Wextra -pedantic -o test Fraction.o Point.o Line.o Function.o FunctionTest.o
	./test

StateTest.o: clean Tests/StateTest.cpp Function.o State.o Fraction.o Point.o Line.o Region.o Owner.o
	g++ -c -W -Wextra -Wall -pedantic Tests/StateTest.cpp
	g++ -W -Wextra -pedantic -o test Fraction.o Point.o Line.o Function.o State.o StateTest.o Region.o Owner.o
	./test

GuardTest.o : clean Tests/GuardTest.cpp Guard.o Fraction.o Region.o
	g++ -c -W -Wextra -Wall -pedantic Tests/GuardTest.cpp
	g++ -W -Wextra -pedantic -o test Fraction.o Guard.o GuardTest.o Region.o
	./test

TransitionTest.o: clean Tests/TransitionTest.cpp Transition.o Fraction.o Guard.o State.o Region.o Function.o Point.o Line.o Owner.o
	g++ -c -W -Wextra -Wall -pedantic Tests/TransitionTest.cpp
	g++ -W -Wextra -pedantic -o test Fraction.o Guard.o Region.o Point.o Line.o State.o Function.o Transition.o TransitionTest.o Owner.o
	./test

PTGTest.o : clean Tests/PTGTest.cpp PTG.o Region.o Point.o Line.o Function.o Guard.o Fraction.o State.o Transition.o Path.o Owner.o MyList.o UnfoldingState.o UnfoldingTransition.o
	g++ -c -W -Wextra -Wall -pedantic Tests/PTGTest.cpp
	g++ -W -Wextra -pedantic -o test Point.o Line.o Region.o Function.o Guard.o Fraction.o State.o Transition.o PTG.o PTGTest.o Path.o Owner.o MyList.o UnfoldingState.o UnfoldingTransition.o
	./test

ValueIterationTest.o: clean Tests/ValueIterationTest.cpp Line.o Fraction.o Point.o Function.o PTG.o State.o Transition.o Guard.o ValueIteration.o Owner.o Region.o Path.o RegionPTG.o MyList.o UnfoldingState.o UnfoldingTransition.o UnfoldingPTG.o
	g++ -c -W -Wextra -Wall -pedantic Tests/ValueIterationTest.cpp
	g++ -W -Wextra -pedantic -o test Fraction.o Point.o Line.o Function.o State.o Guard.o Transition.o PTG.o Region.o ValueIteration.o ValueIterationTest.o Owner.o Path.o RegionPTG.o MyList.o UnfoldingState.o UnfoldingTransition.o UnfoldingPTG.o
	./test

RegionTest.o: clean Tests/RegionTest.cpp Region.o Fraction.o
	g++ -c -W -Wextra -Wall -pedantic Tests/RegionTest.cpp
	g++ -W -Wextra -pedantic -o test Region.o RegionTest.o Fraction.o
	./test

RegionPTGTest.o : clean Tests/RegionPTGTest.cpp PTG.o Region.o Point.o Line.o Function.o Guard.o Fraction.o State.o Transition.o Path.o RegionPTG.o Owner.o MyList.o UnfoldingState.o UnfoldingTransition.o
	g++ -c -W -Wextra -Wall -pedantic Tests/RegionPTGTest.cpp
	g++ -W -Wextra -pedantic -o test Point.o Line.o Region.o Function.o Guard.o Fraction.o State.o Transition.o PTG.o Path.o RegionPTG.o RegionPTGTest.o Owner.o MyList.o UnfoldingState.o UnfoldingTransition.o
	./test

UnfoldingStateTest.o: clean Tests/UnfoldingStateTest.cpp Function.o State.o Fraction.o Point.o Line.o Region.o Owner.o Path.o Transition.o UnfoldingState.o Guard.o MyList.o UnfoldingTransition.o
	g++ -c -W -Wextra -Wall -pedantic Tests/UnfoldingStateTest.cpp
	g++ -W -Wextra -pedantic -o test Fraction.o Point.o Line.o Function.o State.o UnfoldingStateTest.o Region.o Owner.o Path.o Transition.o UnfoldingState.o Guard.o MyList.o UnfoldingTransition.o
	./test

UnfoldingTransitionTest.o: clean Tests/UnfoldingTransitionTest.cpp Transition.o Fraction.o Guard.o State.o Region.o Function.o Point.o Line.o Owner.o Path.o UnfoldingState.o UnfoldingTransition.o MyList.o
	g++ -c -W -Wextra -Wall -pedantic Tests/UnfoldingTransitionTest.cpp
	g++ -W -Wextra -pedantic -o test Fraction.o Guard.o Region.o Point.o Line.o State.o Function.o Transition.o UnfoldingTransitionTest.o Owner.o Path.o UnfoldingState.o UnfoldingTransition.o MyList.o
	./test

MyListTest.o: clean Tests/MyListTest.cpp Transition.o Fraction.o Guard.o State.o Region.o Function.o Point.o Line.o Owner.o Path.o UnfoldingState.o UnfoldingTransition.o MyList.o
	g++ -c -W -Wextra -Wall -pedantic Tests/MyListTest.cpp
	g++ -W -Wextra -pedantic -o test Fraction.o Guard.o Region.o Point.o Line.o State.o Function.o Transition.o MyListTest.o Owner.o Path.o UnfoldingState.o UnfoldingTransition.o MyList.o
	./test

UnfoldingPTGTest.o : clean Tests/UnfoldingPTGTest.cpp PTG.o Region.o Point.o Line.o Function.o Guard.o Fraction.o State.o Transition.o Path.o RegionPTG.o Owner.o UnfoldingState.o UnfoldingTransition.o UnfoldingPTG.o ValueIteration.o MyList.o
	g++ -c -W -Wextra -Wall -pedantic Tests/UnfoldingPTGTest.cpp
	g++ -W -Wextra -pedantic -o test Point.o Line.o Region.o Function.o Guard.o Fraction.o State.o Transition.o PTG.o Path.o RegionPTG.o UnfoldingPTGTest.o Owner.o UnfoldingState.o UnfoldingTransition.o UnfoldingPTG.o ValueIteration.o MyList.o
	./test