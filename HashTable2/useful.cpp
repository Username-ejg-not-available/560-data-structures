#include "useful.h"
#include <cmath>
#include <limits>
bool isPrime(int num) {
    for (int i = 2; i < sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
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
