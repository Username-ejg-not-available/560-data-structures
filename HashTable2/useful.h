#ifndef USEFUL_H
#define USEFUL_H
#include <iostream>
/**
 * @param num number to determine its primeness
 * @return true if num is prime, false otherwise
 */
bool isPrime(int num);
/**
 * @param out variable that input is assigned to
 * @post prompts user for input until they put in an int
 */
void inInt(int& out);
#endif