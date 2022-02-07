/**
* @author Ethan Grantz
* @file Exec.h
* @date 2/8/2021
* @brief declares the functions that the Exec class needs to work
*/
#ifndef EXEC_H
#define EXEC_H

#include "HashTable.h"

class Exec {
private:
    HashTable* _hashTable;

    /**
     * @post prompts user for choices and executes said choices
     */
    void menu();

    /**
     * @param out variable that input is assigned to
     * @post prompts user for input until they put in an int
     */
    void inInt(int& out);
public:
    /**
     * @param filename file input
     * @post reads in file input and calls menu()
     */
    Exec(std::string filename);

    /**
     * @post deletes _hashTable
     */
    ~Exec();

    /**
     * @post prints contents of _hashTable
     */
    void printStudentList() const;

    /**
     * @param str string containing characters
     * @return true if all characters are numeric, false otherwise
     */
    bool isnum(std::string str) const;

    /**
     * @param str is a string
     * @return true if string contains only lowercase letters, false otherwise
     */
    bool islower(std::string str) const;
};
#endif