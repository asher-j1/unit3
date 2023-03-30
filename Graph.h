//
// Created by fired on 3/30/2023.
//

#ifndef UNIT3_GRAPH_H
#define UNIT3_GRAPH_H

#include <vector>
#include <sstream>

using namespace std;

template<class D, class K> // Data = Vertex Data, K = Vertex Key
class Graph {

public:
    Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges);

    D* get(K key);

    bool reachable(D data, K key);

    void bfs(K s);

    void print_path(K start, K end);

    string edge_class(K u, K v);

    void bfs_tree(K start);
};


#endif //UNIT3_GRAPH_H
