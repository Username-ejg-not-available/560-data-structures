/**
* @author Ethan Grantz
* @file Node.h
* @date 3/3/2020
* @brief declaers the functions that the Node class needs to work
*/
#ifndef NODE_H
#define NODE_H
template <typename T>
class Node {
private:
	T m_entry;
	Node<T>* m_next;
public:
	/**
	* @pre input is valid
	* @param value to be assigned to m_entry
	* @post assigns nullptr to m_next and entry to m_entry
	*/
	Node(T);

	/**
	* @pre input is valid
	* @param value to be assigned to m_entry
	* @post assigns entry to m_entry
	*/
	void setEntry(T);

	/**
	* @return returns m_entry
	*/
	T getEntry() const;

	/**
	* @pre input is valid
	* @param value to be assigned to m_next
	* @post assigns next ot m_next
	*/
	void setNext(Node<T>*);

	/**
	* @return returns m_next
	*/
	Node<T>* getNext() const;
};
#include "Node.cpp"
#endif