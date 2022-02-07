/**
* @author Ethan Grantz
* @file DLinkedList.cpp
* @date 2/1/2021
* @brief defines the functions/variables that the DLinkedList class needs to work
*/
#include <stdexcept>

template <typename T>
DLinkedList<T>::DLinkedList() {
    this->_root = nullptr;
    this->_tail = nullptr;
    this->_length = 0;
}

template <typename T>
DLinkedList<T>::~DLinkedList() {
    this->clear();
}

template <typename T>
bool DLinkedList<T>::isEmpty() const {
    return this->_root == nullptr;
}

template <typename T>
unsigned int DLinkedList<T>::length() const {
    return this->_length;
}

template <typename T>
void DLinkedList<T>::insert(T val, unsigned int index) {
    if (index > this->_length || index < 0) throw(std::runtime_error("Index out of bounds."));
    if (index == 0) {
        this->_root = new DNode<T>(val,nullptr,this->_root);
        if (this->_root->getNext() == nullptr) this->_tail = this->_root;
        else this->_root->getNext()->setPrev(this->_root);
    } else if (index == this->_length) {
        this->_tail->setNext(new DNode<T>(val,this->_tail));
        this->_tail = this->_tail->getNext();
    } else {
    	DNode<T>* temp;
        if (index >= this->_length / 2) {
            temp = this->_tail;
            for (unsigned int i = this->_length - 1; i > index - 1; i--) temp = temp->getPrev();
        } else {
            temp = this->_root;
            for (unsigned int i = 0; i < index - 1; i++) temp = temp->getNext();
        }
        DNode<T>* newNode = new DNode<T>(val,temp,temp->getNext());
        temp->getNext()->setPrev(newNode);
        temp->setNext(newNode);
    }
    this->_length++;
}

template <typename T>
void DLinkedList<T>::remove(unsigned int index) {
    if (index < 0 || index > this->_length - 1) throw(std::runtime_error("Index out of bounds"));
    DNode<T>* temp = this->_root;
    if (index == 0) {
        this->_root = this->_root->getNext();
        if (this->_root != nullptr) this->_root->setPrev(nullptr);
        else this->_tail = nullptr;
    } else if (index == this->_length - 1) {
        temp = this->_tail;
        this->_tail = this->_tail->getPrev();
    } else {
        if (index >= this->_length / 2) {
            temp = this->_tail;
            for (unsigned int i = this->_length - 1; i > index; i--) temp = temp->getPrev();
        } else {
            for (unsigned int i = 0; i < index; i++) temp = temp->getNext();
        }
        temp->getPrev()->setNext(temp->getNext());
        temp->getNext()->setPrev(temp->getPrev());
    }
    delete temp;
    this->_length--;
}

template <typename T>
T DLinkedList<T>::getEntry(unsigned int index) const {
    if (index < 0 || index > this->_length - 1) throw(std::runtime_error("Index out of bounds!"));
    DNode<T>* temp;
    if (index >= this->_length / 2) {
        temp = this->_tail;
        for (unsigned int i = this->_length - 1; i > index; i--) temp = temp->getPrev();
    } else {
        temp = this->_root;
        for (unsigned int i = 0; i < index; i++) temp = temp->getNext();
    }
    return temp->getValue();
}

template <typename T>
bool DLinkedList<T>::contains(T val) const {
    DNode<T>* temp = this->_root;
    while (temp != nullptr) {
        if (temp->getValue() == val) return true;
        temp = temp->getNext();
    }
    return false;
}

template <typename T>
void DLinkedList<T>::clear() {
    while (this->_length) this->remove(0);
}
