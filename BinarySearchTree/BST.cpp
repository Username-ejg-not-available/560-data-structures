#include <iostream>

template <typename T>
BST<T>::BST() {
    this->_root = nullptr;
    this->_size = 0;
}

template <typename T>
BST<T>::BST(const BST& other) {
    copier(other._root);
}

template <typename T>
BST<T>::~BST() {
    this->clear(this->_root);
}

template <typename T>
void BST<T>::operator= (const BST& other) {
    this->clear();
    copier(other._root);
}

template <typename T>
void BST<T>::copier(BNode<T>* node) {
    if (node == nullptr) return;
    this->add(node->getValue());
    copier(node->getLeft());
    copier(node->getRight());
}

template <typename T>
unsigned int BST<T>::size() const {
    return _size;
}

template <typename T>
unsigned int BST<T>::height() const {
    return height(this->_root);
}

template <typename T>
unsigned int BST<T>::height(BNode<T>* node) const {
    if (node == nullptr) return 0; 
    else { 
        int leftheight = height(node->getLeft()); 
        int rightheight = height(node->getRight()); 
        if (leftheight > rightheight) return leftheight + 1; 
        else return rightheight + 1; 
    }
}

template <typename T>
void BST<T>::add(T value) {
    if (this->isEmpty()) this->_root = new BNode<T>(value);
    else this->add(value, this->_root);
    this->_size++;
}

template <typename T>
void BST<T>::add(T value, BNode<T>* node) {
    if (value < node->getValue()) {
        if (node->getLeft() == nullptr) node->setLeft(new BNode<T>(value));
        else add(value, node->getLeft());
    }
    else {
        if (node->getRight() == nullptr) node->setRight(new BNode<T>(value));
        else add(value, node->getRight());
    }
}

template <typename T>
void BST<T>::remove(T value) {
    this->_root = this->remove(value, this->_root);
    this->_size--;
}

template <typename T>
BNode<T>* BST<T>::remove(T value, BNode<T>* node) {
    if (node == nullptr) throw(std::runtime_error("Element not in tree!"));
    if (node->getValue() < value) node->setRight(remove(value,node->getRight()));
    else if (node->getValue() > value) node->setLeft(remove(value,node->getLeft()));
    else {
        if (node->getLeft() == nullptr) {
            BNode<T>* temp = node->getRight();
            delete node;
            return temp;
        } 
        else if (node->getRight() == nullptr) {
            BNode<T>* temp = node->getLeft();
            delete node;
            return temp;
        }
        BNode<T>* temp = node->getRight(), * tempPar = node;
        while (temp->getLeft() != nullptr) {
            tempPar = temp;
            temp = temp->getLeft();
        }
        node->setValue(temp->getValue());
        if (tempPar == node) tempPar->setRight(temp->getRight());
        else tempPar->setLeft(temp->getRight());
        delete temp;
    }
    return node;
}

template <typename T>
void BST<T>::clear() {
    this->clear(this->_root);
    this->_root = nullptr;
}

template <typename T>
void BST<T>::clear(BNode<T>* node) {
    if (node == nullptr) return;
    this->clear(node->getLeft());
    this->clear(node->getRight());
    delete node;
}

template <typename T>
bool BST<T>::isEmpty() const {
    return this->_root == nullptr;
}

template <typename T>
void BST<T>::print() const {
    print(_root);
}

template <typename T>
void BST<T>::print(BNode<T>* x) const {
    if (x == nullptr) return;
    std::cout << x->getValue() << "\n";
    print(x->getLeft());
    print(x->getRight());
}

template <typename T>
T BST<T>::findMax() const {
    if (this->isEmpty()) throw(std::runtime_error("Tree is Empty!"));
    BNode<T>* temp = this->_root;
    while (temp->getRight() != nullptr) temp = temp->getRight();
    return temp->getValue();
}

template <typename T>
T BST<T>::findMin() const {
    if (this->isEmpty()) throw(std::runtime_error("Tree is Empty!"));
    BNode<T>* temp = this->_root;
    while (temp->getLeft() != nullptr) temp = temp->getLeft();
    return temp->getValue();
}

