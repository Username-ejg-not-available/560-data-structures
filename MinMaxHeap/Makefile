main: main.o Exec.o
	g++ -std=c++11 -Wall main.o Exec.o -o main

main.o: main.cpp MinMaxHeap.h MinMaxHeap.cpp
	g++ -g -std=c++11 -Wall -c main.cpp

Exec.o: Exec.cpp
	g++ -g -std=c++11 -Wall -c Exec.cpp

clean:
	rm *.o main