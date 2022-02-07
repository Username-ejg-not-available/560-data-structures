/**
* @author Ethan Grantz
* @file BNode.cpp
* @date 4/24/2020
* @brief Defines the functions of BNode
*/
template <typename T>
BNode<T>::BNode(T value, BNode<T>* left, BNode<T>* right) {
    this->_value = value;
	this->_left = left;
	this->_right = right;
}

template <typename T>
BNode<T>* BNode<T>::getLeft() const {
	return _left;
}

template <typename T>
BNode<T>* BNode<T>::getRight() const {
	return _right;
}

template <typename T>
T BNode<T>::getValue() const {
	return _value;
}

template <typename T>
void BNode<T>::setLeft(BNode<T>* left) {
	this->_left = left;
}

template <typename T>
void BNode<T>::setRight(BNode<T>* right) {
	this->_right = right;
}

template <typename T>
void BNode<T>::setValue(T value) {
	this->_value = value;
}