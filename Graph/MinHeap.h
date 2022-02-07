#ifndef MINHEAP_H
#define MINHEAP_H

#include "Heap.h"

template <typename T>
class MinHeap : public Heap<T> {
private:
    void upheap(int) override;
    void downheap(int) override;
    bool uniRemoveCond(T,T) const override;
public:
    MinHeap();
    ~MinHeap();
};
#include "MinHeap.cpp"
#endif