CC = g++

all: hw7
hw7: main.cpp insertCorpus.o 
	$(CC) -o hw7 main.cpp insertCorpus.o
insertCorpus.o: insertCorpus.cpp
	$(CC) -c insertCorpus.cpp

clear: 
	rm *.o hw7
