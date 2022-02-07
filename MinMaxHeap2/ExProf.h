#ifndef EXPROF_H
#define EXPROF_H

#include "MinMaxHeap.h"

class ExProf {
private:
    double** _data;
public:
    ExProf();
    ~ExProf();
    void runTests(unsigned int i);
    double buildTest(MinMaxHeap<int>* tree, unsigned int size);
    double findMinTest(MinMaxHeap<int>* tree);
    double findMaxTest(MinMaxHeap<int>* tree);
    double deleteMinTest(MinMaxHeap<int>* tree);
    double deleteMaxTest(MinMaxHeap<int>* tree);
    std::string getPrintString() const;
};
#endif