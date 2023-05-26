# Value Iteration on Priced Timed Games

__Author__ Julie Parreaux

This tool, written in C++, solves a PTG given by a text file. It implements some 
versions of the value iteration algorithm: the standard version that may not 
converge, a restrict version that compute only a given number of step of the 
algorithm, and the version on the unfolding game definied in [CONCUR'22].

## Compilation

To compile the C++ tool, the user can use the Makefile with the command `make`.

## Execution

According if the user wants to draw the value functions or not, two commands exists 
to solve a given PTG. 

###  Command without draw functions

When the user does not want to draw the functions, he can
directly used the C++ programm by calling the following command:

`./valIt [--show] [--slow] [--nb n] [--state label] [--reg] [--unfolding] file.txt`

with this following options
- `-show`: display the trace of the computation
- `-slow`: use the value iteration algorithm (use the value from the previous 
  iteration to compute the current value), otherwise we use an acceleration of 
  value iteration (use the current value can be computed in the same iteration to 
  compute the current value).
- `-nb n`: restrict to n the number of iterations on each state
- `-state label`: restrict display to the state labelled by *label*
- `-reg`: compute value iteration on the closed game (i.e. region game where gaurds and 
semantic are closed)
- `-unfolding`: compute value iteration on the unfolding from the state given by `-state` 
in the region `[0, 0]`. 
**Be careful this option is always used with the options `-state` and '-reg.**

###  Command with draw functions

When the user wants to draw the functions, he must use the 
Python3 programm by calling the following command:

`python3 main.py [--show] [--slow] [--nb n] [--state label] [--reg] [--unfolding label] file.txt`

with this following options
- `--show`: display the trace of the computation
- `--slow`: use the value iteration algorithm (use the value from the previous
  iteration to compute the current value), otherwise we use an acceleration of
  value iteration (use the current value can be computed in the same iteration to
  compute the current value).
- `--nb n`: restrict to n the number of iterations on each state
- `--state label`: restrict display to the state labelled by *label*
- `--reg`: compute value iteration on the closed game (i.e. region game where gaurds and
  semantic are closed)
- `--unfolding label`: compute value iteration on the unfolding from `label` 
in the region `[0, 0]`. 
**Be careful this option is always used with the option'-reg.**


### File format

The correct reading of the file is ensured if it respects the following format:

> PTG \
> States \
> l0 Min - 1 \
> l1 Max 2 \
> lf Target 0 \
> Transitions \
> l0 0 [1,1] false lf  \
> l1 -10 (0,1) true l0

which contains the name of the PTG, the list of states and the list of 
transitions. Each list is preceded by `States` and `Transitions` keyword,
and each of their element is given on a single line. A state is given by 
a list of element: `label owner weigth` where `owner` can be `Min`, `Max` 
or `Target`. A transition is given by a list of element: 
`origin weight guard reset destination` which `origin` and `destination` 
are the label of states in the transition, `guard` is an open or closed 
interval between two integers (that can be equal in closed case) 
to define the guard, `reset` is the boolean `true` or `false` if the 
clock is reset during the transition.

## Tests 
All class are tested with doctest. For functional tests, we use some example 
files given in `examples` repesitory.

First we have some SPTGs to test the decision on the wait.
- `SPTG0`: contains an unique state: a Target state
- `SPTG1`: contains two states (Min and Target) as Min had better wait
- `SPTG2`: contains two states (Min and Target) as Min has not interest in waiting
- `SPTG3`: contains two states (Max and Target) as Max had better wait
- `SPTG4`: contains two states (Max and Target) as Max has not interest in waiting

For each this SPTG (`SPTG1` to `SPTG4`), we define a PTG (`PTG1` to `PTG4`) 
with a reset on the transition between the state and the Target.

Next, we have some SPTGs to test the decision on the chosen transition.
- `SPTG5`: contains two states (Min and Target) as Min has not interest in waiting
- `SPTG6`: contains two states (Max and Target) as Max has not interest in waiting
- `SPTG7`: contains two states (Min and Target) as Min had better wait
- `SPTG8`: contains two states (Max and Target) as Max had better wait

Then, we have PTGs to test the cycle behaviour
- `Cycle0`: models a finite game with only a negative cycle.
- `Cycle1`: the same of `Cycle0' but with weight on state as Min and Max has not interest 
in waiting  
- `Cycle2`: a PTGs with reset such that value iteration does not converge in finite steps

Finally, we have a more complexe SPTG `SPTG9` that contains negative weight and some cycles.


## References
[CONCUR'22] B. Monmege, J. Parreaux, P.-A. Reynier:
_Decidability of One-Clock Weighted Timed Games with Arbitrary Weights_. CONCUR 2022
