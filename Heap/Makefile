main: main.o Exec.o
	g++ -std=c++11 -Wall main.o Exec.o -o main

main.o: main.cpp MinThreap.h MinThreap.cpp MaxThreap.h MaxThreap.cpp Threap.h
	g++ -g -std=c++11 -Wall -c main.cpp

Exec.o: Exec.cpp
	g++ -g -std=c++11 -Wall -c Exec.cpp

clean:
	rm *.o main