#ifndef BST_H
#define BST_H

#include "BNode.h"

template <typename T>
class BST {
private:
    BNode<T>* _root;
    unsigned int _size;
    unsigned int height(BNode<T>* node) const;
    void add(T value, BNode<T>* node);
    BNode<T>* remove(T value, BNode<T>* node);
    void clear(BNode<T>* node);
    void copier(BNode<T>* node);
    void inorderSuccessor(BNode<T>* node, T* inorder, unsigned int& index) const;
    void levelOrder(BNode<T>* node, unsigned int i) const;
    void spiralOrder(BNode<T>* node, unsigned int i, bool forward) const;
    void printLeft(BNode<T>* node, unsigned int i, unsigned int& last) const;
    void printRight(BNode<T>* node, unsigned int i, unsigned int& last) const;
public:
    BST();
    BST(const BST& other);
    ~BST();
    void operator= (const BST& other);
    unsigned int size() const;
    unsigned int height() const;
    void add(T);
    void remove(T);//maybe use K instead?
    void clear();
    bool isEmpty() const;
    T findMax() const;
    T findMin() const;
    void removeMax();
    void removeMin();
    T inorderSuccessor(T value) const;
    void printLeft() const;
    void printRight() const;
    void levelOrder() const;
    void spiralOrder() const;

    void print() const;
    void print(BNode<T>*) const;
};

#include "BST.cpp"
#endif