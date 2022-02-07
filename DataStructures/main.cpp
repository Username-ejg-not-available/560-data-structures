#include "ClosedHashTable.h"
#include <iostream>

int main(int argc, char** argv) {
    HashTable<int>* zoinks = new HashTable<int>(5, HashTable<int>::Type::QUADRATIC);
    zoinks->insert(4);
    zoinks->insert(3);
    zoinks->insert(624);
    std::cout << zoinks->contains(624);
    zoinks->remove(3);
    zoinks->clear();
    zoinks->contains(624);
    delete zoinks;
}