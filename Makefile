# Created by: Syed Safdar Ali Shah

# Make file to compile and produce binary output for area Homework

#Variables
CC=g++
CFLAGS = -c -Wall -std=c++11

all: assignment

assignment: area.o
	$(CC) area.o -o area

area.o: area.cpp
	$(CC) $(CFLAGS) area.cpp

clean:
	rm -rf *o area
