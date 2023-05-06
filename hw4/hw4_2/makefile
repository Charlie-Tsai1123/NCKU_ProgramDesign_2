CC = g++

all: hw4
hw4: main.cpp check.o checkContinue.o
	$(CC) -o hw4 main.cpp check.o checkContinue.o
check.o: check.cpp
	$(CC) -c check.cpp
checkContinue.o: checkContinue.cpp
	$(CC) -c checkContinue.cpp

clear:
	rm *.o hw4