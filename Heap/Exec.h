#ifndef EXEC_H
#define EXEC_H

#include <string>
#include "MinThreap.h"
#include "MaxThreap.h"

struct Restaurant {
    std::string Name;
    double Dist;
    int Reviews;
    Restaurant() : Name(""), Dist(0), Reviews(0) {}
    Restaurant(std::string name, double dist, int reviews) {
        Name = name;
        Dist = dist;
        Reviews = reviews;
    }
    bool operator==(Restaurant& other) {
        return Name == other.Name;
    }
    bool operator<(Restaurant& other) {//for minheap
        return Dist < other.Dist;
    }
    bool operator>(Restaurant& other) {//for maxheap
        return Reviews > other.Reviews;
    }
    bool operator<=(Restaurant& other) {//for minheap
        return Dist <= other.Dist;
    }
    bool operator>=(Restaurant& other) {//for maxheap
        return Reviews >= other.Reviews; 
    }
    friend std::ostream& operator<<(std::ostream& output, const Restaurant& rest) {
        output << rest.Name;
        return output;
    }
};

class Exec {
private:
	/**
     * @post prompts user for choices and executes said choices
     */
	void menu();

    MinThreap<Restaurant>* _minThreap;
    MaxThreap<Restaurant>* _maxThreap;
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