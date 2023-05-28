CC = g++

all: hw6
hw6: main.cpp insertCorpus.o 
	$(CC) -o hw6 main.cpp insertCorpus.o
insertCorpus.o: insertCorpus.cpp
	$(CC) -c insertCorpus.cpp

clear: 
	rm *.o hw6
