//
// Created by julie on 29/12/22.
//

#ifndef CODE_MYLIST_H
#define CODE_MYLIST_H

#include <string>
#include <list>
#include <iostream>
using namespace std;

template <class Element> class MyList {
private:
    list<Element*>* myList;

public:
    MyList();
    ~MyList();
    void clear();
    void removeAll();

    // Getter
    list<Element*>* getList();
    int size();
    Element* getAElement(string label);
    Element* getFirstElement();
    MyList* copy();
    void removeFirstElement();

    // Operator
    bool operator==(const MyList<Element>& myList) const;

    // Display
    void show();
    void showInline();
    string toString();

    // List manipulation
    void add(Element* element);
    void erase(Element& element);
    bool contains(Element* element) const;
    bool containsString(string label);
    Element* find(const string& label);
    void allSetUsed(bool isReachable);


};



#endif //CODE_MYLIST_H
