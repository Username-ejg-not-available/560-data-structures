#include "Exec.h"
#include <iostream>
#include <limits>
#include <fstream>

void inInt(int& out);

Exec::Exec(std::string filename) {
    this->_leftHeap = new LeftistHeap<int>();
    menu(filename);
}

Exec::~Exec() {
    delete this->_leftHeap;
}

void Exec::menu(std::string filename) {
bool cont = true;
    while (cont) {
        std::cout << "--------------------------------------\n"
            << "Please choose one of the following commands:\n"
            << "    1. BuildHeap\n    2. Insert\n    3. Concatentate\n    4. DeleteMin\n"
            << "    5. FindMin\n    6. Inorder\n    7. LevelOrder\n    8. Exit\n> Enter your choice:\n> ";
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
            this->_leftHeap->clear();
            while (inFile >> temp) {
                if (temp == "") break;
                int x =((temp[temp.size() - 1] == ',') ? std::stoi(temp.substr(0,temp.size() - 1)) : std::stoi(temp));
                if (!this->_leftHeap->contains(x)) this->_leftHeap->add(x);
                else std::cout << x << " already in heap!\n";
            }
            inFile.close();
            std::cout << "Output: Heap built successfully. The new level order traversal is: ";
            _leftHeap->levelOrder();
        } 
        else if (choice == 2) {
            std::cout << "> Output: Enter the value you want to insert: ";
            inInt(num);
            try {
                if (!this->_leftHeap->contains(num)) {
                    this->_leftHeap->add(num);
                    std::cout << "> Output: " << num << " has been successfully inserted into the heap. The new level order traversal is: ";
                    this->_leftHeap->levelOrder();
                } else {
                    std::cout << num << " already in heap!\n";
                }
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
        } 
        else if (choice == 3) {
            std::cout << "Enter the three elements for heap B.\n>";
            int temp, count = 0;
            LeftistHeap<int> tempheap;
            while (count != 3) {
                inInt(temp);
                if (!this->_leftHeap->contains(temp) && !tempheap.contains(temp)) {
                    tempheap.add(temp);
                    count++;
                } else {
                    std::cout << temp << " already in heap!\n";
                }
                if (count != 3) std::cout << ">";
            }
            bool swapped = false;
            try {
                swapped = this->_leftHeap->findMin() > tempheap.findMin();
            } catch (std::runtime_error& e) {}
            this->_leftHeap->concat(tempheap);
            std::cout << ">Output: Trees A and B have been merged to form new tree C.\n";
            if (swapped) std::cout << "Subtrees have been swapped.\n";
            std::cout << "The new level order traversal is: ";
            this->_leftHeap->levelOrder();
        } 
        else if (choice == 4) {
            try {
                int temp = this->_leftHeap->deleteMin();
                std::cout << "> Output: The minimum element " << temp << " has been deleted. The new level order traversal is: ";
                this->_leftHeap->levelOrder();
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
        }
        else if (choice == 5) {
            try {
                int temp = this->_leftHeap->findMin();
                std::cout << "> Output: " << temp << " is the minimum element.\n";
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
        }
        else if (choice == 6) {
            std::cout << "> Output: The in order traversal for the heap is: ";
            this->_leftHeap->inOrder();
        }
        else if (choice == 7) {
            std::cout << "> Output: The level order traversal for the heap is: ";
            this->_leftHeap->levelOrder();
        }
        else if (choice == 8) {
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
