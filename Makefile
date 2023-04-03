CC = g++

all: test

test: test_graph_example.o
	g++ test_graph_example.o -o test

test_graph_example.o: test_graph_example.cpp
	g++ -c test_graph_example.cpp

clean:
	rm *.o test