template <typename T>
void BST<T>::removeMax() {
    if (this->isEmpty()) throw(std::runtime_error("Tree is Empty!"));
    BNode<T>* temp = this->_root, * tempPar = nullptr;
    while (temp->getRight() != nullptr) {
        tempPar = temp;
        temp = temp->getRight();
    }
    if (tempPar != nullptr) tempPar->setRight(temp->getLeft());
    else this->_root = this->_root->getLeft();
    delete temp;
}

template <typename T>
void BST<T>::removeMin() {
    if (this->isEmpty()) throw(std::runtime_error("Tree is Empty!"));
    BNode<T>* temp = this->_root, * tempPar = nullptr;
    while (temp->getLeft() != nullptr) {
        tempPar = temp;
        temp = temp->getLeft();
    }
    if (tempPar != nullptr) tempPar->setLeft(temp->getRight());
    else this->_root = this->_root->getRight();;
    delete temp;
}

template <typename T>
T BST<T>::inorderSuccessor(T value) const {
    if (isEmpty()) throw(std::runtime_error("Tree is Empty!"));
    T inorder[this->_size];
    unsigned int index = 0;
    inorderSuccessor(this->_root,inorder,index);

    for (unsigned int i = 0; i < this->_size; i++) {
        if (inorder[i] == value) {
            if (i < this->_size - 1) {
                return inorder[i+1];
            } else {
                throw(std::runtime_error(std::to_string(value) + " is last value in Inorder!"));
            }
        }
    }
    throw(std::runtime_error(std::to_string(value) + " not in tree!"));
}

template <typename T>
void BST<T>::inorderSuccessor(BNode<T>* node, T* inorder, unsigned int& index) const {
    if (node->getLeft() != nullptr) inorderSuccessor(node->getLeft(), inorder,index);
    inorder[index] = node->getValue();
    index++;
    if (node->getRight() != nullptr) inorderSuccessor(node->getRight(), inorder, index);
}

template <typename T>
void BST<T>::levelOrder() const {
    std::cout << "Level Order: ";
    for (unsigned int i = 0; i < height(this->_root); i++) {
        levelOrder(this->_root, i);
    }
    std::cout << "\n";
}

template <typename T>
void BST<T>::levelOrder(BNode<T>* node, unsigned int i) const {
    if (node == nullptr) return;
    if (i == 0) std::cout << node->getValue() << ", ";
    else {
        levelOrder(node->getLeft(), i - 1);
        levelOrder(node->getRight(), i - 1);
    }
}

template <typename T>
void BST<T>::spiralOrder() const {
    std::cout << "Spiral Level Order: ";
    for (unsigned int i = 0; i < height(this->_root); i++) {
        spiralOrder(this->_root, i, i % 2 == 0);
    }
    std::cout << "\n";
}

template <typename T>
void BST<T>::spiralOrder(BNode<T>* node, unsigned int i, bool forward) const {
    if (node == nullptr) return;
    if (i == 0) std::cout << node->getValue() << ", ";
    else {
        if (forward) {
            spiralOrder(node->getLeft(), i - 1, forward);
            spiralOrder(node->getRight(), i - 1, forward);
        }
        else {
            spiralOrder(node->getRight(), i - 1, forward);
            spiralOrder(node->getLeft(), i - 1, forward);
        }
    }
}

template <typename T>
void BST<T>::printLeft() const {
    std::cout << "Left Side View: ";
    unsigned int temp = 0;
    printLeft(this->_root, 0, temp);
    std::cout << "\n";
}

template <typename T>
void BST<T>::printRight() const {
    std::cout << "Right Side View: ";
    unsigned int temp = 0;
    printRight(this->_root, 0, temp);
    std::cout << "\n";
}

template <typename T>
void BST<T>::printLeft(BNode<T>* node, unsigned int i, unsigned int& last) const {
    if (node == nullptr) return;
    if (i == last) {
        std::cout << node->getValue() << " ";
        last++;
    }
    printLeft(node->getLeft(), i + 1, last);
    printLeft(node->getRight(), i + 1, last);
}

template <typename T>
void BST<T>::printRight(BNode<T>* node, unsigned int i, unsigned int& last) const {
    if (node == nullptr) return;
    if (i == last) {
        std::cout << node->getValue() << " ";
        last++;
    }
    printRight(node->getRight(), i + 1, last);
    printRight(node->getLeft(), i + 1, last);
}