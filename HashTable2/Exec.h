#ifndef EXEC_H
#define EXEC_H

#include <string>
#include "hashtable.h"

class Exec {
private:
	/**
     * @post prompts user for choices and executes said choices
     */
	void menu();

	HashTable* _quadTable, * _doubTable;
public:
	/**
	 * @param filename input file
	 * @post reads in file and inserts values into lists; calls menu()
	 */
	Exec(std::string filename);
	/**
	 * @post deletes _quadTable and _doubTable
	 */
	~Exec();

	/**
	 * @post rehashes both tables to prime number >= 2 * current bucketsize
	 */
	void rehash(TableType table);
};
#endif