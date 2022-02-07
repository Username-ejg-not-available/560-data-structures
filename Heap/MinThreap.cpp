template <typename T>
MinThreap<T>::MinThreap() : Threap<T>() {}

template <typename T>
MinThreap<T>::~MinThreap() {}

template <typename T>
void MinThreap<T>::upheap(int cur) {
    if (cur < 1) return;
    if (cur > this->_fill - 1) throw(std::runtime_error("Not in tree!"));
    if (this->_arr[cur] < this->_arr[(cur - 1) / 3]) {
        this->swap(cur,(cur-1)/3);
        upheap((cur - 1) / 3);
    }
}

template <typename T>
void MinThreap<T>::downheap(int cur) {
    int min = 0;
    T temp = this->_arr[cur];
    if (3*cur+1 < this->_fill && this->_arr[3*cur+1] < temp) temp = this->_arr[min = 3 * cur + 1];
    if (3*cur+2 < this->_fill && this->_arr[3*cur+2] < temp) temp = this->_arr[min = 3 * cur + 2];
    if (3*cur+3 < this->_fill && this->_arr[3*cur+3] < temp) temp = this->_arr[min = 3 * cur + 3];
    if (min) {
        this->swap(cur, min);
        downheap(min);
    }
}
