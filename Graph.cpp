#include <queue>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include "graph.h"

template<class D, class K>
Graph<D, K>::Graph(vector<K> keys, vector<D> data, vector<vector<K>> edges) {
    for (int i = 0; i < keys.size(); i++) {
        vertexes.push_back(Vertex<D, K>(keys[i], data[i], edges[i])); // All of our vertex data is stored as Vertex objects, so init with the key, the data and edges.
    }
}

/**
 * Gets the pointer of a Vertex Object based on the given key
 * Pre: None
 * Post: A pointer is returned
 * @param key The key that corresponds to the Vertex we want
 * @return The pointer of the Vertex object (or nullptr if not found)
 */
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

/**
 * From a given start key is the goal key reachable
 * Pre: In normal operation, both the start and end vertex should exist as well as predecessor data
 * Post: Nothing changes in the graph
 * @param start Starting point
 * @param end End point
 * @return True if possible, False if not
 */
template<class D, class K>
bool Graph<D, K>::reachable(K start, K end) { // Literally just a skimmed down version of print_path funny enough
    if (get(start) == nullptr || get(end) == nullptr) { // Quick exit if the start or end vertex don't exist
        return false;
    }
    Vertex<D, K> *pred = get(end);
    while (get(getPredecessor(pred->key)) != nullptr) { // Get the predecessor, make sure it isn't null
        if (start == pred->key) {
            break; // If pred is same as start key, then we've made it back to the beginning. Meaning we can reach it and can leave this loop to return true.
        }
        pred = get(getPredecessor(pred->key));
    }
    return true;
}

/**
 * Runs a breadth-first-search
 * Pre: A valid graph has been constructed
 * Post: All nodes in the graph have been marked with distance, color and their predecessor
 * @param s Starting key
 */
template<class D, class K>
void Graph<D, K>::bfs(K s) {

    // Reset everything apart from the starting vertex
    for (int i = 0; i < vertexes.size(); i++) {
        vertexes[i].color = WHITE;
        vertexes[i].distance = INT_MAX; // Functionally INF.
    }
    Vertex<D, K> *startVertex = get(s);
    if (startVertex == nullptr) { // Call it quits if start is null
        return;
    }
    startVertex->color = GRAY;
    startVertex->distance = 0;
    setPredecessor(startVertex->key, startVertex->key);
    std::deque<Vertex<D, K>> q; // Queue for FIFO starts with the vertex corresponding to Key S
    q.push_back(*startVertex);
    while (!q.empty()) {
        Vertex<D, K> u = q.front();
        q.pop_front(); // Grab the front and remove it
        for (K v: u.adjs) {
            Vertex<D, K> *vItem = get(v);
            if (vItem->color == WHITE) { // For all of adjacent vertexes of u, if they are undiscovered/white
                // Mark them as GRAY/Discovered, set distance and predecessor, and finally put it on the queue
                vItem->color = GRAY;
                vItem->distance = u.distance + 1;
                setPredecessor(vItem->key, u.key);
                q.push_back(*vItem);
            }
        }
        u.color = BLACK; // Of course this isn't actually needed, but why not just keep it anyway?
    }
}

/**
 * Prints the path of the starting vertex (u) to the end vertex (v)
 * Pre: That both vertexes exist in the graph
 * Post: BFS is run on the graph, but this should be of no consequence in this case
 * @param u Start Vertex Key
 * @param v End Vertex Key
 */
template<class D, class K>
void Graph<D, K>::print_path(K u, K v) {

    unordered_map<K, int> dist;
    unordered_map<K, K> parent;

    for (auto &vtx: vertexes) {
        dist[vtx.key] = INT_MAX;
        parent[vtx.key] = "";
    }

    dist[u] = 0;

    // create queue for BFS algorithm
    queue<K> q;
    q.push(u);

    while (!q.empty()) {
        K curr = q.front();
        q.pop();

        // stop if we reach the destination vertex
        if (curr == v) {
            break;
        }

        // traverse edges incident to current vertex
        for (K adj: get(curr)->adjs) {
            if (dist[adj] == INT_MAX) {
                dist[adj] = dist[curr] + 1;
                parent[adj] = curr;
                q.push(adj);
            }
        }
    }

    vector<K> path;
    K curr = v;
    while (curr != u) {
        path.push_back(curr);
        curr = parent[curr];
    }
    path.push_back(u);

    stringstream ss;
    for (int i = path.size() - 1; i >= 0; i--) {
        ss << path[i];
        if (i != 0) {
            ss << " -> ";
        }
    }
    string str = ss.str();
    cout << str;
}

