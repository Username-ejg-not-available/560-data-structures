#ifndef EXEC_H
#define EXEC_H

#include <string>
#include "BST.h"

class Exec {
private:
	/**
     * @post prompts user for choices and executes said choices
     */
	void menu();

    BST<int>* _tree;
public:
	/**
	 * @param filename input file
	 * @post inserts items into tree and calls menu
	 */
	Exec(std::string filename);
	/**
	 * @post deletes tree
	 */
	~Exec();
};
#endif