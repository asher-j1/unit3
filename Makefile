CC = g++

all: test

test: test_graph.o
	g++ -std=c++11 test_graph.o -o test

test_graph.o: test_graph.cpp
	g++ -std=c++11 -c test_graph.cpp

clean:
	rm *.o test 
