#include "hashtable.h"
#include <iostream>

HashTable::HashTable(unsigned int bs, unsigned int r, TableType type) {
    this->_bucketSize = bs;
    this->_load = 0;
    this->_R = r;
    this->_type = type;
    this->_list = new Node[bs];
}

HashTable::HashTable(unsigned int bs, const HashTable& other) {
    this->_bucketSize = bs;
    this->_load = 0;
    this->_R = other._bucketSize;
    this->_type = other._type;
    this->_list = new Node[bs];
    for (unsigned int i = 0; i < other._bucketSize; i++) {
        if (other._list[i].EntryType == 2) this->insert(other._list[i].Value);
    }
}

HashTable::~HashTable() {
    delete[] this->_list;
}

unsigned int HashTable::hashFunction(int num, unsigned int i) const {
    if (this->_type == TableType::QUADRATIC) return (num + i * i) % this->_bucketSize;
    return (num + i * (this->_R - num % this->_R)) % this->_bucketSize;
}

bool HashTable::contains(int num) const {
    unsigned int hash = this->hashFunction(num,0), i = 0;
    while (this->_list[hash].EntryType) {
        if (this->_list[hash].EntryType == 2 && this->_list[hash].Value == num) return true;
        hash = hashFunction(num,++i);
    }
    return false;
}

bool HashTable::insert(int num) {
    for (unsigned int i = 0; i < this->_bucketSize; i++) {
        unsigned hash = this->hashFunction(num,i);
        if (this->_list[hash].EntryType != 2) {
            this->_list[hash].Value = num;
            this->_list[hash].EntryType = 2;
            this->_load++;
            return true;
        }
    }
    return false;
}

void HashTable::remove(int num) {
    unsigned int hash = hashFunction(num,0), i = 0;
    while (this->_list[hash].EntryType) {
        if (this->_list[hash].EntryType == 2 && this->_list[hash].Value == num) {
            this->_list[hash].EntryType = 1;
            this->_load--;
            return;
        }
        hash = hashFunction(num,++i);
    }
}

unsigned int HashTable::getBucketSize() const {
    return this->_bucketSize;
}

double HashTable::getLoadFactor() const {
    return (double)this->_load / this->_bucketSize;
}

void HashTable::print() const {
    for (unsigned int i = 0; i < this->_bucketSize; i++) {
        std::cout << i;
        unsigned int spaces = std::to_string(this->_bucketSize).size() - std::to_string(i).size();
        for (unsigned int j = 0; j < spaces; j++) std::cout << " ";
        std::cout << ": " 
            << ((this->_list[i].EntryType == 2) ? std::to_string(this->_list[i].Value) : "") << "\n";
    }
}