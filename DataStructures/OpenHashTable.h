#ifndef OPENHASHTABLE_H
#define OPENHASHTABLE_H

#include "LinkedList.h"

template <typename T>
class HashTable {
private:
    unsigned int _tableSize, _load;
    LinkedList<T>* _table;
    unsigned int hashFunction(int) const;
public:
    HashTable(unsigned int);
    HashTable(unsigned int, const HashTable&);
    ~HashTable();
    void insert(T);
    void remove(T);
    bool contains(T) const;
    void clear();
    unsigned int size() const;
    double load() const;
};
#include "OpenHashTable.cpp"
#endif