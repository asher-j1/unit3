#include <queue>
#include <algorithm>
#include "graph.h"

template<class D, class K>
Graph<D, K>::Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges) {

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
bool Graph<D, K>::reachable(K start, K end) { // Literally just a skimmed down version of print_path funny enough
    if (get(start) == nullptr || get(end) == nullptr) {
        return false;
    }
    Vertex<D,K> *pred = get(end);
    while (get(getPredecessor(pred->key)) != nullptr) {
        if (start == pred->key) {
            break;
        }
        pred = get(getPredecessor(pred->key));
    }
    return true;
}


template<class D, class K>
void Graph<D, K>::bfs(K s) {
    for (Vertex<D, K> vertex: vertexes) {
        if (vertex.key != s) {
            vertex.color = WHITE;
            vertex.distance = 2000000; // Functionally INF.
        }
    }
    Vertex<D, K> *startVertex = get(s);
    if (startVertex == nullptr) {
        return;
    }
    startVertex->color = GRAY;
    startVertex->distance = 0;
    setPredecessor(startVertex->key, startVertex->key);
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
                q.push_back(*vItem);
            }
        }
        u.color = BLACK;
    }
}

template<class D, class K>
void Graph<D, K>::print_path(K u, K v) {
    if (get(u) == nullptr || get(v) == nullptr) {
        cout << "No Path";
        return;
    }

    Vertex<D,K> *pred = get(v);
    string res;
    while (get(getPredecessor(pred->key)) != nullptr) {
        if (u == pred->key) {
            res.append(pred->key);
            break;
        }
        res.append(pred->key);
        res.append(" >- "); // Yes this is on purpose, do not change.
        pred = get(getPredecessor(pred->key));
    }
    reverse(res.begin(), res.end());
    cout << res;
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

