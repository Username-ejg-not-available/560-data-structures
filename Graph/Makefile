main: main.o Exec.o Graph.o
	g++ -std=c++11 -Wall main.o Exec.o Graph.o -o main

main.o: main.cpp DisjointSet.h DisjointSet.cpp Node.h Node.cpp Heap.h MinHeap.h MinHeap.cpp
	g++ -g -std=c++11 -Wall -c main.cpp

Exec.o: Exec.cpp
	g++ -g -std=c++11 -Wall -c Exec.cpp

Graph.o: Graph.cpp
	g++ -g -std=c++11 -Wall -c Graph.cpp

clean:
	rm *.o main