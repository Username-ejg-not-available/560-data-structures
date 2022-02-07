template <typename T>
MinHeap<T>::MinHeap() : Heap<T>() {}

template <typename T>
MinHeap<T>::~MinHeap() {}

template <typename T>
void MinHeap<T>::upheap(int cur) {
    if (cur > this->_fill - 1) throw(std::runtime_error("Not in tree!"));
    if (this->_arr[cur] < this->_arr[(cur - 1) / 2]) {
        this->swap(cur,(cur-1)/2);
        upheap((cur - 1) / 2);
    }
}

template <typename T>
void MinHeap<T>::downheap(int cur) {
    int min = 0;
    T temp = this->_arr[cur];
    if (2*cur+1 < this->_fill && this->_arr[2*cur+1] < temp) temp = this->_arr[min = 2 * cur + 1];
    if (2*cur+2 < this->_fill && this->_arr[2*cur+2] < temp) temp = this->_arr[min = 2 * cur + 2];
    if (min) {
        this->swap(cur, min);
        downheap(min);
    }
}

template <typename T>
bool MinHeap<T>::uniRemoveCond(T par, T cur) const {
    return par > cur;
}