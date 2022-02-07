/**
* @author Ethan Grantz
* @file HashTable.cpp
* @date 2/8/2021
* @brief defines the functions that the HashTable class needs to work
*/
#include "HashTable.h"

HashTable::HashTable(unsigned int bs) {
    this->_bucketSize = bs;
    this->_arr = new LinkedList<LinkedList<Data>*>();
    for (unsigned int i = 0; i < bs; i++) {
        this->_arr->insert(i,new LinkedList<Data>());
    }
}

HashTable::~HashTable() {
    for (unsigned int i = 0; i < this->_bucketSize; i++) delete this->_arr->getEntry(i);
    delete this->_arr;
}

int HashTable::hashFunction(std::string name) const {
    int result = 0;
    for (char c : name) {
        result += c;
    }
    return result % this->_bucketSize;
}

unsigned int HashTable::getBucketSize() const {
    return this->_bucketSize;
}

void HashTable::insert(std::string key, int id) {
    if (this->contains(key,id)) throw(std::runtime_error("Entry already in table!"));
    LinkedList<Data>* temp = this->_arr->getEntry(this->hashFunction(key));
    temp->insert(temp->getLength(), Data(key,id));
}

void HashTable::remove(std::string key, int id) {
    if (!this->contains(key, id)) throw(std::runtime_error("Entry not in table!"));
    LinkedList<Data>* temp = this->_arr->getEntry(this->hashFunction(key));
    for (unsigned int i = 0; i < temp->getLength(); i++) {
        if (temp->getEntry(i).Key == key && temp->getEntry(i).Id == id) {
            temp->remove(i);
            break;
        }
    }
}

HashTable::Data HashTable::get(std::string key) const {
    LinkedList<Data>* temp = this->_arr->getEntry(this->hashFunction(key));
    for (unsigned int i = 0; i < temp->getLength(); i++) {
        if (temp->getEntry(i).Key == key) return temp->getEntry(i);
    }
    throw(std::runtime_error("Entry not found!"));
}

unsigned int HashTable::getIndex(std::string key) const {
    this->get(key);
    return this->hashFunction(key);
}

bool HashTable::contains(std::string key, int id) const {
    try {
        Data x = this->get(key);
        if (x.Id != id) return false;
    } catch (std::runtime_error& e) {
        return false;
    }
    return true;
}

std::string HashTable::getPrintString(unsigned int index) const {
    if (index > this->_bucketSize || !this->_arr->getEntry(index)->getLength()) return "";
    LinkedList<Data>* temp = this->_arr->getEntry(index);
    std::string result = "";
    for (unsigned int i = 0; i < temp->getLength(); i++) {
        Data d = temp->getEntry(i);
        result += "-> " + std::to_string(d.Id) + " " + d.Key + " ";
    }
    return result;
}