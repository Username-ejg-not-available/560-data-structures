#include <iostream>

template <typename T>
DisjointSet<T>::DisjointSet() {
    this->_arr = new Node<T>*[1000];
    this->_rankArr = new int[1000];
    this->_fill = 0;
}

template <typename T>
DisjointSet<T>::~DisjointSet() {
    clear();
    delete[] this->_arr;
    delete[] this->_rankArr;
}

template <typename T>
void DisjointSet<T>::add(T val) {
    this->_arr[this->_fill] = new Node<T>(val);
    this->_arr[this->_fill]->setNext(this->_arr[this->_fill]);
    this->_rankArr[this->_fill] = 0;
    this->_fill++;
}

template <typename T>
T DisjointSet<T>::unionByRank(T val1, T val2) {
    int index1 = getRootIndex(val1), index2 = getRootIndex(val2);
    if (index1 == -1) throw(std::runtime_error("> Output: Sorry! " + std::to_string(val1) + " is not found!"));
    if (index2 == -1) throw(std::runtime_error("> Output: Sorry! " + std::to_string(val2) + " is not found!"));
    if (index1 == index2) return this->_arr[index1]->getEntry();
    if (this->_rankArr[index1] == this->_rankArr[index2]) {
        if (this->_arr[index1]->getEntry() > this->_arr[index2]->getEntry()) {
            this->_rankArr[index1]++;
            this->_arr[index2]->setNext(this->_arr[index1]);
            return this->_arr[index1]->getEntry();
        } else {
            this->_rankArr[index2]++;
            this->_arr[index1]->setNext(this->_arr[index2]);
            return this->_arr[index2]->getEntry();
        }
    }
    else {
        if (this->_rankArr[index1] > this->_rankArr[index2]) {
            this->_arr[index2]->setNext(this->_arr[index1]);
            return this->_arr[index1]->getEntry();
        }
        else {
            this->_arr[index1]->setNext(this->_arr[index2]);
            return this->_arr[index2]->getEntry();
        }
    }
}

template <typename T>
T DisjointSet<T>::find(T val) {
    int index = getIndex(val);
    if (index == -1) throw(std::runtime_error("> Output: Sorry! " + std::to_string(val) + " is not found!"));
    Node<T>* curr = this->_arr[index], *prev = nullptr;
    do {
        prev = curr;
        curr = curr->getNext();
    } while (curr != prev);
    compress(val);
    return curr->getEntry();
}

template <typename T>
void DisjointSet<T>::compress(T val) {
    int index = getIndex(val);
    if (index == -1) throw(std::runtime_error(">Output: Sorry! " + std::to_string(val) + " is not found!"));
    Node<T>* curr = this->_arr[index], *next = this->_arr[index]->getNext(), *root = this->_arr[getRootIndex(val)];
    while (curr != curr->getNext()) {
        next = curr->getNext();
        curr->setNext(root);
        curr = next;
    }
}

template <typename T>
bool DisjointSet<T>::contains(T val) const {
    for (int i = 0; i < this->_fill; i++) {
        if (this->_arr[i]->getEntry() == val) return true;
    }
    return false;
}

template <typename T>
void DisjointSet<T>::clear() {
    for (int i = 0; i < this->_fill; i++) {
        delete this->_arr[i];
    }
    this->_fill = 0;
}

template <typename T>
int DisjointSet<T>::getIndex(T val) const {
    for (int i = 0; i < this->_fill; i++) {
        if (this->_arr[i]->getEntry() == val) return i;
    }
    return -1;
}

template <typename T>
int DisjointSet<T>::getRootIndex(T val) const {
    int index = getIndex(val);
    if (index == -1) return -1;
    Node<T>* curr = this->_arr[index];
    while (curr != curr->getNext() && index != -1) {
        curr = curr->getNext();
        index = getIndex(curr->getEntry());
    }
    return index;
}

template <typename T>
void DisjointSet<T>::printPath(T val) const {
    int index = getIndex(val);
    if (index == -1) {
        std::cout << "> Output: Sorry! " << val << " is not found!\n";
        return;
    }
    Node<T>* curr = this->_arr[index], *prev;
    std::cout << "> Output: The path for the element " << val << " is: ";
    bool printArrow = false;
    do {
        if (printArrow) std::cout << "->";
        printArrow = true;
        std::cout << curr->getEntry();
        prev = curr;
        curr = curr->getNext();
    } while (prev != curr);
    std::cout << "\n";
}

//make set: makes an array of nodes
//union by weight: Set with highest number of nodes is new root (root is the furthest parent)
//      if num of nodes are the same, higher root is the same
//Union by height: greatest height becomes root
//Union by rank: Similar to union by height, but rank does not change with path compression
    //If two sets have same rank, rank is 1 higher. If diff rank, rank is the higher of the two
//Find: return root that is representative of of that number, need to apply path compression at end
//Path Compression: All ancestors of a specified node become direct children of root
