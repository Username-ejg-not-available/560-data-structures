/**
* @author Ethan Grantz
* @file BNode.cpp
* @date 4/24/2020
* @brief Defines the functions of BNode
*/
template <typename T>
BNode<T>::BNode(T value, BNode<T>* left, BNode<T>* right, int rank) {
    this->_value = value;
	this->_left = left;
	this->_right = right;
	this->_rank = rank;
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

template <typename T>
int BNode<T>::getRank() const {
	return this->_rank;
}

template <typename T>
void BNode<T>::updateRank() {
	updateRank(this);
}

template <typename T>
int BNode<T>::updateRank(BNode<T>* node) const {
	int left = -1, right = -1;
	if (node->getLeft() != nullptr) left = 1 + updateRank(node->getLeft());
	if (node->getRight() != nullptr) right = 1 + updateRank(node->getRight());
	if (left == -1 || right == -1) {
		node->_rank = 1;
		return node->_rank;
	}
	node->_rank = (left > right) ? right : left;
	return node->_rank;
}