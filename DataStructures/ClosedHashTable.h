#ifndef CLOSEDHASHTABLE_H
#define CLOSEDHASHTABLE_H

template <typename T>
class HashTable {
public:
    enum class Type { LINEAR, QUADRATIC, DOUBLEHASH };
    HashTable(unsigned int, Type);
    HashTable(unsigned int, const HashTable&);
    ~HashTable();
    bool insert(T);
    void remove(T);
    void clear();
    bool contains(T) const;
    unsigned int size() const;
    double load() const;
private:
    struct Node {
        enum class State { EMPTY, FULL, DELETED };
        T Entry;
        State NodeState;
        Node() : NodeState(State::EMPTY) {} 
    };

    unsigned int _tableSize, _load;
    Node* _table;
    Type _type;
    unsigned int hashFunction(int,unsigned int) const;
};
#include "ClosedHashTable.cpp"
#endif