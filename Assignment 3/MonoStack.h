#ifndef MONOSTACK_H
#define MONOSTACK_H

#include <iostream>

template <typename T>
class MonoStack{
public:
  MonoStack();
  MonoStack(int iSize, char o);
  ~MonoStack();
  int size();
  bool isEmpty();
  void push(T c);
  T pop();
  T pop(int pos);
  T peek();
  T peek(int pos);

private:
  T* stackArr;
  char typeStack;
  int count;
  int max;
  int top;
  bool isFull();

};

template <typename T>
MonoStack<T>::MonoStack(){ //O(1)
  top = -1;
  count = 0;
  max = 0;
  stackArr = new T[10];
  typeStack = 'i';
}

template <typename T>
MonoStack<T>::MonoStack(int iSize, char o){ //O(1)
  top = -1;
  count = 0;
  max = iSize;
  stackArr = new T[max];
  typeStack = o;
}

template <typename T>
MonoStack<T>::~MonoStack(){ //O(1)
  delete[] stackArr;
}

template <typename T>
int MonoStack<T>::size(){ //O(1)
  return count;
}

template <typename T>
bool MonoStack<T>::isEmpty(){ //O(1)
  return (count==0);
}

template <typename T>
bool MonoStack<T>::isFull(){ //O(1)
  return (count==max);
}

template <typename T>
void MonoStack<T>::push(T c){ //O(max) linear
  if(isFull()){
    T* temp = new T[2*max];
    for(int i = 0; i < max; ++i){

      temp[i] = stackArr[i];
    }
  }
  max *= 2;
  bool insertC = true;
  for(int i = 0; i < count; ++i){
    if(typeStack == 'i'){
        if(stackArr[i] < c){
            insertC = false;
        }
    } else if (typeStack == 'd'){
        if(stackArr[i] > c){
            insertC = false;
        }
    }
  }
    if (insertC){
    stackArr[++top] = c;
    ++count;
    }
}


template <typename T>
T MonoStack<T>::pop(){ //O(1)
  if(isEmpty()){
    throw std::out_of_range("Array is empty. Cannot pop");
  } else{
    --count;
    return stackArr[top--];
  }
}

template <typename T>
T MonoStack<T>::pop(int pos){ //O(1)
  if(isEmpty()){
      std::cout << "Array is empty. Cannot pop" << std::endl;
  } else{
  --count;
  return stackArr[pos];
  }
}

template <typename T>
T MonoStack<T>::peek(){ //O(1)
  return stackArr[top];
}

template <typename T>
T MonoStack<T>::peek(int pos){
    return stackArr[pos];
}

#endif
