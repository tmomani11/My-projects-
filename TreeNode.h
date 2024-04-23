#ifndef BST_TREENODE_H
#define BST_TREENODE_H
#include <iostream>
using namespace std;
template <class T>
class TreeNode{
    TreeNode();
    TreeNode(T key);
    virtual ~TreeNode();

    T key;
    TreeNode<T> *left;
    TreeNode<T> *right;

};
template <class T>
TreeNode<T>::TreeNode() {
        key = 0;
        left = nullptr;
        right = nullptr;
}
template <class T>
TreeNode<T>::TreeNode(T key) {
    this->key = key;
    left = nullptr;
    right = nullptr;
}
template <class T>
TreeNode<T>::~TreeNode() {
    cout << "Deleting node with key: " << key << endl;
    left = nullptr;
    right = nullptr;
}
template <class T>
class BST{
    BST();
    virtual ~BST();

    void insert(T key);
    bool contains(T key);
    bool deleteNode(T key);
    bool isEmpty();
    void printTree();
    T* getMin();
    T* getMax();
    TreeNode<T>* getSuccessor(TreeNode<T> *d); // d represents the node to be deleted

    void recPrint(TreeNode<T> node);

private:
    TreeNode<T> *root;


};
template <class T>
BST<T>::BST() {
    root = nullptr;
}
template <class T>
BST<T>::~BST() {
    // iterate and delete

}
template <class T>
void BST<T>::recPrint(TreeNode<T> node) {
    if(node == nullptr)
        return;
    cout << node->key << endl;
    recPrint(node->left);
    recPrint(node->right);
}
template <class T>
void BST<T>::printTree() {
    recPrint(root);
}
template <class T>
bool BST<T>::isEmpty() {
    return root == nullptr;
}
template <class T>
T* BST<T>::getMin() {
    if(isEmpty()) return nullptr;
    TreeNode<T> *curr = root;
    while(curr->left != nullptr) {
        curr = curr->left;
    }
    return &curr->key;
}
template <class T>
T* BST<T>::getMax() {
    if(isEmpty()) return nullptr;
    TreeNode<T> *curr = root;
    while(curr->right != nullptr) {
        curr = curr->right;
    }
    return &curr->key;
}
template <class T>
void BST<T>::insert(T key) {
    TreeNode<T> *node = new TreeNode<T>(key);
    if(isEmpty()) {
        root = node;
    } else {
        TreeNode<T> *curr = root;
        TreeNode<T> *parent = nullptr;
        while (true) {
            parent = curr;
            if (key < curr->key) {
                curr = curr->left;
                if (curr == nullptr) {
                    parent->left = node;
                    break;
                }
            } else {
                curr = curr->right;
                if (curr == nullptr) {
                    parent->right = node;
                    break;
                }
            }
        }
    }
}
template <class T>
bool BST<T>::contains(T key) {
    if(isEmpty()) return false;
    TreeNode<T> *curr = root;
    while(curr->key != key) {
        if(key < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
        if(curr == nullptr) return false;
    }
    return true;
}
template <class T>
bool BST<T>::deleteNode(T key) {
if(isEmpty())
    return false;
TreeNode<T> *curr = root;
TreeNode<T> *parent = root;
bool isLeft = true;
while(curr->key != key){
    parent == curr;
    if(key < curr->key){
        isLeft = true;
        curr = curr->left;
    } else {
        isLeft = false;
        curr = curr->right;
    }
    if(curr == nullptr)
        return false;
}
// if we make it here, we found the node to be deleted
// case: node to be deleted has no children
if(curr->left == NULL && curr->right == NULL){
    if(curr == root){
        root = nullptr;
    } else if(isLeft){
        parent->left = nullptr;
    } else {
        parent->right = nullptr;
    }
}
// case: node to be deleted has 1 child
else if(curr->right == NULL){
    // node to be deleted has a left child
    if(curr == root){
        root = curr->left;
    } else if(isLeft){
        parent->left = curr->left;
    } else {
        parent->right = curr->left;
    }

}
    else if(curr->left == NULL) {
        // node to be deleted has a right child
        if (curr == root) {
            root = curr->right;
        } else if (isLeft) {
            parent->left = curr->right;
        } else {
            parent->right = curr->right;
        }
    }
    else{
        //the node to be deleted has 2 children
        TreeNode<T> *successor = getSuccessor(curr);
        if(curr == root){
            root = successor;
        } else if(isLeft){
            parent->left = successor;
        } else {
            parent->right = successor;
        }
        successor->left = curr->left;
        curr->right = nullptr;
        curr->left = nullptr;
    }
    delete curr;
    return true;
}
template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d) {
    //d represents the node to be deleted, we are finding the smallest in the right subtree of d
    TreeNode<T> *sp = d;
    TreeNode<T> *successor = d;
    TreeNode<T> *current = d->right;
    while(current != nullptr){
        sp = successor;
        successor = current;
        current = current->left;
    }
    if (successor != d->right) {
        sp->left = successor->right;
        successor->right = d->right;
    }
    return successor;
}










#endif //BST_TREENODE_H