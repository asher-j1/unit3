//
// Created by fired on 3/30/2023.
//

#ifndef UNIT3_GRAPH_H
#define UNIT3_GRAPH_H

#include <vector>
#include <sstream>

using namespace std;

template<class D, class K>
class Vertex {
public:
    K key;
    D data;
    int distance;
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

    vector<K> keys;
    vector<D> data;
    vector<vector<K>> adjs;
    vector<Vertex<D, K>> vertexes = {};

    Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges);

    Vertex<D, K> *get(K key);

    bool reachable(D data, K key);

    void bfs(K s);

    void print_path(K start, K end);

    string edge_class(K u, K v);

    void bfs_tree(K start);
};


#endif //UNIT3_GRAPH_H
