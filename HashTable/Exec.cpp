/**
* @author Ethan Grantz
* @file Exec.cpp
* @date 2/8/2021
* @brief defines the functions that the Exec class needs to work
*/
#include "Exec.h"
#include <fstream>
#include <iostream>
#include <limits>

Exec::Exec(std::string filename) {
    this->_hashTable = new HashTable(11);
    std::ifstream inFile;
    inFile.open(filename);
    if (!inFile) {
        std::cout << "File not Found!\n";
        return;
    }
    while (!inFile.eof()) {
        std::string id,name;
        inFile >> id >> name;
        if (id == "") break;
        if (name[name.size() - 1] == ',') name = name.substr(0,name.size()-1);
        this->_hashTable->insert(name,std::stoi(id));
    }
    inFile.close();
    this->menu();
}

Exec::~Exec() {
    delete this->_hashTable;
}

void Exec::menu() {
    bool cont = true;
    while (cont) {
        std::cout << "Please choose one of the following commands:\n"
            << "1- AddStudent\n2- RemoveStudent\n3- PrintStudentList\n"
            << "4- FindStudent\n5- Exit\n\n>Input: ";
        int choice;
        std::string tempStr;
        inInt(choice);
        switch (choice) {
        case 1:
            std::cout << ">Enter the record to be inserted:\n>";
            getline(std::cin,tempStr);
            if (tempStr.size() < 8 || !isnum(tempStr.substr(0,5)) 
                || tempStr[5] != ':' || tempStr[6] != ' ' || !islower(tempStr.substr(7))) 
            {
                std::cout << ">Invalid Input.\n\n";
                break;
            }
            try {
                this->_hashTable->insert(tempStr.substr(7),std::stoi(tempStr.substr(0,5)));
                std::cout << ">Output: Record is successfully inserted.\n\n";
            } catch (std::runtime_error& e) {
                std::cout << ">Output: Record was not added successfully\n\n";
            }
            break;
        case 2:
            std::cout << ">Enter a record to be removed:\n>";
            std::getline(std::cin, tempStr);
            if (tempStr.size() < 8 || !isnum(tempStr.substr(0,5)) 
                || tempStr[5] != ':' || tempStr[6] != ' ' || !islower(tempStr.substr(7))) 
            {
                std::cout << ">Invalid Input.\n\n";
                break;
            }
            try {
                this->_hashTable->remove(tempStr.substr(7),std::stoi(tempStr.substr(0,5)));
                std::cout << ">Record has been removed from the hash table.\n\n";
            } catch (std::runtime_error& e) {
                std::cout << ">No record found\n\n";
            }
            break;
        case 3:
            printStudentList();
            break;
        case 4:
            std::cout << ">Enter the student to be found:\n>";
            std::cin >> tempStr;
            try {
                int ind = this->_hashTable->getIndex(tempStr);
                std::cout << ">Record found at index " << ind << "\n\n";
            } catch (std::runtime_error& e) {
                std::cout << ">Record not found\n\n";
            }
            break;
        case 5:
            cont = false;
            break;
        default:
            break;
        }
    }
    std::cout << ">Bye bye!\n";
}

void Exec::inInt(int& out) {
	std::cin >> out;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "You daft fool. You absolute Buffoon. That's not a valid input!\n>";
		std::cin >> out;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Exec::printStudentList() const {
    std::cout << "\n";
    for (unsigned int i = 0; i < this->_hashTable->getBucketSize(); i++) {
        std::cout << i << ": " << this->_hashTable->getPrintString(i) << "\n";
    }
    std::cout << "\n";
}

bool Exec::isnum(std::string str) const {
    for (char c : str) {
        if (c < 48 || c > 57) return false;
    }
    return true;
}

bool Exec::islower(std::string str) const {
    for (char c : str) {
        if (c < 97 || c > 122) return false;
    }
    return true;
}
