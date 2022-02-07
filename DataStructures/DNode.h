/**
*@author Ethan Grantz
*@file Node.h
*@date 2/1/2021
*@brief declares the functions/variables that a doubly linked node needs
*/
#ifndef DNODE_H
#define DNODE_H

template<typename T>
class DNode {
private:
    T _value;
    DNode<T>* _prev, * _next;
public:
    /**
	* @pre input is valid
	* @param val to be assigned to _value
    * @param prev previous node (defaults to nullptr)
    * @param next next node (defaults to nullptr)
	* @post assigns val to _value, prev to _prev, and next to _next
	*/
    DNode(T val, DNode<T>* prev = nullptr, DNode<T>* next = nullptr);
    
    /**
	* @return returns _value
	*/
    T getValue() const;

    /**
	* @return returns _prev
	*/
    DNode<T>* getPrev() const;

    /**
	* @return returns _next
	*/
    DNode<T>* getNext() const;

    /**
	* @pre input is valid
	* @param val to be assigned to _value
	* @post assigns val to _value
	*/
    void setValue(T val);

    /**
	* @pre input is valid
	* @param next to be assigned to _next
	* @post assigns next to _next
	*/
    void setNext(DNode<T>* next);

    /**
	* @pre input is valid
	* @param prev to be assigned to _prev
	* @post assigns next to _prev
	*/
    void setPrev(DNode<T>* prev);
};
#include "DNode.cpp"
#endif
