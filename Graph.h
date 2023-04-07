#ifndef UNIT3_GRAPH_H
#define UNIT3_GRAPH_H

#include <vector>
#include <sstream>
#include <map>

using namespace std;

enum Color {
    WHITE = 0, GRAY = 1, BLACK = 2
};

template<class D, class K>
class Vertex {
public:
    K key;
    D data;
    int distance = 0;
    int discovery = 0;
    int finish = 0;
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
    map<K, K> preds;
    int dfsTime = 0;

    void setPredecessor(K k, K pred) {
        preds[k] = pred;
    }

    K getPredecessor(K k) {
        return preds[k];
    }

    Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges);

    Vertex<D, K> *get(K key);

    bool reachable(K start, K end);

    void bfs(K s);

    void print_path(K start, K end);

    string edge_class(K u, K v);

    void bfs_tree(K start);

    void dfs(K u, K v);

    void dfs_visit(const K& key, K u, K v);
};


#endif
