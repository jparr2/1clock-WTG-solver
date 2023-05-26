//
// Created by julie on 26/12/22.
//

#ifndef CODE_PATH_H
#define CODE_PATH_H

#include <string>
#include <list>
#include <iostream>
#include "Transition.hpp"
#include "MyList.h"
using namespace std;

class Path {
private:
    MyList<Transition>* path;

public:
    Path();
    Path(Transition* transition);
    Path(Path* old_path, Transition* transition);
    Path(Path* old_path);

    ~Path();

    MyList<Transition>* getPath();
    int size();
    State* getOrigin();

    bool contains(Transition* transition);
    MyList<Transition>* getListTransition(Transition* transition);

    void show();
    string toString();

    bool operator==(const Path& other_path) const;

    int sizeLastResetTransition();
};





#endif //CODE_PATH_H
