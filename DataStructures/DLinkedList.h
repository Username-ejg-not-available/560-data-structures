/**
* @author Ethan Grantz
* @file DLinkedList.h
* @date 2/1/2021
* @brief declares the functions/variables that the DLinkedList class needs to work
*/
#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "DNode.h"

template <typename T>
class DLinkedList {
private:
    DNode<T>* _root, * _tail;
    unsigned int _length;
public:
    /**
	* @post intializes _root and _tail to nullptr and _length to 0
	*/
    DLinkedList();

    /**
     * @post calls clear()
     */
    ~DLinkedList();

    /**
     * @return returns if _length == 0
     */
    bool isEmpty() const;

    /**
	* @return returns _length
	*/
    unsigned int length() const;

    /**
	* @pre The index is valid
	* @post The entry is added to the list at the index
	* @param val, value/object to add to the list
	* @param index, position to insert at (1 to length + 1) (indexed this way because Dr. Gibbons told his 268 class that singly linked lists index this way for some reason)
	* @throw std::runtime_error if the index is invalid
	*/
    void insert(T val, unsigned int index);

    /**
	* @pre The index is valid
	* @post The entry at given position is removed, reducing length by 1
	* @param index, position to remove (1 to length)
	* @throw std::runtime_error if the index is invalid
	*/
    void remove(unsigned int index);

    /**
	* @pre The index is valid
	* @param index, position to get (1 to length)
	* @throw std::runtime_error if the index is invalid
	*/
    T getEntry(unsigned int) const;

    bool contains(T) const;

    /**
     * @post runs remove() until _length == 0
     */
    void clear();
};
#include "DLinkedList.cpp"
#endif