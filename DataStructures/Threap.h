#ifndef THREAP_H
#define THREAP_H

#include <stdexcept>
#include <iostream>
#include <cmath>

template <typename T>
class Threap {
protected:
    T* _arr;
    int _size, _fill;
    void resize();
    virtual void upheap(int) = 0;
    virtual void downheap(int) = 0;
    void swap(int,int);
public:
    Threap();
    virtual ~Threap();
    void add(T);
    T pop();
    void clear();
    void print() const;
    T peek() const;
    bool contains(T) const;
};
template <typename T>
Threap<T>::Threap() {
    this->_arr = new T[4];
    this->_size = 4;
    this->_fill = 0;
}

template <typename T>
Threap<T>::~Threap() {
    delete[] this->_arr;
}

template <typename T>
void Threap<T>::clear() {
    delete[] this->_arr;
    this->_size = 4;
    this->_fill = 0;
    this->_arr = new T[4];
}

template <typename T>
void Threap<T>::resize() {
    if (this->_size == this->_fill) {
        T* temp = new T[this->_size * 2];
        for (int i = 0; i < this->_size; i++) {
            temp[i] = this->_arr[i];
        }
        delete[] this->_arr;
        this->_arr = temp;
        this->_size *= 2;
    } 
    else if (this->_size > (this->_fill + 1) * 3 && this->_fill) {
        T* temp = new T[this->_size / 3];
        for (int i = 0; i < this->_size / 3; i++) {
            temp[i] = this->_arr[i];
        }
        delete[] this->_arr;
        this->_arr = temp;
        this->_size /= 3;
    }
}

template <typename T>
void Threap<T>::swap(int pos1, int pos2) {
    if (pos1 > this->_fill || pos2 > this->_fill) return;
    T temp = this->_arr[pos1];
    this->_arr[pos1] = this->_arr[pos2];
    this->_arr[pos2] = temp;
}

template <typename T>
void Threap<T>::add(T val) {
    resize();
    this->_arr[this->_fill] = val;
    this->_fill++;
    this->upheap(this->_fill - 1);
}

template <typename T>
T Threap<T>::pop() {
    if (!this->_fill) throw(std::runtime_error("Tree is empty!"));
    resize();
    T temp = this->_arr[0];
    this->_arr[0] = this->_arr[this->_fill - 1];
    this->_fill--;
    downheap(0);
    return temp;
}

template <typename T>
void Threap<T>::print() const {
    int poww = 0, index = 0;
    while (index < this->_fill) {
        for (int i = 0; i < pow(3,poww); i++) {
            if (index > this->_fill - 1) break;
            std::cout << this->_arr[index];
            if (i != pow(3,poww) - 1) std::cout << " : ";
            else std::cout << "\n";
            index++;
        }
        poww++;
    }
    std::cout << "\n";
}

template <typename T>
T Threap<T>::peek() const {
    return this->_arr[0];
}

template <typename T>
bool Threap<T>::contains(T obj) const {
    for (int i = 0; i < this->_fill; i++) {
        if (this->_arr[i] == obj) return true;
    }
    return false;
}
#endif