main: main.o Exec.o hashtable.o useful.o
	g++ -std=c++11 -Wall main.o Exec.o hashtable.o useful.o -o main

main.o: main.cpp
	g++ -g -std=c++11 -Wall -c main.cpp

Exec.o: Exec.cpp
	g++ -g -std=c++11 -Wall -c Exec.cpp

hashtable.o: hashtable.cpp
	g++ -g -std=c++11 -Wall -c hashtable.cpp

useful.o: useful.cpp
	g++ -g -std=c++11 -Wall -c useful.cpp

clean:
	rm *.o main