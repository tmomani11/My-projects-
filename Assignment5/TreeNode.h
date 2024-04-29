#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T>
class TreeNode{
public:
  TreeNode(T d);
  virtual ~TreeNode();
  T getData();
  T m_data;
  template <typename S>
  friend class BST;

private:
  TreeNode<T>* m_left;
  TreeNode<T>* m_right;
};

template <typename T>
TreeNode<T>::TreeNode(T d){
  m_data = d;
  m_left = nullptr;
  m_right = nullptr;
}

template <typename T>
TreeNode<T>::~TreeNode(){
  if(m_left != nullptr){
    delete m_left;
  }
  if(m_right != nullptr){
    delete m_right;
  }
}

template <typename T>
T TreeNode<T>::getData(){
  return m_data;
}

#endif