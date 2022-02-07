#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include "Node.h"

template <typename T>
class DisjointSet {
private:
    Node<T>** _arr;
    int* _rankArr;
    int _fill;

    int getIndex(T) const;
    int getRootIndex(T) const;
public:
    DisjointSet();
    ~DisjointSet();
    void add(T);
    T unionByRank(T, T);
    T find(T);
    void compress(T);
    bool contains(T) const;
    void clear();
    void printPath(T) const;
};
#include "DisjointSet.cpp"
#endif