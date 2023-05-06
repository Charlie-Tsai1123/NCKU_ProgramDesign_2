CC = g++

all: hw4
hw4: main.cpp check.o
	$(CC) -o hw4 main.cpp check.o
check.o: check.cpp
	$(CC) -c check.cpp

clear:
	rm *.o hw4
