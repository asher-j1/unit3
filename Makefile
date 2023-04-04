CC = g++

all: test

test: test_graph_example.o
	g++ -std=c++11 test_graph_example.o -o test

test_graph_example.o: test_graph_example.cpp
	g++ -std=c++11 -c test_graph_example.cpp

clean:
	rm *.o test