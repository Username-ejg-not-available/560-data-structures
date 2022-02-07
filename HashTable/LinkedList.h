/**
* @author Ethan Grantz
* @file LinkedList.h
* @date 3/3/2020
* @brief declares the functions that the LinkedList class needs to work
*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
template <typename T>
class LinkedList {
private:
	Node<T>* m_front;
	unsigned int m_length;
public:
	Node<T>* getFirst() const { return m_front;}
	/**
	* @post intializes m_front to nullptr and m_length to 0
	*/
	LinkedList();

	/**
	* @post Creates deep copy of orig and assigns to calling object
	* @param orig is object being copied
	*/
	LinkedList(const LinkedList& orig);

	/**
	* @post runs clear()
	*/
	~LinkedList();

	/**
	* @pre calling object is currently allocated on heap
	* @post Creates deep copy of rhs to assign to calling object
	* @param rhs is object being copied
	*/
	void operator= (const LinkedList& rhs);

	/**
	* @pre The index is valid
	* @post The entry is added to the list at the index
	* @param index, position to insert at (0 to length)
	* @param entry, value/object to add to the list
	* @throw std::runtime_error if the index is invalid
	*/
	void insert(unsigned int index, T entry);
	
	/**
	* @pre The index is valid
	* @post The entry at given position is removed, reducing length by 1
	* @param index, position to remove (0 to length - 1)
	* @throw std::runtime_error if the index is invalid
	*/
	void remove(unsigned int index);

	/**
	* @pre The index is valid
	* @post none
	* @param index, position to get (0 to length - 1)
	* @throw std::runtime_error if the index is invalid
	*/
	T getEntry(unsigned int index);

	/**
	* @pre None
	* @post List is empty
	* @throw none
	*/
	void clear();

	/**
	* @pre The index is valid (must already exist)
	* @post Given entry overrides the entry at the given index
	* @param index, position to override at (0 to length - 1)
	* @param entry, value/object to place at given index
	* @throw std::runtime_error if the index is invalid
	*/
	void setEntry(unsigned int index, T entry);

	/**
	* @return returns m_length
	*/
	unsigned int getLength() const;
};
#include "LinkedList.cpp"
#endif