#include <cmath>
#include <iostream>

template <typename T>
MinMaxHeap<T>::MinMaxHeap() {
    this->_size = 3;
    this->_fill = 0;
    this->_arr = new T[this->_size];
}

template <typename T>
MinMaxHeap<T>::~MinMaxHeap() {
    delete[] this->_arr;
}

template <typename T>
void MinMaxHeap<T>::add(T val) {
    resize();
    this->_arr[this->_fill] = val;
    this->_fill++;
    heapify(this->_fill - 1);
    /*if (verify(0)) {
        std::cout << "Valid tree\n";
    } else {
        std::cout << "Invalid tree\n\n";
        print(2);
        std::cout << "\n";
    }*/
}

template <typename T>
T MinMaxHeap<T>::pop() {
    if (!this->_fill) throw(std::runtime_error("Tree is empty!"));
    T temp = this->_arr[0];
    remove(temp);
    return temp;
}

template <typename T>
void MinMaxHeap<T>::remove(T val) {
    if (!this->_fill) throw(std::runtime_error("Tree is empty!"));
    int i = 0;
    for (; i < this->_fill; i++) {
        if (this->_arr[i] == val) break;
    }
    if (i == this->_fill) throw(std::runtime_error("Item not in tree!"));
    resize();
    this->_arr[i] = this->_arr[this->_fill - 1];
    this->_fill--;
    heapify(i);

    /*if (verify(0)) {
        std::cout << "Valid tree\n";
    } else {
        std::cout << "Invalid tree\n\n";
        print(2);
        std::cout << "\n";
    }*/
}

template <typename T>
void MinMaxHeap<T>::heapify(int i) {
    if (getLevel(i) % 2) {//on a max level
        int max = i;
        if (getLevel(i) + 1 < getLevel(this->_fill - 1)) {//has grandchildren
            if (4*i+3 < this->_fill && this->_arr[max] < this->_arr[4*i+3]) max = 4 * i + 3;
            if (4*i+4 < this->_fill && this->_arr[max] < this->_arr[4*i+4]) max = 4 * i + 4;
            if (4*i+5 < this->_fill && this->_arr[max] < this->_arr[4*i+5]) max = 4 * i + 5;
            if (4*i+6 < this->_fill && this->_arr[max] < this->_arr[4*i+6]) max = 4 * i + 6;
        }
        else if (getLevel(i) < getLevel(this->_fill - 1)) {//has children
            if (2*i+1 < this->_fill && this->_arr[max] < this->_arr[2*i+1]) max = 2 * i + 1;
            if (2*i+2 < this->_fill && this->_arr[max] < this->_arr[2*i+2]) max = 2 * i + 2;
        }
        else {//on bottom layer
            if ((double)(i - 1) / 2 >= 0 && this->_arr[max] < this->_arr[(i - 1) / 2]) max = (i - 1) / 2;
        }
        if (max != i) upheap(i);//if conceptual minheap parent is greater
        else downheap(i);
    }
    else {//on a min level
        if ((double)(i - 3) / 4 >= 0 && this->_arr[i] < this->_arr[(i - 3) / 4]) upheap(i);
        else downheap(i);
    }
}

template <typename T>
void MinMaxHeap<T>::upheap(int i) {
    if (getLevel(i) % 2) {
        int swapper = i;
        if (getLevel(i) + 1 < getLevel(this->_fill - 1)) {
            if (4*i+3 < this->_fill && this->_arr[swapper] < this->_arr[4*i+3]) swapper = 4 * i + 3;
            if (4*i+4 < this->_fill && this->_arr[swapper] < this->_arr[4*i+4]) swapper = 4 * i + 4;
            if (4*i+5 < this->_fill && this->_arr[swapper] < this->_arr[4*i+5]) swapper = 4 * i + 5;
            if (4*i+6 < this->_fill && this->_arr[swapper] < this->_arr[4*i+6]) swapper = 4 * i + 6;
        }
        else if (getLevel(i) < getLevel(this->_fill - 1)) {
            if (2*i+1 < this->_fill && this->_arr[swapper] < this->_arr[2*i+1]) swapper = 2 * i + 1;
            if (2*i+2 < this->_fill && this->_arr[swapper] < this->_arr[2*i+2]) swapper = 2 * i + 2;
        }
        else {
            if ((double)(i - 1) / 2 >= 0 && this->_arr[swapper] < this->_arr[(i - 1) / 2]) swapper = (i - 1) / 2;
        }
        if (swapper != i) {
            this->swap(i,swapper);
            upheap(swapper);
        }
    }
    else if ((double)(i - 3) / 4 >= 0 && this->_arr[i] < this->_arr[(i - 3) / 4]) {
        this->swap(i,(i - 3) / 4);
        upheap((i - 3) / 4);
    }
}

