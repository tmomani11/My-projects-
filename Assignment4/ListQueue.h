#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include "DblList.h"
#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T>
class ListQueue{
public:
  ListQueue();
  ~ListQueue();
  int size();
  bool isEmpty();
  void add(T c);
  T remove();
  T peek();
  void print();

private:
  DblList<T>* theList;

};

template <typename T>
ListQueue<T>::ListQueue(){
  theList = new DblList<T>();
}


template <typename T>
ListQueue<T>::~ListQueue(){
  delete theList;
}

template <typename T>
int ListQueue<T>::size(){
  return theList->getSize();
}

template <typename T>
bool ListQueue<T>::isEmpty(){
  return theList->isEmpty();
}


template <typename T>
void ListQueue<T>::add(T c){
  theList->addBack(c);
}

template <typename T>
T ListQueue<T>::remove(){
  try{
  return theList->removeFront();
  } 
  catch (exception& e)
  {
    cout << "Standard exception: " << e.what() << endl;
  } 
}

template <typename T>
T ListQueue<T>::peek(){
  try
  {
    return theList->get(0);
  }
  catch(const std::exception& e)
  {
    cout << e.what() << '\n';
  }
}

template <typename T>
void ListQueue<T>::print(){
  theList->print();
}

#endif
