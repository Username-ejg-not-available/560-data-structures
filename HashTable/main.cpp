/**
* @author Ethan Grantz
* @file main.cpp
* @date 2/8/2021
* @brief creates instance of Exec
*/
#include "Exec.h"

int main(int argc, char** argv) {
    Exec* e = new Exec((argc > 1) ? argv[1] : "data.txt");
    delete e;
}