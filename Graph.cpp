#include <queue>
#include "Graph.h"

template<class D, class K>
Graph<D, K>::Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges) {

//     vector<string> keys ={"R", "V", "S", "T", "U", "Y", "W", "X"}; // 3
//     vector<int> data ={1, 2, 3, 5, 4, 6, 7, 8};
//     vector<vector<string>> edges ={{"V"},{"S"},{"R"},{"S","U","W"},{"Y"},{"W"},{"X"},{"U"}} // suw

    for (int i = 0; i < keys.size(); i++) {
        vertexes.push_back(Vertex<D, K>(keys[i], data[i], edges[i]));
    }

//    // Add edges
//    for (int i = 0; i < keys.size(); i++) {
//        Vertex<D, K>* uVertex = get(keys[i]);
//        vector<K> adjKeys = edges[i];
//        for (K adjKey : adjKeys) {
//            Vertex<D, K>* vVertex = get(adjKey);
//            uVertex->adjs.push_back(adjKey);
//        }
//    }
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
    bool result = false;
//    Vertex<D,K> startVertex = *get(start);
//    for (K key : startVertex.adjs) {
//        if (key == end) {
//            return true;
//        } else {
//            result = reachable(key, end);
//            if (result == true) {
//                return true;
//            }
//        }
//    }
    return result;
}


template<class D, class K>
void Graph<D, K>::bfs(K s) {
    for (Vertex<D, K> vertex: vertexes) {
        if (vertex.key != s) {
            vertex.color = WHITE;
            vertex.distance = 2000000; // Functionally INF.
            //setPredecessor(vertex.key, nullptr);
        }
    }
    Vertex<D, K> *startVertex = get(s);
    if (startVertex == nullptr) {
        return;
    }
    startVertex->color = GRAY;
    startVertex->distance = 0;
    std::deque<Vertex<D, K>> q;
    q.push_back(*startVertex);
    while (!q.empty()) {
        Vertex<D, K> u = q.front();
        q.pop_front();
        for (K v: u.adjs) {
            Vertex<D, K> *vItem = get(v);
            if (vItem->color == WHITE) {
                vItem->color = GRAY;
                vItem->distance = u.distance + 1;
                setPredecessor(vItem->key, u.key);
                //vItem->predecessor = &(u.key);
                cout << "Key: " << vItem->key << " Pred Key: " << get((getPredecessor(vItem->key)))->key << endl;
                q.push_back(*vItem);
            }
        }
        u.color = BLACK;
    }
//    cout << "After" << endl;
//    for (Vertex<D, K> vertex: vertexes) {
//        //if (&getPredecessor(vertex.key) != nullptr) {
//            cout << "Key: " << vertex.key << " Pred Key: " << getPredecessor(vertex.key) << endl;
//        //}
//    }
}

template<class D, class K>
void Graph<D, K>::print_path(K u, K v) { // Dijkstra? 24.3 658
    // Graph? Dijkstra.


//    if (get(u) == nullptr || get(v) == nullptr) {
//        cout << "No Path";
//        return;
//    }
//
//    Vertex<D,K> *pred = get(v);
//    string res = "";
//    while (get(*(pred->predecessor)) != nullptr) {
//        res.append(pred->key);
//        res.append(" <- ");
//        string str = "Key: ";
//        str.append(pred->key) ;
//        str.append(" Pred Key: ");
//        str.append(get(*(pred->predecessor))->key);
//        pred = get(*(pred->predecessor));
//    }
//    cout << res << endl;


}

template<class D, class K>
string Graph<D, K>::edge_class(K u, K v) {
//    Vertex<D, K>* uVertex = get(u);
//    Vertex<D, K>* vVertex = get(v);
//
//    if (uVertex->color == WHITE) {
//        // u is an unexplored vertex
//        return "tree";
//    } else if (vVertex->color == GRAY) {
//        // v is a descendant of u in the BFS tree
//        return "cross";
//    } else {
//        // v is either an ancestor or a non-descendant of u
//        // (assuming the graph is undirected)
//        if (uVertex->distance < vVertex->distance) {
//            // v is an ancestor of u
//            return "forward";
//        } else {
//            // v is a non-descendant of u
//            return "back";
//        }
//    }
    return "NYI";
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
            ss.seekp(-1, stringstream::cur);
            ss << "\n";
        }
    }
    string str = ss.str();
    str.erase(str.length() - 1, 1);
    cout << str;
}

