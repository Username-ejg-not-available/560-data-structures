#include "ExProf.h"
#include <stdlib.h>
#include <time.h>

ExProf::ExProf() {
    this->_data = new double*[5];
    for (int i = 0; i < 5; i++) {
        this->_data[i] = new double[5];
        for (int j = 0; j < 5; j++) this->_data[i][j] = 0.0;
    }
    for (int i = 0; i < 5; i++) runTests(i);
}

ExProf::~ExProf() {
    for (int i = 0; i < 5; i++) delete[] this->_data[i];
    delete[] this->_data;
}

void ExProf::runTests(unsigned int i) {
    double sample[5] = {0,0,0,0,0}; //[test][samplenum]
    for (int j = 0; j < 5; j++) {
        srand(time(NULL));
        MinMaxHeap<int>* tree = new MinMaxHeap<int>();
        sample[0] += buildTest(tree, (i + 1) * 100000);
        sample[1] += findMinTest(tree);
        sample[2] += findMaxTest(tree);
        sample[3] += deleteMinTest(tree);
        sample[4] += deleteMaxTest(tree);
        delete tree;
    }
    for (int j = 0; j < 5; j++) {
        this->_data[j][i] = sample[j] / 5;
    }
}

double ExProf::buildTest(MinMaxHeap<int>* tree, unsigned int size) {
    clock_t t;
    t = clock();
    for (unsigned int i = 0; i < size; i++) tree->add(rand() % 500000 + 1);
    return (double)(clock() - t) / CLOCKS_PER_SEC;
}

double ExProf::findMinTest(MinMaxHeap<int>* tree) {
    clock_t t;
    t = clock();
    tree->findMin();
    return (double)(clock() - t) / CLOCKS_PER_SEC;
}

double ExProf::findMaxTest(MinMaxHeap<int>* tree) {
    clock_t t;
    t = clock();
    tree->findMax();
    return (double)(clock() - t) / CLOCKS_PER_SEC;
}

double ExProf::deleteMinTest(MinMaxHeap<int>* tree) {
    clock_t t;
    t = clock();
    tree->popMin();
    return (double)(clock() - t) / CLOCKS_PER_SEC;
}

double ExProf::deleteMaxTest(MinMaxHeap<int>* tree) {
    clock_t t;
    t = clock();
    tree->popMax();
    return (double)(clock() - t) / CLOCKS_PER_SEC;
}

std::string ExProf::getPrintString() const {
    std::string res = "+---------------+----------+----------+----------+----------+----------+\n";
    res += "| Input size    |  100,000 |  200,000 |  300,000 |  400,000 |  500,000 |\n";
    std::string head[] = { "Build (s)    ", "FindMin (s)  ", "FindMax (s)  ", "DeleteMin (s)", "DeleteMax (s)" };
    for (int i = 0; i < 5; i++) {//test
        res += "+---------------+----------+----------+----------+----------+----------+\n";
        res += "| " + head[i] + " | ";
        for (int j = 0; j < 5; j++) {//size
            res += std::to_string(this->_data[i][j]) + " | ";
        }
        res += "\n";
    }
    res += "+---------------+----------+----------+----------+----------+----------+\n";
    return res;
}