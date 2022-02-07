/**
*@author Ethan Grantz
*@file Node.cpp
*@date 2/1/2021
*@brief defines the functions that a doubly linked node needs
*/

template <typename T>
DNode<T>::DNode(T val, DNode<T>* prev, DNode<T>* next) {
    this->_value = val;
    this->_prev = prev;
    this->_next = next;
}

template <typename T>
T DNode<T>::getValue() const {
    return this->_value;
}

template <typename T>
DNode<T>* DNode<T>::getPrev() const {
    return this->_prev;
}

template <typename T>
DNode<T>* DNode<T>::getNext() const {
    return this->_next;
}

template <typename T>
void DNode<T>::setValue(T val) {
    this->_value = val;
}

template <typename T>
void DNode<T>::setPrev(DNode<T>* prev) {
    this->_prev = prev;
}

template <typename T>
void DNode<T>::setNext(DNode<T>* next) {
    this->_next = next;
}