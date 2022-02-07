#ifndef MAXTHREAP_H
#define MAXTHREAP_H

#include "Threap.h"

template <typename T>
class MaxThreap : public Threap<T> {
private:
    void upheap(int) override;
    void downheap(int) override;
public:
    MaxThreap();
    ~MaxThreap();
};
#include "MaxThreap.cpp"
#endif