#include "Exec.h"
#include "ExProf.h"
#include <iostream>
#include <fstream>
#include <limits>

void inInt(int&);

Exec::Exec(std::string filename) {
    std::ifstream inFile;
    inFile.open(filename);
    this->_tree = new BST<int>();
    if (!inFile) {
        std::cerr << "File not found!\n";
        inFile.close();
        return;
    }
    int temp;
    while (inFile >> temp) {
        this->_tree->add(temp);
    }
    inFile.close();
    menu();
}

Exec::~Exec() {
    delete _tree;
}

void Exec::menu() {
bool cont = true;
    while (cont) {
        std::cout << "--------------------------------------\n"
            << "Please choose one of the following commands:\n"
            << "    1.  AddItem\n    2.  DeleteItem\n    3.  FindMin\n    4.  FindMax\n" 
            << "    5.  DeleteMin\n    6.  DeleteMax\n    7.  InorderSuccessor\n"
            << "    8.  LevelOrder\n    9.  SpiralLevelOrder\n    10. LeftSideView\n"
            << "    11. RightSideView\n    12. ExperimentalProfiling\n    13. Exit\n>";
        int choice, num;
        inInt(choice);
        if (choice == 1) {
            std::cout << ">Enter the element to be added: ";
            std::cin >> num;
            this->_tree->add(num);
            std::cout << ">Element " << num << " was successfully added.\n";
        } 
        else if (choice == 2) {
            std::cout << ">Enter the element to be deleted: ";
            std::cin >> num;
            try {
                this->_tree->remove(num);
                std::cout << ">Element " << num << " was successfully deleted.\n";
            } catch (std::runtime_error& e) {
                std::cout << ">" << e.what() << "\n";
            }
        } 
        else if (choice == 3) {
            try {
                num = this->_tree->findMin();
                std::cout << ">Smallest element in the tree is: " << num << "\n";
            } catch (std::runtime_error& e) {
                std::cout << ">" << e.what() << "\n";
            }
        } 
        else if (choice == 4) {
            try {
                num = this->_tree->findMax();
                std::cout << ">Largest element in the tree is: " << num << "\n";
            } catch (std::runtime_error& e) {
                std::cout << ">" << e.what() << "\n";
            }
        }
        else if (choice == 5) {
            try {
                this->_tree->removeMin();
                std::cout << ">Smallest element was successfully deleted from the tree.\n";
            } catch (std::runtime_error& e) {
                std::cout << ">" << e.what() << "\n";
            }
        }
        else if (choice == 6) {
            try {
                this->_tree->removeMax();
                std::cout << ">Largest element was successfully deleted from the tree.\n";
            } catch (std::runtime_error& e) {
                std::cout << ">" << e.what() << "\n";
            }
        }
        else if (choice == 7) {
            std::cout << "Enter the element to which you want to know the inorder successor: ";
            std::cin >> num;
            try {
                int res = this->_tree->inorderSuccessor(num);
                std::cout << ">The inorder successor of " << num << " is " << res << "\n";
            } catch (std::runtime_error& e) {
                std::cout << ">" << e.what() << "\n";
            }

        }
        else if (choice == 8) {
            this->_tree->levelOrder();
        }
        else if (choice == 9) {
            this->_tree->spiralOrder();
        }
        else if (choice == 10) {
            this->_tree->printLeft();
        }
        else if (choice == 11) {
            this->_tree->printRight();
        }
        else if (choice == 12) {
            ExProf e;
            std::cout << e.getPrintString() << "\n";
        } 
        else if (choice == 13) {
            cont = false;
        } else {
            std::cout << "\nInvalid input\n";
        }
    }
    std::cout << ">Done.\n";
}

void inInt(int& out) {
	std::cin >> out;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "You daft fool. You absolute Buffoon. That's not a valid input!\n>";
		std::cin >> out;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}