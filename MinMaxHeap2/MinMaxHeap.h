#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H


template <typename T>
class MinMaxHeap {
private:
    T* _arr;
    int _size, _fill;

    void upheap(int);
    void downheap(int);
    void resize();
    void swap(int, int);
    int getLevel(unsigned int) const;
public:
    MinMaxHeap();
    ~MinMaxHeap();
    void add(T);
    T popMin();
    T popMax();
    T findMin();
    T findMax();
    void clear();
    void print(int) const;
    bool verify(int) const;
};
#include "MinMaxHeap.cpp"
#endif