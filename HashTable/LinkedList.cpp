/**
* @author Ethan Grantz
* @file LinkedList.cpp
* @date 3/3/2020
* @brief defines the functions that the LinkedList class needs to work
*/
#include <stdexcept>

template <typename T>
LinkedList<T>::LinkedList() {
	m_length = 0;
	m_front = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& orig) {
	m_length = orig.m_length;
	if (!m_length) {
		m_front = nullptr;
		return;
	}
	m_front = new Node<T>(orig.m_front->getEntry());
	Node<T>* temp = m_front;
	Node<T>* temp2 = orig.m_front;
	for (int i = 1; i < m_length; i++) {
		temp2 = temp2->getNext();
		temp->setNext(new Node<T>(temp2->getEntry()));
		temp = temp->getNext();
	}
}

template <typename T>
LinkedList<T>::~LinkedList() {
	clear();
}

template <typename T>
void LinkedList<T>::operator= (const LinkedList& rhs) {
	clear();
	m_length = rhs.m_length;
	if (!m_length) {
		m_front = nullptr;
		return;
	}
	m_front = new Node<T>(rhs.m_front->getEntry());
	Node<T>* temp = m_front;
	Node<T>* temp2 = rhs.m_front;
	for (int i = 1; i < m_length; i++) {
		temp2 = temp2->getNext();
		temp->setNext(new Node<T>(temp2->getEntry()));
		temp = temp->getNext();
	}
}

template <typename T>
void LinkedList<T>::insert(unsigned int index, T entry) {
	if (index < 0 || index > m_length) throw(std::runtime_error("Invalid Index"));
	Node<T>* temp = new Node<T>(entry);
	if (index == 0) {
		temp->setNext(m_front);
		m_front = temp;
	} else if (index == m_length) {
		Node<T>* temp2 = m_front;
		for (unsigned int i = 0; i < m_length - 1; i++) temp2 = temp2->getNext();
		temp2->setNext(temp);
	} else {
		Node<T>* temp2 = m_front;
		for (unsigned int i = 0; i < index - 1; i++) temp2 = temp2->getNext();
		temp->setNext(temp2->getNext());
		temp2->setNext(temp);
	}
	m_length++;
}

template <typename T>
void LinkedList<T>::remove(unsigned int index) {
	if (index < 0 || index > m_length - 1) throw(std::runtime_error("Invalid Index"));
	Node<T>* temp = m_front;
	if (index == 0) {
		m_front = m_front->getNext();
		delete temp;
	} else {
		for (unsigned int i = 0; i < index - 1; i++) temp = temp->getNext();
		Node<T>* temp2 = temp->getNext();
		temp->setNext(temp2->getNext());
		delete temp2;
	}
	m_length--;
}

template <typename T>
T LinkedList<T>::getEntry(unsigned int index) {
	if (index < 0 || index > m_length - 1) throw(std::runtime_error("Invalid Index.\n"));
	Node<T>* temp = m_front;
	for (unsigned int i = 0; i < index; i++) temp = temp->getNext();
	return temp->getEntry();
}

template <typename T>
void LinkedList<T>::clear() {
	while (m_length) remove(0);
}

template <typename T>
void LinkedList<T>::setEntry(unsigned int index, T entry) {
	if (index < 0 || index > m_length - 1) throw(std::runtime_error("Invalid Index.\n"));
	Node<T>* temp = m_front;
	for (unsigned int i = 0; i < index; i++) temp = temp->getNext();
	temp->setEntry(entry);
}

template <typename T>
unsigned int LinkedList<T>::getLength() const {
	return m_length;
}