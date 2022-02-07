#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#include "BNode.h"

template <typename T>
class LeftistHeap {
private:
    BNode<T>* _root;

    void levelOrder(BNode<T>* node, unsigned int i) const;
    void inOrder(BNode<T>* node) const;
    void clear(BNode<T>*);
    unsigned int height(BNode<T>* node) const;
    void contains(T, BNode<T>*, bool&) const;
    BNode<T>* deepcopy(BNode<T>*) const;
public:
    LeftistHeap();
    ~LeftistHeap();
    void concat(const LeftistHeap&);
    BNode<T>* concat(BNode<T>* h1, BNode<T>* h2);
    void add(T);
    T deleteMin();
    T findMin() const;
    void inOrder() const;
    void levelOrder() const;
    void clear();
    unsigned int height() const;
    bool contains(T) const;
};
#include "LeftistHeap.cpp"
#endif