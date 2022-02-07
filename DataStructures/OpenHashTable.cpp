template <typename T>
HashTable<T>::HashTable(unsigned int bs) {
    this->_tableSize = bs;
    this->_load = 0;
    this->_table = new LinkedList<T>[bs];
}

template <typename T>
HashTable<T>::HashTable(unsigned int bs, const HashTable& other) {
    this->_tableSize = bs; 
    this->_load = 0;
    this->_table = new LinkedList<T>[bs];
    for (unsigned int i = 0; i < other._tableSize; i++) {
        for (unsigned int j = 0; j < other._table[i].getLength(); j++) {
            this->insert(other._table[i].getEntry(j));
        }
    }
}

template <typename T>
HashTable<T>::~HashTable() {
    delete[] this->_table;   
}

template <typename T>
unsigned int HashTable<T>::hashFunction(int val) const {
    return val % this->_tableSize;
}

template <typename T>
void HashTable<T>::insert(T val) {
    unsigned int index = this->hashFunction(int(val));
    this->_table[index].insert(this->_table[index].getLength(),val);
    this->_load++;
}

template <typename T>
void HashTable<T>::remove(T val) {
    unsigned int index = this->hashFunction(int(val));
    for (int i = 0; i < this->_table[index].getLength(); i++) {
        if (this->_table[index].getEntry(i) == val) {
            this->_table[index].remove(i);
            this->_load--;
            return;
        }
    }
    throw(std::runtime_error("Value not found in list."));
}

template <typename T>
bool HashTable<T>::contains(T val) const {
    return this->_table[this->hashFunction(int(val))].contains(val);
}

template <typename T>
void HashTable<T>::clear() {
    for (unsigned int i = 0; i < this->_tableSize; i++) this->_table[i].clear();
}

template <typename T>
unsigned int HashTable<T>::size() const {
    return this->_tableSize;
}

template <typename T>
double HashTable<T>::load() const {
    return (double)this->_load / this->_tableSize;
}