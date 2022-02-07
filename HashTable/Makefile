main: main.o Exec.o HashTable.o
	g++ -std=c++11 -Wall main.o Exec.o HashTable.o -o main

main.o: main.cpp Node.h Node.cpp LinkedList.h LinkedList.cpp
	g++ -g -std=c++11 -Wall -c main.cpp

Exec.o: Exec.cpp
	g++ -g -std=c++11 -Wall -c Exec.cpp

HashTable.o: HashTable.cpp
	g++ -g -std=c++11 -Wall -c HashTable.cpp

clean:
	rm *.o main