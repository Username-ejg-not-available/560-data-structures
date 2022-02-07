#ifndef MINTHREAP_H
#define MINTHREAP_H

#include "Threap.h"

template <typename T>
class MinThreap : public Threap<T> {
private:
    void upheap(int) override;
    void downheap(int) override;
public:
    MinThreap();
    ~MinThreap();
};
#include "MinThreap.cpp"
#endif