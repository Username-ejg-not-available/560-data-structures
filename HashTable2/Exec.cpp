#include "Exec.h"
#include "useful.h"
#include <fstream>

Exec::Exec(std::string filename) {
    this->_quadTable = new HashTable(11,5,TableType::QUADRATIC);
    this->_doubTable = new HashTable(11,5,TableType::DOUBLE);
    std::ifstream inFile;
    inFile.open(filename);
    if (!inFile) {
        std::cerr << "File not found!\n";
        inFile.close();
        return;
    }
    int temp;
    while (inFile >> temp) {
        this->_quadTable->insert(temp);
        this->_doubTable->insert(temp);
    }
    inFile.close();
    this->menu();
}

Exec::~Exec() {
    delete this->_quadTable;
    delete this->_doubTable;
}

void Exec::menu() {
    bool cont = true;
    while (cont) {
        std::cout << "--------------------------------------\n"
            << "Please choose one of the following commands:\n"
            << "    1. Insert\n    2. Delete\n    3. Find\n    4. Print\n    5. Exit\n>";
        int choice, num;
        inInt(choice);
        if (choice == 1) {
            std::cout << "Choose a number to be inserted:\n>";
            inInt(num);
            std::cout << "\nQuadratic Probing:\n";
            if (this->_quadTable->contains(num)) {
                std::cout << num << " was already in list.\n";
            } else {
                if (this->_quadTable->getLoadFactor() > .5) rehash(TableType::QUADRATIC);
                if (this->_quadTable->insert(num)) std::cout << num << " has been inserted.\n";
                else std::cout << num << " could not be inserted.\n";
            }
            std::cout << "\nDouble Hashing:\n";
            if (this->_doubTable->contains(num)) {
                std::cout << num << " was already in list.\n";
            } else {
                if (this->_doubTable->getLoadFactor() > .5) rehash(TableType::DOUBLE);
                if (this->_doubTable->insert(num)) std::cout << num << " has been inserted.\n";
                else std::cout << num << " could not be inserted.\n";
            }
        } 
        else if (choice == 2) {
            std::cout << "Choose a number to be removed:\n>";
            inInt(num);
            std::cout << "\nQuadratic Probing:\n";
            if (!this->_quadTable->contains(num)) {
                std::cout << "Record not found.\n";
            } else {
                this->_quadTable->remove(num);
                std::cout << num << " has been removed.\n";
            }
            std::cout << "\nDouble Hashing:\n";
            if (!this->_doubTable->contains(num)) {
                std::cout << "Record not found.\n";
            } else {
                this->_doubTable->remove(num);
                std::cout << num << " has been removed.\n";
            }
        } 
        else if (choice == 3) {
            std::cout << "Choose a number to find:\n>";
            inInt(num);
            std::cout << "\nQuadratic Probing:\n";
            if (this->_quadTable->contains(num)) std::cout << num << " is found.\n";
            else std::cout << num << " is not found.\n";
            std::cout << "\nDouble Hashing:\n";
            if (this->_doubTable->contains(num)) std::cout << num << " is found.\n";
            else std::cout << num << " is not found.\n";
        } 
        else if (choice == 4) {
            std::cout << "\nQuadratic Probing:\n";
            this->_quadTable->print();
            std::cout << "\n\nDouble Hashing:\n";
            this->_doubTable->print();
        } 
        else if (choice == 5) {
            cont = false;
        } else {
            std::cout << "\nInvalid input\n";
        }
    }
    std::cout << "Bye Bye!!\n";
}

void Exec::rehash(TableType table) {
    if (table == TableType::QUADRATIC) {
        unsigned int newSize = this->_quadTable->getBucketSize() * 2;
        while (!isPrime(newSize)) newSize++;
        HashTable* temp = new HashTable(newSize, *this->_quadTable);
        delete this->_quadTable;
        this->_quadTable = temp;
    }
    else {
        unsigned int newSize = this->_doubTable->getBucketSize() * 2;
        while (!isPrime(newSize)) newSize++;
        HashTable* temp = new HashTable(newSize, *this->_doubTable);
        delete this->_doubTable;
        this->_doubTable = temp;
    }
    std::cout << ">Rehash applied\n";
}