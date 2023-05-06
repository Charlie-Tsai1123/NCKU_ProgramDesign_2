CC = g++

all: hw5
hw5: main.cpp printSet.o insertCorpus.o
	$(CC) -o hw5 main.cpp printSet.o insertCorpus.o
printSet.o: printSet.cpp
	$(CC) -c printSet.cpp
insertCorpus.o: insertCorpus.cpp
	$(CC) -c insertCorpus.cpp

clear: 
	rm *.o hw5