#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>
#include <iostream>
#include <cmath>

template <typename T>
class Heap {
protected:
    T* _arr;
    int _size, _fill;
    void resize();
    virtual void upheap(int) = 0;
    virtual void downheap(int) = 0;
    void swap(int,int);
protected:
    virtual bool uniRemoveCond(T par, T cur) const = 0;
public:
    Heap();
    virtual ~Heap();
    void add(T);
    T pop();
    T remove(T);
    void clear();
    bool isEmpty() const;
    void print() const;
    T peek() const;
    bool contains(T) const;
};
template <typename T>
Heap<T>::Heap() {
    this->_arr = new T[4];
    this->_size = 4;
    this->_fill = 0;
}

template <typename T>
Heap<T>::~Heap() {
    delete[] this->_arr;
}

template <typename T>
void Heap<T>::clear() {
    delete[] this->_arr;
    this->_size = 4;
    this->_fill = 0;
    this->_arr = new T[4];
}

template <typename T>
void Heap<T>::resize() {
    if (this->_size == this->_fill) {
        T* temp = new T[this->_size * 2];
        for (int i = 0; i < this->_size; i++) {
            temp[i] = this->_arr[i];
        }
        delete[] this->_arr;
        this->_arr = temp;
        this->_size *= 2;
    } 
    else if (this->_size > (this->_fill + 1) * 2 && this->_fill) {
        T* temp = new T[this->_size / 2];
        for (int i = 0; i < this->_size / 2; i++) {
            temp[i] = this->_arr[i];
        }
        delete[] this->_arr;
        this->_arr = temp;
        this->_size /= 2;
    }
}

template <typename T>
void Heap<T>::swap(int pos1, int pos2) {
    if (pos1 > this->_fill || pos2 > this->_fill) return;
    T temp = this->_arr[pos1];
    this->_arr[pos1] = this->_arr[pos2];
    this->_arr[pos2] = temp;
}

template <typename T>
void Heap<T>::add(T val) {
    resize();
    this->_arr[this->_fill] = val;
    this->_fill++;
    this->upheap(this->_fill - 1);
}

template <typename T>
T Heap<T>::pop() {
    if (!this->_fill) throw(std::runtime_error("Tree is empty!"));
    resize();
    T temp = this->_arr[0];
    this->_arr[0] = this->_arr[this->_fill - 1];
    this->_fill--;
    downheap(0);
    return temp;
}

template <typename T>
void Heap<T>::print() const {
    int poww = 0, index = 0;
    while (index < this->_fill) {
        for (int i = 0; i < pow(2,poww); i++) {
            if (index > this->_fill - 1) break;
            std::cout << this->_arr[index];
            if (i != pow(2,poww) - 1) std::cout << " : ";
            else std::cout << "\n";
            index++;
        }
        poww++;
    }
    std::cout << "\n";
}

template <typename T>
T Heap<T>::peek() const {
    return this->_arr[0];
}

template <typename T>
bool Heap<T>::contains(T obj) const {
    for (int i = 0; i < this->_fill; i++) {
        if (this->_arr[i] == obj) return true;
    }
    return false;
}

template <typename T>
bool Heap<T>::isEmpty() const {
    return this->_fill == 0;
}

template <typename T>
T Heap<T>::remove(T obj) {
    if (!contains(obj)) throw(std::runtime_error("Item no in tree!"));
    int i = 0;
    for (; i < this->_fill; i++) {
        if (this->_arr[i] == obj) break;
    }
    std::cout << i << "\n";
    T temp = this->_arr[i];
    this->_arr[i] = this->_arr[this->_fill - 1];
    this->_fill--;

    if (i && uniRemoveCond(this->_arr[(i-1)/2],this->_arr[i])) upheap(i);
    else downheap(i);
    return temp;
}
#endif