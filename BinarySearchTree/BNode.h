/**
* @author Ethan Grantz
* @file BNode.h
* @date 4/24/2020
* @brief Declares the functions and variables of BNode
*/
#ifndef BNode_H
#define BNode_H
template <typename T>
class BNode {
private:
	BNode<T>* _left,* _right;
	T _value;
public:
	/**
	* @pre input is valid
	* @param value to be assigned to _value
	* @param left to be assigned to _left
	* @param right to be assigned to _right
	* @post assigns nullptr to left and right and T to _value
	*/
	BNode(T value, BNode<T>* left = nullptr, BNode<T>* right = nullptr);

	/**
	* @return returns _left
	*/
	BNode<T>* getLeft() const;

	/**
	* @return returns _right
	*/
	BNode<T>* getRight() const;

	/**
	* @return returns _value
	*/
	T getValue() const;

	/**
	* @pre input is valid
	* @param left to be assigned to left
	* @post assigns parameter to left
	*/
	void setLeft(BNode<T>* left);
	
	/**
	* @pre input is valid
	* @param right to be assigned to right
	* @post assigns parameter to right
	*/
	void setRight(BNode<T>* right);

	/**
	* @pre input is valid
	* @param value to be assigned to _value
	* @post assigns parameter to _value
	*/
	void setValue(T value);
};
#include "BNode.cpp"
#endif