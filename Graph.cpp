#include "Graph.h"

template<class D, class K>
Graph<D, K>::Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges) { // List in List for the adjs/edges
    // Check PDF for new version
    /*
     * vector<string> keys ={"R", "V", "S", "T", "U", "Y", "W", "X"};
     * vector<int> data ={1, 2, 3, 5, 4, 6, 7, 8};
     * vector<vector<string>> edges ={{"V"},{"S"},{"R"},{"S","U","W"},{"Y"},{"W"},{"X"},{"U"}}
     */
//    this->keys = keys;
//    this->data = data;
//    this->adjs = edges;

    //cout << "addinf vert start " << keys.size() << endl;
    for (int i = 0; i < keys.size(); i++) {
        //cout << "addinf vert " << keys[i] << endl;
        vertexes.push_back(Vertex(keys[i], data[i], edges[i]));
    }
}

template<class D, class K>
Vertex<D,K> *Graph<D, K>::get(K key) {
    for (int i = 0; i < vertexes.size(); i++) {
        Vertex<D,K> vertex = vertexes[i];
        if (vertex.key == key) {
            cout <<"ret " << vertex.key << endl;
            return &vertex;
        }
    }
    return nullptr;
}

template<class D, class K>
bool Graph<D, K>::reachable(D data, K key) {
    return false;
}

template<class D, class K>
void Graph<D, K>::bfs(K s) {

}

template<class D, class K>
void Graph<D, K>::print_path(K start, K end) {

}

template<class D, class K>
string Graph<D, K>::edge_class(K u, K v) {
    return std::string();
}

template<class D, class K>
void Graph<D, K>::bfs_tree(K start) {

}

