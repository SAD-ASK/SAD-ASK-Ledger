CC = gcc
CFLAGS = -c -Wall

CXX = g++
CXXFLAGS = -std=c++11
all: ledger

ledger: ledger.o sqlite3.o
	g++ -std=c++11 ledger.o sqlite3.o -o ledger

ledger.o: ledger.cpp ledger.h
	g++ -std=c++11 -c ledger.cpp ledger.h

sqlite3.o:
	gcc -c sqlite3.c

clean: rm *.o ledger
