#ifndef EXEC_H
#define EXEC_H

#include <string>
#include "Graph.h"

class Exec {
private:
	/**
     * @post prompts user for choices and executes said choices
     */
	void menu(std::string filename);

    Graph* _graph;
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