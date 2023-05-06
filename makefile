CC = g++

all: hw5
hw5: main.cpp printSet.o
	$(CC) -o hw5 main.cpp printSet.o
printSet.o: printSet.cpp
	$(CC) -c printSet.cpp

clear: 
	rm *.o hw5