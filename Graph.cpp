#include <queue>
#include "Graph.h"

template<class D, class K>
Graph<D, K>::Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges) { // List in List for the adjs/edges
    // Check PDF for new version
    /*
     * vector<string> keys ={"R", "V", "S", "T", "U", "Y", "W", "X"}; // 3
     * vector<int> data ={1, 2, 3, 5, 4, 6, 7, 8};
     * vector<vector<string>> edges ={{"V"},{"S"},{"R"},{"S","U","W"},{"Y"},{"W"},{"X"},{"U"}} // suw
     */
    for (int i = 0; i < keys.size(); i++) {
        vertexes.push_back(Vertex(keys[i], data[i], edges[i]));
    }
}

template<class D, class K>
Vertex<D, K> *Graph<D, K>::get(K key) {
    for (int i = 0; i < vertexes.size(); i++) {
        Vertex<D, K> vertex = vertexes[i];
        if (vertex.key == key) {
            return &vertexes[i];
        }
    }
    return nullptr;
}

template<class D, class K>
bool Graph<D, K>::reachable(K start, K end) {

    return false;
}

template<class D, class K>
void Graph<D, K>::bfs(K s) {
    for (Vertex<D, K> vertex: vertexes) {
        vertex.color = WHITE;
        vertex.distance = 0;
        vertex.predecessor = nullptr;
    }
    Vertex<D, K> *startVertex = get(s);
    startVertex->color = GRAY;
    startVertex->distance = 0;
    startVertex->predecessor = nullptr;
    std::queue<Vertex<D, K>> q;
    q.push(*startVertex);
    while (!q.empty()) {
        Vertex<D, K> u = q.front();
        q.pop();
        for (K v: u.adjs) {
            Vertex<D, K> *vItem = get(v);
            if (vItem->color == WHITE) {
                vItem->color = GRAY;
                vItem->distance = u.distance + 1;
                vItem->predecessor = &(u.key);
                q.push(*vItem);
            }
        }
        u.color=BLACK;
    }
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

