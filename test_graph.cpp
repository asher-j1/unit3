#include <fstream>
#include <sstream>
#include "iostream"
#include <vector>
#include "graph.cpp"

using namespace std;

Graph<string, string> *generate_graph(string fname)
{
    string line;
    ifstream infile(fname);
    vector<string> keys = {};
    vector<string> data = {};
    vector<vector<string>> adjs = {};
    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            unsigned long delim = line.find(":");
            string key = line.substr(0, delim);
            string adj = line.substr(delim + 1);

            keys.push_back(key);
            data.push_back(key + " data");
            delim = adj.find(",");
            vector<string> adj_lst = {};
            while (delim < adj.length())
            {
                adj_lst.push_back(adj.substr(0, delim));
                adj = adj.substr(delim + 1);
                delim = adj.find(",");
            }
            adj_lst.push_back(adj);
            adjs.push_back(adj_lst);
        }
    }
    Graph<string, string> *G = new Graph<string, string>(keys, data, adjs);
    return G;
}

void test_get(Graph<string, string> *G)
{
    try
    {
        if (G->get("S") == nullptr || G->get("S")->data != "S data")
        {
            cout << "Incorrect result getting vertex \"s\"" << endl;
        }
        if (G->get("a") != nullptr)
        {
            cout << "Incorrect result getting non-existant vertex \"a\"" << endl;
        }
        if (G->get("T") == nullptr || G->get("T")->data != "T data")
        {
            cout << "Incorrect result getting vertex \"T\"" << endl;
        }
        if (G->get("V") == nullptr || G->get("V")->data != "V data")
        {
            cout << "Incorrect result getting vertex \"V\"" << endl;
        }
        if (G->get("W") == nullptr || G->get("W")->data != "W data")
        {
            cout << "Incorrect result getting vertex \"W\"" << endl;
        }
        if (G->get("b") != nullptr)
        {
            cout << "Incorrect result getting non-existant vertex \"b\"" << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error getting vertex from graph : " << e.what() << endl;
    }
}

void test_reachable(Graph<string, string> *G)
{
    try
    {
        if (!G->reachable("R", "V"))
        {
            cout << "Incorrectly identified adjacent vertex \"V\" as unreachable from \"R\"" << endl;
        }
        if (!G->reachable("X", "W"))
        {
            cout << "Incorrectly identified \"W\" as unreachable from \"X\"" << endl;
        }
        if (G->reachable("S", "A"))
        {
            cout << "Incorrectly identified non-existant vetex \"A\" as reachable from \"S\"" << endl;
        }
        if (!G->reachable("Y", "Y"))
        {
            cout << "Incorrectly identified vertex \"Y\" as unreachable from itself" << endl;
        }
        if (!G->reachable("T", "V"))
        {
            cout << "Incorrectly identified adjacent vertex \"V\" as unreachable from \"T\"" << endl;
        }

        if (!G->reachable("U", "R"))
        {
            cout << "Incorrectly identified non-adjacent vertex \"R\" as reachable from \"U\"" << endl;
        }

        if (G->reachable("V", "Z"))
        {
            cout << "Incorrectly identified non-existant vertex \"Z\" as reachable from \"V\"" << endl;
        }

        if (G->reachable("R", "O"))
        {
            cout << "Incorrectly identified non-existant vertex \"O\" as reachable from \"R\"" << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing reachable : " << e.what() << endl;
    }
}

void test_bfs(Graph<string, string> *G)
{
    try
    {
        G->bfs("T");
        string vertices[8] = {"V", "R", "S", "W", "T", "X", "U", "Y"};
        int distances[8] = {3, 2, 1, 1, 0, 2, 1, 2};

        for (int i = 0; i < 8; i++)
        {
            if (G->get(vertices[i]) == nullptr || G->get(vertices[i])->distance != distances[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices[i] << " should have distance " << distances[i]
                     << " from source vertex \"t\"" << endl;
            }
        }

        G->bfs("S");
        string vertices2[3] = {"R", "V", "S"};
        int distances2[3] = {1, 2, 0};

        for (int i = 0; i < 3; i++)
        {
            if (G->get(vertices2[i]) == nullptr || G->get(vertices2[i])->distance != distances2[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices2[i] << " should have distance " << distances2[i]
                     << " from source vertex \"S\"" << endl;
            }
        }

        G->bfs("U");
        string vertices3[4] = {"Y", "W", "X", "U"};
        int distances3[4] = {1, 2, 3, 0};

        for (int i = 0; i < 4; i++)
        {
            if (G->get(vertices3[i]) == nullptr || G->get(vertices3[i])->distance != distances3[i])
            {
                cout << "Incorrect bfs result. Vertex " << vertices3[i] << " should have distance " << distances3[i]
                     << " from source vertex \"U\"" << endl;
            }
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs : " << e.what() << endl;
    }
}

void test_print_path(Graph<string, string> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path("T", "V");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T -> S -> R -> V")
        {
            cout << "Incorrect path from vertex \"T\" to vertex \"V\". Expected: T -> S -> R -> V but got : "
                 << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }

    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path("T", "W");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T -> W")
        {
            cout << "Incorrect path from vertex \"T\" to vertex \"W\". Expected: T -> W but got : "
                 << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }

    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path("T", "X");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T -> W -> X")
        {
            cout << "Incorrect path from vertex \"T\" to vertex \"X\". Expected: T -> W -> X but got : "
                 << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }

    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path("Y", "U");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "Y -> W -> X -> U")
        {
            cout << "Incorrect path from vertex \"Y\" to vertex \"U\". Expected: Y -> W -> X -> U but got : "
                 << buffer.str() << endl;
        }
    }

    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }

    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->print_path("W", "Y");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "W -> X -> U -> Y")
        {
            cout << "Incorrect path from vertex \"W\" to vertex \"Y\". Expected: W -> X -> U -> Y but got : "
                 << buffer.str() << endl;
        }
    }

    catch (exception &e)
    {
        cerr << "Error testing print path : " << e.what() << endl;
    }
}
void test_edge_class(Graph<string, string> *G)
{
    try
    {
        string e_class = G->edge_class("R", "V"); // tree edge
        if (e_class != "tree edge")
        {
            cout << "Misidentified tree edge (\"R\", \"V\") as : " << e_class << endl;
        }
        e_class = G->edge_class("X", "U"); // back edge
        if (e_class != "back edge")
        {
            cout << "Misidentified back edge (\"X\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("R", "U"); // no edge
        if (e_class != "no edge")
        {
            cout << "Misidentified non-existant edge (\"R\", \"U\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "W"); // forward edge
        if (e_class != "forward edge")
        {
            cout << "Misidentified forward edge (\"T\", \"W\") as : " << e_class << endl;
        }
        e_class = G->edge_class("T", "S"); // cross edge
        if (e_class != "cross edge")
        {
            cout << "Misidentified forward edge (\"T\", \"S\") as : " << e_class << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing edge class : " << e.what() << endl;
    }
}

void test_bfs_tree(Graph<string, string> *G)
{
    try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree("T");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "T\nS U W\nR Y X\nV")
        {
            cout << "Incorrect bfs tree. Expected : \nT\nS U W\nR Y X\nV \nbut got :\n"
                 << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    }

     try
    {
        stringstream buffer;
        streambuf *prevbuf = cout.rdbuf(buffer.rdbuf());
        G->bfs_tree("S");
        cout.rdbuf(prevbuf);
        if (buffer.str() != "S\nR\nV")
        {
            cout << "Incorrect bfs tree. Expected : \nS\nR \nV \nbut got : \n"
                 << buffer.str() << endl;
        }
    }
    catch (exception &e)
    {
        cerr << "Error testing bfs tree : " << e.what() << endl;
    } 
}

int main()
{

    cout << "Read File" << endl;
    Graph<string, string> *G = generate_graph("graph_description.txt");
    cout << "Get" << endl;
    test_get(G);
    cout << "Reachable" << endl;
    test_reachable(G);
    cout << "BFS" << endl;
    test_bfs(G);
    cout << "Print Path" << endl;
    test_print_path(G);
    cout << "Edge class" << endl;
    test_edge_class(G);
    cout << "BFS Tree" << endl;
    test_bfs_tree(G);

    cout << "Testing completed" << endl;

    delete G;

    return 0;
}
