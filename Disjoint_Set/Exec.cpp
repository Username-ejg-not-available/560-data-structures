#include "Exec.h"
#include <iostream>
#include <limits>
#include <fstream>

void inInt(int& out);

Exec::Exec(std::string filename) {
    this->_disjSet = new DisjointSet<int>();
    menu(filename);
}

Exec::~Exec() {
    delete this->_disjSet;
}

void Exec::menu(std::string filename) {
bool cont = true;
    while (cont) {
        std::cout << "--------------------------------------\n"
            << "Please choose one of the following commands:\n"
            << "    1. MakeSet\n    2. UnionByRank\n    3. Find\n    4. PathCompression\n"
            << "    5. PrintPath\n    6. Exit\n> Enter your choice:\n> ";
        int choice, num;
        std::string temp;
        inInt(choice);
        if (choice == 1) {
            std::ifstream inFile;
            inFile.open(filename);
            if (!inFile) {
                std::cerr << "File not found!\n";
                inFile.close();
                continue;
            }
            this->_disjSet->clear();
            while (inFile >> temp) {
                if (temp == "") break;
                if (!this->_disjSet->contains(std::stoi(temp))) this->_disjSet->add(std::stoi(temp));
                else std::cout << temp << " already in sets!\n";
            }
            inFile.close();
            std::cout << "> Output: The disjoint sets have been constructed.\n";
        } 
        else if (choice == 2) {
            std::cout << "> Output: Enter the representative elements for the two sets which you wish to union:\n> ";
            int num2;
            inInt(num);
            std::cout << "> ";
            inInt(num2);
            try {
                int temp = this->_disjSet->unionByRank(num,num2);
                std::cout << "> Output: Union on " << num << " and " << num2 << " has been done. The representative element is " << temp << "\n";
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
        } 
        else if (choice == 3) {
            std::cout << "> Output: Enter the element you want to find:\n> ";
            inInt(num);
            try {
                int rep = this->_disjSet->find(num);
                std::cout << "> Output: Element " << num << " has been found successfully."
                    << " The representative element is " << rep << ".\n";
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
        } 
        else if (choice == 4) {
            std::cout << "> Output: Enter the element on whose set you would want to perform path compression.\n> ";
            inInt(num);
            try {
                int rep = this->_disjSet->find(num);
                std::cout << "> Output: Path Compression has been done successfully. "
                    << "The representative element is " << rep << ".\n";
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
        }
        else if (choice == 5) {
            std::cout << "> Output: Enter the element you want to find the path for:\n> ";
            inInt(num);
            this->_disjSet->printPath(num);
        }
        else if (choice == 6) {
            cont = false;
        }
        else {
            std::cout << "\nInvalid input\n";
        }
    }
    std::cout << "> Output: Bye Bye!\n";
}

void inInt(int& out) {
	std::cin >> out;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "That's not a valid input!\n> ";
		std::cin >> out;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}