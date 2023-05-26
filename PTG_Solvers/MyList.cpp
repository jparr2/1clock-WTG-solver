//
// Created by julie on 29/12/22.
//

#include "MyList.h"
#include "State.hpp"
#include "Transition.hpp"
#include "UnfoldingState.h"
#include "UnfoldingTransition.h"

template<class Element>
MyList<Element>::MyList() {
    myList = new list<Element*>();
}

template<class Element>
MyList<Element>::~MyList() {
    myList->clear();
    delete myList;
}

template<class Element>
void MyList<Element>::show()  {
    for (auto element : *myList) {
        element->show();
        cout << endl;
    }
}

template<class Element>
void MyList<Element>::allSetUsed(bool isUsed){
    for (Element* element : *myList){
        element->setUsed(isUsed);
    }
}

template<class Element>
bool MyList<Element>::contains(Element* element) const{
    bool result = false;
    for (auto* elementList : *myList){
        result |= (*elementList == *element);
    }
    return result;
}
template<class Element>
bool MyList<Element>::containsString(string label) {
    bool result = false;
    for (auto* element : *myList){
        result |= (element->getLabel() == label);
    }
    return result;
}


template<class Element>
bool MyList<Element>::operator==(const MyList<Element>& listElement) const {
    bool result = true;
    for (auto* element : *myList){result &= listElement.contains(element);}
    for (auto* element : *listElement.myList){result &= contains(element);}
    return result;
}

template<class Element>
void MyList<Element>::add(Element* element) {
    myList->push_back(element);
}
template<class Element>
void MyList<Element>::erase(Element& element) {
    auto it = myList->begin();
    while (it != myList->end()) {
        Element* current = *it;
        if (element == *current){
            myList->erase(it);
            return;
        }
        it++;
    }
}
template<class Element>
Element* MyList<Element>::find(const string& label) {
    auto it = myList->begin();
    while (it != myList->end()) {
        Element* current = *it;
        if (label == current->getLabel()){
            myList->erase(it);
            return current;
        }
        it++;
    }
    return nullptr;
}

template<class Element>
list<Element*>* MyList<Element>::getList() {return myList;}

template<class Element>
void MyList<Element>::clear() {myList->clear();}

template<class Element>
void MyList<Element>::removeAll() {
    auto it = myList->begin();
    while (it != myList->end()){
        Element* current = *it;
        delete current;
        it++;
    }
}

template<class Element>
Element* MyList<Element>::getAElement(string label) {
    for (auto element: *myList){
        if (element->getLabel() == label) {
            return  element;
        }
    }
    return nullptr;
}

template<class Element>
int MyList<Element>::size() {return myList->size();}

template<class Element>
Element* MyList<Element>::getFirstElement() {return myList->front();}
template<class Element>
void MyList<Element>::removeFirstElement() {myList->pop_front();}

template<class Element>
MyList<Element>* MyList<Element>::copy() {
    MyList<Element>* result = new MyList<Element>();
    for (Element* element : *myList)
        result->add(new Element(element));
    return result;
}


template<class Element>
void MyList<Element>::showInline() {
    cout << "{";
    for (Element* element: *myList) {
        element->show();
        cout << ", ";
    }
    cout << "}";
}

template<class Element>
string MyList<Element>::toString() {
    string result = "";
    for (Element* element : *myList){
        result += element->toString();
    }
    return result;
}




template class MyList<State>;
template class MyList<Transition>;
template class MyList<UnfoldingState>;
template class MyList<UnfoldingTransition>;
