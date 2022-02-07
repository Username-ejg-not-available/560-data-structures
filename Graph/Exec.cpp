#include "Exec.h"
#include <iostream>
#include <limits>
#include <fstream>

void inInt(int& out);

Exec::Exec(std::string filename) {
    this->_graph = new Graph(0);
    menu(filename);
}

Exec::~Exec() {
    delete this->_graph;
}

void Exec::menu(std::string filename) {
bool cont = true;
    while (cont) {
        std::cout << "--------------------------------------\n"
            << "Please choose one of the following commands:\n"
            << "    1. BuildGraph\n    2. BFS\n    3. DFS\n    4. Kruskal\n"
            << "    5. Prim\n    6. Exit\n> Enter your choice:\n> ";
        int choice, num;
        std::string temp;
        inInt(choice);
        if (choice == 1) {
            std::ifstream inFile;
            inFile.open(filename);
            inFile >> temp;
            int err = sscanf(temp.c_str(), "n,%d", &num);
            if (err != 1 || num < 0) continue;
            delete this->_graph;
            this->_graph = new Graph(num);
            int tempnum;
            for (int i = 0; i < num; i++) {
                for (int j = 0; j < num; j++) {
                    inFile >> tempnum;
                    if (tempnum == -1) continue;
                    try {
                        this->_graph->addEdge(Graph::Edge(i + 1,j + 1,tempnum));
                    } catch (std::runtime_error& e) {
                        std::cout << e.what() << "\n";
                    }
                }
            }
            std::cout << "> Output: Graph has been built successfully.\n";
        } 
        else if (choice == 2) {
            this->_graph->BFS();
        } 
        else if (choice == 3) {
            this->_graph->DFS();
        } 
        else if (choice == 4) {
            this->_graph->Kruskal();
        }
        else if (choice == 5) {
            this->_graph->Prim();
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