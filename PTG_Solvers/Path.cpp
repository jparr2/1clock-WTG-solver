//
// Created by julie on 26/12/22.
//

#include "Path.h"

Path::Path(){
    path = new MyList<Transition>();
}
Path::Path(Transition* transition) {
    path = new MyList<Transition>();
    path->add(new Transition(transition));
}
Path::Path(Path* old_path, Transition* transition) {
    path = old_path->path->copy();
    path->add(new Transition(transition));
}
Path::Path(Path* old_path) {
    path = old_path->path->copy();
}

Path::~Path() {
    path->removeAll();
    delete path;
    path = nullptr;
}

void Path::show() {
    if (path != nullptr)
        path->showInline();
    else
        cout << "{}";
}
string Path::toString() {return path->toString();}

MyList<Transition>* Path::getPath() {return path;}
int Path::size() {return path->size();}
State* Path::getOrigin() {return path->getFirstElement()->getOrigin();}

bool Path::operator==(const Path &other_path) const {return (*path == *other_path.path);}
bool Path::contains(Transition* transition) {return (path->contains(transition));}

MyList<Transition>* Path::getListTransition(Transition* transition) {
    MyList<Transition>* result = new MyList<Transition>();
    auto it = path->getList()->begin();
    Transition* current = *it;
    while (it != path->getList()->end() && !(*current == *transition)){
        it++;
        current = *it;
    }
    it++;
    while (it != path->getList()->end()){
        current = *it;
        result->add(new Transition(current->getOrigin(), current->getWeight(),
                                   current->getGuard(), current->isReset(),
                                   current->getDestination(), current->getLabel()));
        it++;
    }
    return result;
}

int Path::sizeLastResetTransition() {
    int result = 0;
    auto it = path->getList()->end();
    bool find = false;
    while (!find && it != path->getList()->begin()) {
        it --;
        Transition* current = *it;
        if (current->isReset()){
            find = true;
        } else {
            result ++;
        }
    }
    return result;
}