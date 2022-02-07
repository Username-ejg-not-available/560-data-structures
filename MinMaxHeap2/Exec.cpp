#include "Exec.h"
#include "ExProf.h"
#include <iostream>
#include <limits>
#include <fstream>

void inInt(int& out);

Exec::Exec(std::string filename) {
    this->_minMaxHeap = new MinMaxHeap<int>();
    menu(filename);
}

Exec::~Exec() {
    delete this->_minMaxHeap;
}

void Exec::menu(std::string filename) {
bool cont = true;
    while (cont) {
        std::cout << "--------------------------------------\n"
            << "Please choose one of the following commands:\n"
            << "    1. BuildHeap\n    2. Insert\n    3. DeleteMin\n    4. DeleteMax\n"
            << "    5. FindMin\n    6. FindMax\n    7. LevelOrder\n    8. ExperimentalProfiling\n"
            << "    9. Exit\n> Enter your choice:\n> ";
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
            std::string temp;
            while (inFile >> temp) {
                this->_minMaxHeap->add(
                    ((temp[temp.size() - 1] == ',') ? 
                    std::stoi(temp.substr(0,temp.size() - 1)) : std::stoi(temp)));
            }
            inFile.close();
            std::cout << ">Output:\n";
            this->_minMaxHeap->print(2);
        } 
        else if (choice == 2) {
            std::cout << "> Enter element to be inserted: ";
            inInt(num);
            try {
                this->_minMaxHeap->add(num);
                std::cout << "> Output: " << num << " has been inserted successfully.\n";
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
        } 
        else if (choice == 3) {
            try {
                int temp = this->_minMaxHeap->popMin();
                std::cout << "> Output: " << temp << " has been deleted successfully.\n";
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
        } 
        else if (choice == 4) {
            try {
                int temp = this->_minMaxHeap->popMax();
                std::cout << "> Output: " << temp << " has been deleted successfully.\n";
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
        }
        else if (choice == 5) {
            try {
                int temp = this->_minMaxHeap->findMin();
                std::cout << "> Output: " << temp << " is the minimum element.\n";
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
        }
        else if (choice == 6) {
            try {
                int temp = this->_minMaxHeap->findMax();
                std::cout << "> Output: " << temp << " is the maximum element.\n";
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
        }
        else if (choice == 7) {
            std::cout << ">Output:\n";
            this->_minMaxHeap->print(2);
        }
        else if (choice == 8) {
            ExProf e;
            std::cout << e.getPrintString() << "\n";
        }
        else if (choice == 9) {
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
		std::cout << "You daft fool. You absolute Buffoon. That's not a valid input!\n> ";
		std::cin >> out;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}