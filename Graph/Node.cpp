/**
* @author Ethan Grantz
* @file Node.cpp
* @date 3/3/2020
* @brief defines the functions that the Node class needs to work
*/
template <typename T>
Node<T>::Node(T entry) {
	m_entry = entry;
	m_next = nullptr;
}

template <typename T>
void Node<T>::setEntry(T entry) {
	m_entry = entry;
}

template <typename T>
T Node<T>::getEntry() const {
	return m_entry;
}

template <typename T>
void Node<T>::setNext(Node<T>* next) {
	m_next = next;
}

template <typename T>
Node<T>* Node<T>::getNext() const {
	return m_next;
}