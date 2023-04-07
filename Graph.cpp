#include <queue>
#include <algorithm>
#include <unordered_map>
#include <sstream>
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
    Vertex<D, K> *pred = get(end);
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
    
    unordered_map<K, int> dist;
    unordered_map<K, K> parent;

    for (auto &vtx : vertexes)
    {
        dist[vtx.key] = INT_MAX;
        parent[vtx.key] = "";
    }

    dist[u] = 0;

    // create queue for BFS algorithm
    queue<K> q;
    q.push(u);

    while (!q.empty())
    {
        K curr = q.front();
        q.pop();

        // stop if we reach the destination vertex
        if (curr == v)
        {
            break;
        }

        // traverse edges incident to current vertex
        for (K adj : get(curr)->adjs)
        {
            if (dist[adj] == INT_MAX)
            {
                dist[adj] = dist[curr] + 1;
                parent[adj] = curr;
                q.push(adj);
            }
        }
    }

    vector<K> path;
    K curr = v;
    while (curr != u)
    {
        path.push_back(curr);
        curr = parent[curr];
    }
    path.push_back(u);

    stringstream ss;
    for (int i = path.size() - 1; i >= 0; i--)
    {
        ss << path[i];
        if (i != 0)
        {
            ss << " -> ";
        }
    }
    string str = ss.str();
    cout << str;
}

template<class D, class K>
void Graph<D, K>::dfs(K u, K v) {
    // Reset
    for (int i = 0; i < vertexes.size(); i++) {
        vertexes[i].color = WHITE;
        //vertexes[i].discovery = 0;
        //vertexes[i].finish = 0;
    }
    for (int i = 0; i < vertexes.size(); i++) {
        if (vertexes[i].color == WHITE) {
            dfs_visit(vertexes[i].key, u, v);
        }
    }
}

template<class D, class K>
void Graph<D, K>::dfs_visit(const K &key, K u, K v) {
    Vertex<D, K> *uVert = get(key);
    uVert->color = GRAY;
    uVert->discovery = dfsTime;
    dfsTime += 1;
    for (K adjKey: uVert->adjs) {
        Vertex<D, K> *vVert = get(adjKey);
        if (vVert->color == WHITE) {
            dfs_visit(vVert->key, u, v);
            if (uVert->key == u && vVert->key == v) {
                cout << "tree edge";
                //return;
            }
        } else {
            if (uVert->key == u && vVert->key == v) {
                if (uVert->discovery > vVert->discovery && uVert->finish > vVert->finish) {
                    cout << "cross edge";
                    //return;
                } else if (uVert->discovery < vVert->discovery && uVert->finish > vVert->finish) {
                    cout << "forward edge";
                    //return;
                } else if (uVert->discovery > vVert->discovery && uVert->finish < vVert->finish) {
                    cout << "back edge";
                    //return;
                }
            }
        }
        uVert->finish = dfsTime;
        dfsTime++;
    }
}

template<class D, class K>
string Graph<D, K>::edge_class(K u, K v) {
    stringstream buffer;
    streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
    dfs(u, v);
    cout.rdbuf(prevbuf);
    if (buffer.str().empty()) {
        return "no edge";
    }
    return buffer.str();
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

