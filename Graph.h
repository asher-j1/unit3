#ifndef UNIT3_GRAPH_H
#define UNIT3_GRAPH_H

#include <vector>
#include <sstream>

using namespace std;

enum Color {
    WHITE, BLACK, GRAY
};

template<class D, class K>
class Vertex {
public:
    K key;
    D data;
    int distance = 0;
    K *predecessor = nullptr;
    Color color = WHITE;
    vector<K> adjs;

    Vertex(K key, D data, vector<K> edges);
};

template<class D, class K>
Vertex<D, K>::Vertex(K key, D data, vector<K> edges) {
    this->key = key;
    this->data = data;
    adjs = edges;
}

template<class D, class K> // Data = Vertex Data, K = Vertex Key
class Graph {
public:
    vector<Vertex<D, K>> vertexes = {};

    Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges);

    Vertex<D, K> *get(K key);

    bool reachable(K start, K end);

    void bfs(K s);

    void print_path(K start, K end);

    string edge_class(K u, K v);

    void bfs_tree(K start);
};


#endif //UNIT3_GRAPH_H
