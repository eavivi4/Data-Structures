#include <iostream>
#include <vector>

using namespace std;


class Matrix {
    int numVert;
    vector<vector<int>> matrix;;
public:
    Matrix(int n) {
        // Vertex by vertex matrix
        numVert = n;
        for (int i = 0; i < numVert; i++)
        {
            vector<int> ver;
            for (int j = 0; j < numVert; j++)
            {
                ver.push_back(0);
            }
            matrix.push_back(ver);
        }

    }

    void AddEdge(int a, int b) {
        // -1 because zero indexed
        matrix[a-1][b-1] = 1;
        matrix[b-1][a-1] = 1;
        return;
    }

    bool EdgeExist(int a, int b) {
        return matrix[a-1][b-1];
    }

    void PrintMat() {
        for (int i = 0; i < numVert; i++)
        {
            for (int j = 0; j < numVert; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        return;
    }

};

class Vertex {
    int data;
    vector<int> adj;
public: 
    Vertex(int d) {
        data = d;
    }

    int getData() {
        return data;
    }

    void AddEdge(int b) {
        // Add an edge to the given vertex
        adj.push_back(b);
        return;
    }

    bool EdgeSearch(int b) {
        for (int i = 0; i < adj.size(); i++)
        {
            // Find the edge in the edges list
            if (adj[i] == b)
            {
                return true;
            }
        }
        // No connection to vertex b
        return false;
    }

    void printEdges() {
        for(int i = 0; i < adj.size(); i++)
        {
            cout << adj[i] << " ";
        }
        cout << endl;
        return;
    }
};

class AdjacencyList {
    // List of vertex objects
    vector<Vertex*> adjlist;
public:

    void AddVertex(int a) {
        // Add vertex into adjacency list
        Vertex* v = new Vertex(a);
        adjlist.push_back(v);
        return;
    }

    void AddEdge(int a, int b) {
        for (int i = 0; i < adjlist.size(); i++)
        {
            // Find data in adjacency list and set the other vertex as an edge
            if(adjlist[i]->getData() == a)
            {
                adjlist[i]->AddEdge(b);
            }
            // Add for both vertices because undirected graph
            else if(adjlist[i]->getData() == b)
            {
                adjlist[i]->AddEdge(a);
            }
        }
        return;
    }

    void PrintAdj() {
        for (int i = 0; i < adjlist.size(); i++)
        {
            // Print vertex and then its edges
            cout << "Vertex: " << adjlist[i]->getData() << " Edges: ";
            adjlist[i]->printEdges();
        }
        return;
    }

    bool VertexExist(int a)
    {
        for (int i = 0; i < adjlist.size(); i++)
        {
            // Find data in vertex list
            if(adjlist[i]->getData() == a)
            {
                return true;
            }
        }
        return false;
    }

    bool EdgeExist(int a, int b) {
        if (!VertexExist(a) || !VertexExist(b))
        {
            // If one vertex is not in list
            return false;
        }
        for (int i = 0; i < adjlist.size(); i++)
        {
            // Find data in vertex list
            if(adjlist[i]->getData() == a)
            {
                return adjlist[i]->EdgeSearch(b);
            }
        }
        return false;
    }
};

void BFS() {

}

void DFS() {
    
}

int main() {

    // Undirected Graphs

    cout << "Matrix: " << endl;
    Matrix* m = new Matrix(5);
    m->AddEdge(1,2);
    m->AddEdge(2,3);
    m->AddEdge(4,5);
    m->AddEdge(4,4);
    m->AddEdge(5,1);
    m->AddEdge(3,5);
    m->PrintMat();
    string b = "false";
    if (m->EdgeExist(1,3))
    {
        b = "true";
    }
    cout << "Edge exists between 1 to 3: " << b << endl;
    b = "false";
    if (m->EdgeExist(2,3))
    {
        b = "true";
    }
    cout << "Edge exists between 2 to 3: " << b << endl;

    cout << "Adjacency list: " << endl;
    AdjacencyList* a = new AdjacencyList();
    a->AddVertex(1);
    a->AddVertex(2);
    a->AddVertex(3);
    a->AddVertex(4);
    a->AddVertex(5);
    a->AddEdge(1,2);
    a->AddEdge(2,3);
    a->AddEdge(4,5);
    a->AddEdge(4,4);
    a->AddEdge(5,1);
    a->AddEdge(3,5);
    a->PrintAdj();
    b = "false";
    if (a->EdgeExist(1,3))
    {
        b = "true";
    }
    cout << "Edge exists between 1 to 3: " << b << endl;
    b = "false";
    if (a->EdgeExist(2,3))
    {
        b = "true";
    }
    cout << "Edge exists between 2 to 3: " << b << endl;
    
    return 0;
}