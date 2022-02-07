#include "Exec.h"
#include <iostream>
#include <limits>
#include <fstream>

void inInt(int& out);
Restaurant toRestaurant(std::string);

Exec::Exec(std::string filename) {
    std::ifstream inFile;
    inFile.open(filename);
    this->_minThreap = new MinThreap<Restaurant>();
    this->_maxThreap = new MaxThreap<Restaurant>();
    if (!inFile) {
        std::cerr << "File not found!\n";
        inFile.close();
        return;
    }
    std::string temp;
    while (!inFile.eof()) {
        getline(inFile, temp);
        if (temp == "") break;
        try {
            this->_minThreap->add(toRestaurant(temp));
        } catch (std::runtime_error& e) {
            std::cout << e.what() << "\n";
        }
        try {
            this->_maxThreap->add(toRestaurant(temp));
        } catch (std::runtime_error& e) {
            std::cout << e.what() << "\n";
        }
    }
    inFile.close();
    menu();
}

Exec::~Exec() {
    delete this->_maxThreap;
    delete this->_minThreap;
}

void Exec::menu() {
bool cont = true;
    while (cont) {
        std::cout << "--------------------------------------\n"
            << "Please choose one of the following commands:\n"
            << "    1. Add New Restaurant\n    2. Remove Nearest Restaurant\n"
            << "    3. Remove Most Reviewed Restaurant\n    4. Search Nearest Restaurant\n" 
            << "    5. Search Most Reviewed Restaurant\n    6. Print By Restaurant Distance\n"
            << "    7. Print By Restaurant Review Count\n    8. Exit\n> ";
        int choice;
        std::string temp;
        inInt(choice);
        if (choice == 1) {
            std::cout << "> Enter the record to be inserted:\n> ";
            getline(std::cin, temp);
            Restaurant tempRest = toRestaurant(temp);
            try {
                if (this->_minThreap->contains(tempRest)) std::cout << tempRest.Name << " already in Distance heap!\n";
                else this->_minThreap->add(tempRest);
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
            try {
                if (this->_maxThreap->contains(tempRest)) std::cout << tempRest.Name << " already in Review heap!\n";
                else this->_maxThreap->add(tempRest);
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
        } 
        else if (choice == 2) {
            try {
                Restaurant temp = this->_minThreap->pop();
                std::cout << "Nearest: " << temp.Name << ": " << temp.Dist << " has been removed.\n";
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
        } 
        else if (choice == 3) {
            try {
                Restaurant temp = this->_maxThreap->pop();
                std::cout << "Most reviewed restaurant: " << temp.Name << ": " << temp.Reviews << " has been removed.\n";
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
        } 
        else if (choice == 4) {
            try {
                Restaurant temp = this->_minThreap->peek();
                std::cout << "> Nearest restaurant: " << temp.Name << "\n> Distance: " << temp.Dist << " miles\n";
            } catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
        }
        else if (choice == 5) {
            try {
                Restaurant temp = this->_maxThreap->peek();
                std::cout << "> Most reviewed restaurant: " << temp.Name << "\n> Number of reviews: " << temp.Dist << "\n";
            } catch (std::runtime_error& e) {
            	std::cout << e.what() << "\n";
            }
        }
        else if (choice == 6) {
            this->_minThreap->print();
        }
        else if (choice == 7) {
            this->_maxThreap->print();
        }
        else if (choice == 8) {
            cont = false;
        } else {
            std::cout << "\nInvalid input\n";
        }
    }
    std::cout << "> Done.\n";
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

Restaurant toRestaurant(std::string text) {
    Restaurant r;
    unsigned int i = 0;
    for (; i < text.size(); i++) {
        if (text[i] == ',') {
            if (r.Name == "") r.Name = text.substr(0,i);
            else if (r.Dist == 0) {
                r.Dist = std::stof(text.substr(r.Name.size() + 2, i));
                break;
            }
        }
    }
    r.Reviews = stoi(text.substr(i + 2));
    return r;
}
