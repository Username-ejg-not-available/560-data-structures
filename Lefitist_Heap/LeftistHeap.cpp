#include <stdexcept>
#include <iostream>

template <typename T>
LeftistHeap<T>::LeftistHeap() {
    this->_root = nullptr;
}

template <typename T>
LeftistHeap<T>::~LeftistHeap() {
    this->clear(this->_root);
}

template <typename T>
void LeftistHeap<T>::concat(const LeftistHeap& otherheap) {
    this->_root = concat(this->_root, deepcopy(otherheap._root));
}

template <typename T>
BNode<T>* LeftistHeap<T>::concat(BNode<T>* h1, BNode<T>* h2) {
    if (h1 == nullptr) return h2;
    if (h2 == nullptr) return h1;
    if (h1->getValue() > h2->getValue()) {
        BNode<T>* temp = h1;
        h1 = h2;
        h2 = temp;
    }
    h1->setRight(concat(h2, h1->getRight()));
    h1->updateRank();
    int leftrank, rightrank;
    leftrank = (h1->getLeft() == nullptr) ? 0 : h1->getLeft()->getRank();
    rightrank = (h1->getRight() == nullptr) ? 0 : h1->getRight()->getRank();
    if (leftrank < rightrank) {
        BNode<T>* temp = h1->getLeft();
        h1->setLeft(h1->getRight());
        h1->setRight(temp);
    }
    return h1;
}

template <typename T>
void LeftistHeap<T>::add(T val) {
    this->_root = concat(this->_root, new BNode<T>(val));
}

template <typename T>
T LeftistHeap<T>::deleteMin() {
    if (this->_root == nullptr) throw(std::runtime_error("Heap is empty!"));
    BNode<T>* left = this->_root->getLeft();
    BNode<T>* right = this->_root->getRight();
    T temp = this->_root->getValue();
    delete this->_root;
    this->_root = concat(left, right);
    return temp;
}

template <typename T>
T LeftistHeap<T>::findMin() const {
    if (this->_root == nullptr) throw(std::runtime_error("Heap is empty!"));
    return this->_root->getValue();
}

template <typename T>
void LeftistHeap<T>::inOrder() const {
    inOrder(this->_root);
    std::cout << "\n";
}

template <typename T>
void LeftistHeap<T>::inOrder(BNode<T>* node) const {
    if (node == nullptr) return;
    inOrder(node->getLeft());
    std::cout << node->getValue() << ", ";
    inOrder(node->getRight());
}

template <typename T>
void LeftistHeap<T>::levelOrder() const {
    for (unsigned int i = 0; i < height(this->_root); i++) {
        levelOrder(this->_root, i);
    }
    std::cout << "\n";
}

template <typename T>
void LeftistHeap<T>::levelOrder(BNode<T>* node, unsigned int i) const {
    if (node == nullptr) return;
    if (i == 0) std::cout << node->getValue() << ", ";
    else {
        levelOrder(node->getLeft(), i - 1);
        levelOrder(node->getRight(), i - 1);
    }
}

template <typename T>
void LeftistHeap<T>::clear() {
    clear(this->_root);
    this->_root = nullptr;
}

template <typename T>
void LeftistHeap<T>::clear(BNode<T>* node) {
    if (node == nullptr) return;
    if (node->getLeft() != nullptr) clear(node->getLeft());
    if (node->getRight() != nullptr) clear(node->getRight());
    delete node;
}

template <typename T>
unsigned int LeftistHeap<T>::height() const {
    return this->height(this->_root);
}

template <typename T>
unsigned int LeftistHeap<T>::height(BNode<T>* node) const {
    if (node == nullptr) return 0; 
    else { 
        int leftheight = height(node->getLeft()); 
        int rightheight = height(node->getRight()); 
        if (leftheight > rightheight) return leftheight + 1; 
        else return rightheight + 1; 
    }
}

template <typename T>
BNode<T>* LeftistHeap<T>::deepcopy(BNode<T>* node) const {
    if (node == nullptr) return nullptr;
    return new BNode<T>(node->getValue(), deepcopy(node->getLeft()), deepcopy(node->getRight()), node->getRank());
}

template <typename T>
bool LeftistHeap<T>::contains(T val) const {
    bool res = false;
    contains(val, this->_root, res);
    return res;
}

template <typename T>
void LeftistHeap<T>::contains(T val, BNode<T>* node, bool& out) const {
    if (node == nullptr) return;
    if (node->getValue() == val) {
        out = true;
        return;
    }
    contains(val, node->getLeft(), out);
    contains(val, node->getRight(), out);
}