template <typename T>
void MinMaxHeap<T>::downheap(int i) {
    if (getLevel(i) % 2) {
        if ((double)(i - 3) / 4 >= 0 && this->_arr[i] > this->_arr[(i - 3) / 4]) {
            this->swap(i,(i - 3) / 4);
            downheap((i - 3) / 4);
        }
    }
    else {
        int swapper = i;
        if (getLevel(i) + 1 < getLevel(this->_fill - 1)) {
            if (4*i+3 < this->_fill && this->_arr[swapper] > this->_arr[4*i+3]) swapper = 4 * i + 3;
            if (4*i+4 < this->_fill && this->_arr[swapper] > this->_arr[4*i+4]) swapper = 4 * i + 4;
            if (4*i+5 < this->_fill && this->_arr[swapper] > this->_arr[4*i+5]) swapper = 4 * i + 5;
            if (4*i+6 < this->_fill && this->_arr[swapper] > this->_arr[4*i+6]) swapper = 4 * i + 6;
        }
        else if (getLevel(i) < getLevel(this->_fill - 1)) {
            if (2*i+1 < this->_fill && this->_arr[swapper] > this->_arr[2*i+1]) swapper = 2 * i + 1;
            if (2*i+2 < this->_fill && this->_arr[swapper] > this->_arr[2*i+2]) swapper = 2 * i + 2;
        }
        else {
            if ((double)(i - 1) / 2 >= 0 && this->_arr[swapper] > this->_arr[(i - 1) / 2]) swapper = (i - 1) / 2;
        }
        if (swapper != i) {
            this->swap(i,swapper);
            downheap(swapper);
        }
    }
}

template <typename T>
void MinMaxHeap<T>::clear() {
    this->_fill = 0;
}

template <typename T>
void MinMaxHeap<T>::resize() {
    if (this->_size == this->_fill) {
        T* temp = new T[this->_size * 2];
        for (int i = 0; i < this->_size; i++) {
            temp[i] = this->_arr[i];
        }
        delete[] this->_arr;
        this->_arr = temp;
        this->_size *= 2;
    } 
    else if (this->_size > (this->_fill + 1) * 2 && this->_fill) {
        T* temp = new T[this->_size / 2];
        for (int i = 0; i < this->_size / 2; i++) {
            temp[i] = this->_arr[i];
        }
        delete[] this->_arr;
        this->_arr = temp;
        this->_size /= 2;
    }
}

template <typename T>
void MinMaxHeap<T>::swap(int pos1, int pos2) {
    if (pos1 > this->_fill || pos2 > this->_fill) throw(std::runtime_error("Invalid swap!"));
    T temp = this->_arr[pos1];
    this->_arr[pos1] = this->_arr[pos2];
    this->_arr[pos2] = temp;
}

template <typename T>
int MinMaxHeap<T>::getLevel(unsigned int i) const {
    return log2(i + 1);
}

template <typename T>
void MinMaxHeap<T>::print(int op) const {
    for (int i = 0; i < this->_fill; i++) {
        if (op == 2 || (int)log2(i + 1) % 2 == op) {
            std::cout << this->_arr[i] << " ";
            if (i < 1 || log2(i + 2) == (int)log2(i + 2)) std::cout << "\n";
        }
    }
    std::cout << "\n";
}

template <typename T>
bool MinMaxHeap<T>::verify(int i) const {
    if (i >= this->_fill - 1) return true;
    if (getLevel(i) % 2) {
        if (2*i+1 < this->_fill && this->_arr[i] < this->_arr[2*i+1]) return false;
        if (2*i+2 < this->_fill && this->_arr[i] < this->_arr[2*i+2]) return false;
        if (4*i+3 < this->_fill && this->_arr[i] < this->_arr[4*i+3]) return false;
        if (4*i+4 < this->_fill && this->_arr[i] < this->_arr[4*i+4]) return false;
        if (4*i+5 < this->_fill && this->_arr[i] < this->_arr[4*i+5]) return false;
        if (4*i+6 < this->_fill && this->_arr[i] < this->_arr[4*i+6]) return false;
        return verify(2 * i + 1) && verify(2 * i + 2);
    }
    else {
        if (2*i+1 < this->_fill && this->_arr[i] > this->_arr[2*i+1]) return false;
        if (2*i+2 < this->_fill && this->_arr[i] > this->_arr[2*i+2]) return false;
        if (4*i+3 < this->_fill && this->_arr[i] > this->_arr[4*i+3]) return false;
        if (4*i+4 < this->_fill && this->_arr[i] > this->_arr[4*i+4]) return false;
        if (4*i+5 < this->_fill && this->_arr[i] > this->_arr[4*i+5]) return false;
        if (4*i+6 < this->_fill && this->_arr[i] > this->_arr[4*i+6]) return false;
        return verify(2 * i + 1) && verify(2 * i + 2);
    }
    return true;
}