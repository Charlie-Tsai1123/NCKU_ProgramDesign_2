CC = g++

all: hw3
hw3: main.cpp check.o
	$(CC) -o hw3 main.cpp check.o
check.o: check.cpp
	$(CC) -c check.cpp

clear:
	rm *.o hw3