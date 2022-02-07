main: main.o Exec.o ExProf.o
	g++ -std=c++11 -Wall main.o Exec.o ExProf.o -o main

main.o: main.cpp BNode.h BNode.cpp BST.h BST.cpp
	g++ -g -std=c++11 -Wall -c main.cpp

Exec.o: Exec.cpp
	g++ -g -std=c++11 -Wall -c Exec.cpp

ExProf.o: ExProf.cpp
	g++ -g -std=c++11 -Wall -c ExProf.cpp

clean:
	rm *.o main