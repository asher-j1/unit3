#include <queue>
#include "Graph.h"

template<class D, class K>
Graph<D, K>::Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges) {
    /*
     * vector<string> keys ={"R", "V", "S", "T", "U", "Y", "W", "X"}; // 3
     * vector<int> data ={1, 2, 3, 5, 4, 6, 7, 8};
     * vector<vector<string>> edges ={{"V"},{"S"},{"R"},{"S","U","W"},{"Y"},{"W"},{"X"},{"U"}} // suw
     */
    for (int i = 0; i < keys.size(); i++) {
        vertexes.push_back(Vertex<D,K>(keys[i], data[i], edges[i]));
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

//template<class D, class K>
//bool Graph<D, K>::reachable(K start, K end) {
//    bool result = false;
//    Vertex<D,K> startVertex = *get(start);
//    for (K key : startVertex.adjs) {
//        if (key == end) {
//            return true;
//        }
//        return reachable(key, end);
//    }
//    //return result;
//}


template<class D, class K>
bool Graph<D, K>::reachable(K start, K end) {
    bool result = false;
    Vertex<D,K> startVertex = *get(start);
    for (K key : startVertex.adjs) {
        if (key == end) {
            return true;
        } else {
            result = reachable(key, end);
            if (result == true) {
                return true;
            }
        }
    }
    return result;
}


template<class D, class K>
void Graph<D, K>::bfs(K s) {
    for (Vertex<D, K> vertex: vertexes) {
        vertex.color = WHITE;
        vertex.distance = 0;
        vertex.predecessor = nullptr;
    }
    Vertex<D, K> *startVertex = get(s);
    if (startVertex == nullptr) {
        return;
    }
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
        u.color = BLACK;
    }
}

template<class D, class K>
void Graph<D, K>::print_path(K u, K v) { // Dijkstra? 24.3 658
    if v==u:
        print("no path exists")
    elif v.predecessor == NULL:
        print("No path exists")
    else:
        print_path(u, v)
        print(v)
}

template<class D, class K>
string Graph<D, K>::edge_class(K u, K v) {

    // Page 609 in book, maybe impl. DFS (or was it BFS) for easier edges?
    Vertex<D,K> vertex = *get(v);
    if (vertex.color == WHITE) {
        return "tree edge";
    } else if (vertex.color == GRAY) {
        return "back edge";
    } else {
        return "??";
    }
    return "NYI"; // TODO This isn't actually implemented yet
}

template<class D, class K>
void Graph<D, K>::bfs_tree(K start) {
    int maxDistance = 0;
    for (Vertex<D, K> vertex: vertexes) {
        if (maxDistance < vertex.distance) {
            maxDistance = vertex.distance; // Get max distance
        }
    }
    stringstream ss;
    for (int i = 0; i <= maxDistance; i++) {
        for (Vertex<D, K> vertex: vertexes) {
            if (vertex.distance == i) {
                ss << vertex.key << " ";
            }
        }
        if (i < maxDistance) {
            ss.seekp(-1, ss.cur);
            ss << "\n";
        }
    }
    string str = ss.str();
    str.erase(str.length() - 1, 1);
    cout << str;
}