/**
 * The first part to a DFS algorithm tailored for use in edge_class
 * Pre: dfsTime equals 0
 * Post: dfsTime != 0, and the DFS is completed
 * @param u The starting key of the edge to classify
 * @param v The ending key of the edge to classify
 */
template<class D, class K>
void Graph<D, K>::dfs(K u, K v) {
    // Reset
    // Only color, nothing else
    for (int i = 0; i < vertexes.size(); i++) {
        vertexes[i].color = WHITE;
    }
    for (int i = 0; i < vertexes.size(); i++) {
        if (vertexes[i].color == WHITE) {
            dfs_visit(vertexes[i].key, u, v); // For each vertex that is undiscovered, start visiting them
        }
    }
}

/**
 * Second part of DFS, tailored for edge_class
 * Visits each vertex and their adjacent vertex's
 * Also determines what edge class we have
 *
 * Pre: key corresponds to a valid vertex
 * Post: key and its adj. nodes are visited while the edge class is determined
 *
 * @param key Key we're checking, used for recursion
 * @param u Starting key of the edge we're classifying
 * @param v End key of the edge we're classifying
 */
template<class D, class K>
void Graph<D, K>::dfs_visit(const K &key, K u, K v) {
    // Start by setting u as discovered and its discovery time
    Vertex<D, K> *uVert = get(key);
    uVert->color = GRAY;
    uVert->discovery = dfsTime;
    dfsTime += 1;
    for (K adjKey: uVert->adjs) {
        Vertex<D, K> *vVert = get(adjKey);
        if (vVert->color == WHITE) {
            dfs_visit(vVert->key, u, v);
            if (uVert->key == u && vVert->key == v) { // If we are checking the start and end vertex of the edge we want, then we can say its a tree edge, otherwise continue normally
                cout << "tree edge";
            }
        } else {
            if (uVert->key == u && vVert->key == v) { // Determines the edge_class if we are checking the right start and end
                if (uVert->discovery > vVert->discovery && uVert->finish > vVert->finish) { // If the start and end vertex times check out, then print the right edge
                    cout << "cross edge";
                } else if (uVert->discovery < vVert->discovery && uVert->finish > vVert->finish) {
                    cout << "forward edge";
                } else if (uVert->discovery > vVert->discovery && uVert->finish < vVert->finish) {
                    cout << "back edge";
                }
            }
        }
        uVert->finish = dfsTime; // Update finishcfg and increment dfs time
        dfsTime++;
    }
}

/**
 * Uses a modified DFS algorithm to determine what type of edge (u,v) is
 *
 * Pre: Both u and v correspond to a valid vertex
 * Post: DFS is completed on the graph
 * @param u Starting key for edge
 * @param v End key for edge
 * @return What type of edge (u,v) is, or no edge if not one
 */
template<class D, class K>
string Graph<D, K>::edge_class(K u, K v) {
    dfsTime = 0; // Very important: Resets DFS time variable
    stringstream buffer;
    streambuf *prevbuf = cout.rdbuf(buffer.rdbuf()); // Just like how the test_graph_example checks the buffer, this does the same to grab the edge class
    dfs(u, v); // Runs the DFS, the most important part
    cout.rdbuf(prevbuf);
    if (buffer.str().empty()) { // If we didn't get an edge from the dfs sorting then its no edge.
        return "no edge";
    }
    return buffer.str();
}

/**
 * Prints out a tree representing the BFS'd grpah
 * Pre: That start corresponds to a valid vertex
 * Post: A BFS is run on the graph
 * @param start The key to the source vertex
 */
template<class D, class K>
void Graph<D, K>::bfs_tree(K start) {
    bfs(start); // Rerun BFS based on the given source node
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
                ss << vertex.key << " "; // For each vertex <= i, print out its key
            }
        }
        if (i < maxDistance) { // When all are done for i, add new line and repeat
            ss.seekp(-1, stringstream::cur);
            ss << "\n";
        }
    }
    string str = ss.str();
    str.erase(str.length() - 1, 1); // Get rid of the last character because of potential space or extra new line, ensures it matches with test cases
    cout << str;
}

