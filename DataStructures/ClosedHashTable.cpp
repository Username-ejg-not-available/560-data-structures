template <typename T>
HashTable<T>::HashTable(unsigned int bs, Type type) {
    this->_tableSize = bs;
    this->_load = 0;
    this->_type = type;
    this->_table = new Node[bs];
}

template <typename T>
HashTable<T>::HashTable(unsigned int bs, const HashTable& other) {
    this->_tableSize = bs;
    this->_load = 0;
    this->_type = other._type;
    this->_table = new Node[bs];
    for (unsigned int i = 0; i < other._tableSize; i++) {
        if (other._table[i].NodeState == Node::State::FULL) this->insert(other._table[i].Entry);
    }
}

template <typename T>
HashTable<T>::~HashTable() {
    delete[] this->_table;
}

template <typename T>
unsigned int HashTable<T>::hashFunction(int x, unsigned int i) const {
    if (this->_type == Type::LINEAR) return (x + i) % this->_tableSize;
    else if (this->_type == Type::QUADRATIC) return (x + i * i) % this->_tableSize;
    else return (x + i * (3 - (x % 3))) % this->_tableSize;
}

template <typename T>
bool HashTable<T>::insert(T val) {
    for (unsigned int i = 0; i < this->_tableSize; i++) {
        unsigned int hash = hashFunction(int(val), i);
        if (this->_table[hash].NodeState != Node::State::FULL) {
            this->_table[hash].Entry = val;
            this->_table[hash].NodeState = Node::State::FULL;
            this->_load++;
            return true;
        }
    }
    return false;
}

template <typename T>
void HashTable<T>::remove(T val) {
    unsigned int i = 0, hash = hashFunction(int(val), i);
    while (this->_table[hash].NodeState != Node::State::EMPTY) {
        if (this->_table[hash].NodeState == Node::State::FULL && this->_table[hash].Entry == val) {
            this->_table[hash].NodeState = Node::State::DELETED;
            this->_load--;
            return;
        }
        hash = hashFunction(int(val), ++i);
    }
}

template <typename T>
void HashTable<T>::clear() {
    for (unsigned int i = 0; i < this->_tableSize; i++) {
        this->_table[i].NodeState = Node::State::EMPTY;
    }
}

template <typename T>
bool HashTable<T>::contains(T val) const {
    for (unsigned int i = 0; i < this->_tableSize; i++) {
        if (this->_table[i].Entry == val) return true;
    }
    return false;
}

template <typename T>
unsigned int HashTable<T>::size() const {
    return this->_tableSize;
}

template <typename T>
double HashTable<T>::load() const {
    return (double)this->_load / this->_tableSize;
}