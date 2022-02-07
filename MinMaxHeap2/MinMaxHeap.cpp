#include <iostream>
#include <cmath>

template <typename T>
void MinMaxHeap<T>::upheap(int i) {
    if (!i) return;
    if (getLevel(i) % 2) {
        if (this->_arr[i] > this->_arr[(i-1)/2]) {
            if (i > 2 && this->_arr[i] > this->_arr[(i-3)/4]) {
                this->swap(i,(i-3)/4);
                upheap((i-3)/4);
            }
        } else {
            this->swap(i,(i-1)/2);
            upheap((i-1)/2);
        }
    } else {
        if (this->_arr[i] < this->_arr[(i-1)/2]) {
            if (i > 2 && this->_arr[i] < this->_arr[(i-3)/4]) {
                this->swap(i,(i-3)/4);
                upheap((i-3)/4);
            }
        } else {
            this->swap(i,(i-1)/2);
            upheap((i-1)/2);
        }
    }
}

template <typename T>
void MinMaxHeap<T>::downheap(int i) {
    if (getLevel(i) % 2) {
        int max = i;
        if (2 * i + 1 < this->_fill) max = 2 * i + 1;
        if (2 * i + 2 < this->_fill && this->_arr[max] < this->_arr[2 * i + 2]) max = 2 * i + 2;
        if (4 * i + 3 < this->_fill && this->_arr[max] < this->_arr[4 * i + 3]) max = 4 * i + 3;
        if (4 * i + 4 < this->_fill && this->_arr[max] < this->_arr[4 * i + 4]) max = 4 * i + 4;
        if (4 * i + 5 < this->_fill && this->_arr[max] < this->_arr[4 * i + 5]) max = 4 * i + 5;
        if (4 * i + 6 < this->_fill && this->_arr[max] < this->_arr[4 * i + 6]) max = 4 * i + 6;
        if (max > 2 * i + 2) {
            if (this->_arr[max] > this->_arr[i]) {
                swap(i,max);
                if (this->_arr[max] < this->_arr[(max-1)/2]) {
                    swap(max,(max-1)/2);
                }
                downheap(max);
            }
        } else if (this->_arr[max] > this->_arr[i]) {
            this->swap(i,max);
        }
    } else {
        int min = i;
        if (2 * i + 1 < this->_fill) min = 2 * i + 1;
        if (2 * i + 2 < this->_fill && this->_arr[min] > this->_arr[2 * i + 2]) min = 2 * i + 2;
        if (4 * i + 3 < this->_fill && this->_arr[min] > this->_arr[4 * i + 3]) min = 4 * i + 3;
        if (4 * i + 4 < this->_fill && this->_arr[min] > this->_arr[4 * i + 4]) min = 4 * i + 4;
        if (4 * i + 5 < this->_fill && this->_arr[min] > this->_arr[4 * i + 5]) min = 4 * i + 5;
        if (4 * i + 6 < this->_fill && this->_arr[min] > this->_arr[4 * i + 6]) min = 4 * i + 6;
        if (min > 2 * i + 2) {
            if (this->_arr[min] < this->_arr[i]) {
                swap(i,min);
                if (this->_arr[min] > this->_arr[(min-1)/2]) {
                    swap(min,(min-1)/2);
                }
                downheap(min);
            }
        } else if (this->_arr[min] < this->_arr[i]) {
            this->swap(i,min);
        }
    }
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
MinMaxHeap<T>::MinMaxHeap() {
    this->_size = 900000;
    this->_fill = 0;
    this->_arr = new T[this->_size];
}

template <typename T>
MinMaxHeap<T>::~MinMaxHeap() {
    delete[] this->_arr;
}

template <typename T>
void MinMaxHeap<T>::add(T val) {
    //resize();
    this->_arr[this->_fill] = val;
    this->_fill++;
    upheap(this->_fill - 1);
}

template <typename T>
T MinMaxHeap<T>::popMin() {
    if (!this->_fill) throw(std::runtime_error("Tree is empty!"));
    T temp = this->_arr[0];
    this->_arr[0] = this->_arr[this->_fill - 1];
    this->_fill--;
    downheap(0);
    return temp;
}

template <typename T>
T MinMaxHeap<T>::popMax() {
    if (!this->_fill) throw(std::runtime_error("Tree is empty!"));
    T temp;
    int index = 0, second = 0;
    if (this->_fill == 1) temp = this->_arr[second = index = 0];
    else if (this->_fill == 2) temp = this->_arr[second = index = 1];
    else {
        if (this->_arr[1] > this->_arr[2]) second = (index = 1) + 1;
        else second = (index = 2) - 1;
        if (2*index+1 < this->_fill && this->_arr[2*index+1] > this->_arr[second]) second = 2*index+1;
        if (2*index+2 < this->_fill && this->_arr[2*index+2] > this->_arr[second]) second = 2*index+2;
        if (4*index+3 < this->_fill && this->_arr[4*index+3] > this->_arr[second]) second = 4*index+3;
        if (4*index+4 < this->_fill && this->_arr[4*index+4] > this->_arr[second]) second = 4*index+4;
        if (4*index+5 < this->_fill && this->_arr[4*index+5] > this->_arr[second]) second = 4*index+5;
        if (4*index+6 < this->_fill && this->_arr[4*index+6] > this->_arr[second]) second = 4*index+6;
    }
    temp = this->_arr[index];
    this->_arr[index] = this->_arr[second];
    this->_arr[second] = this->_arr[this->_fill - 1];
    this->_fill--;
    downheap(second);
    return temp;
}

template <typename T>
T MinMaxHeap<T>::findMin() {
    if (!this->_fill) throw(std::runtime_error("Tree is empty!"));
    return this->_arr[0];
}

template <typename T>
T MinMaxHeap<T>::findMax() {
    if (!this->_fill) throw(std::runtime_error("Tree is empty!"));
    if (this->_fill == 1) return this->_arr[0];
    else if (this->_fill == 2) return this->_arr[1];
    else return (this->_arr[1] > this->_arr[2]) ? this->_arr[1]: this->_arr[2];
}

template <typename T>
void MinMaxHeap<T>::clear() {
    this->_fill = 0;
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
