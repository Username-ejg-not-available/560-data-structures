#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H


template <typename T>
class MinMaxHeap {
private:
    T* _arr;
    int _size, _fill;

    /*
     * I finished the lab before Monday and Tuesday, before the change was made.
     * I couldn't be bothered to redo the entire lab because I decided to do mine early like a responsible student
     * Therefore if the design is poor that is because the original assignment was very difficult and I had to get
     * creative.
     */

    /*
     * Only way I could think to do a general removal concisely is to treat this structure as a minheap.
     * For instance, minmaxheap:      ->    Converted to minheap (or min rhombus):
     *      2                                               2
     *    25 23                                        13  9 7 11
     * 13  9 7 11                                     24 8 12
     *24 8 12                                             25 23
     * In this way, I can use a simple minheap removal algorithm for both add() and remove(), 
     * but jury-rigged with a hideous traversal method to move about the tree as if it was a minheap, 
     * despite not actually satisfying heap conditions.
     * If on a maxlevel, upheap moves down, downheap moves up.
     * If on a minlevel, upheap moves up, downheap moves down.
     * 
     * Functions should have the same big O complexity, they just look really ugly.
     */
    void heapify(int);
    void upheap(int);
    void downheap(int);
    void resize();
    void swap(int, int);
    int getLevel(unsigned int) const;
    void remove(T);
public:
    MinMaxHeap();
    ~MinMaxHeap();
    void add(T);
    T pop();
    void clear();
    void print(int) const;
    bool verify(int) const;
};
#include "MinMaxHeap.cpp"
#endif