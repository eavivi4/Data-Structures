#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class Matrix {
    int numVert;
    
public:
    vector<vector<int>> matrix;
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

    int GetSize() {
        return numVert;
    }
};

class Vertex {
    int data;
public: 
    vector<int> adj;
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
public:
    // List of vertex objects
    vector<Vertex*> adjlist;

    void AddVertex(int a) {
        // Add vertex into adjacency list
        Vertex* v = new Vertex(a);
        adjlist.push_back(v);
        return;
    }

    void AddEdge(int a, int b) {
        FindVert(a)->AddEdge(b);
        return;
    }

    Vertex* FindVert(int a) {
        for (int i = 0; i < adjlist.size(); i++)
        {
            // Find data in vertex list
            if(adjlist[i]->getData() == a)
            {
                return adjlist[i];
            }
        }
        return nullptr;
    }

    int getSize() {
        return adjlist.size();
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
        if (FindVert(a))
        {
            return true;
        }
        return false;
    }

    bool EdgeExist(int a, int b) {
        if (!VertexExist(a) || !VertexExist(b))
        {
            // If one vertex is not in list
            return false;
        }
        return FindVert(a)->EdgeSearch(b);
    }

    
};

void BFSMat(Matrix* m, int a, int b) {
    // Breath First Search for Matrix
    // Queue
    // Shortest path
    queue<int> q;
    vector<bool> visited(m->GetSize(), false);
    q.push(a);
    visited[a-1] = true;
    while(!q.empty())
    {
        int curr = q.front();
        q.pop();
        cout << curr << ": ";
        
        for (int i = 0; i < m->GetSize(); i++)
        {
            
            if (m->matrix[curr-1][i] && i+1 == b) {
                cout << i+1 << endl;
                return;
            }
            else if (!visited[i+1] && m->matrix[curr-1][i])
            {
                q.push(i+1);
                cout << i+1 << " ";
                visited[i+1] = true;
            }
        }
        cout << endl;
    }
    return;

}

void BFSAdj(AdjacencyList* list, int a, int b) {
    // Breath First Search for Adjacency List
    // Queue
    // Shortest path
    queue<Vertex*> q;
    vector<bool> visited(list->getSize(), false);
    Vertex* start = list->FindVert(a);
    q.push(start);
    visited[start->getData()] = true;
    while(!q.empty())
    {
        Vertex* curr = q.front();
        q.pop();
        cout << curr->getData() << ": ";
        if (curr->EdgeSearch(b)) {
            cout << b << endl;
            return;
        }
        else 
        {
            for (int j = 0; j < curr->adj.size(); j++)
            {
                int element = curr->adj[j];
                if (!visited[element])
                {
                    q.push(list->FindVert(element));
                    cout << element << " ";
                    visited[element] = true;
                }
            }
            
            
        }
        cout << endl;
    }
    return;
}

bool DFSMat(Matrix* m, int a, int b) {
    // Depth First Search for Matrix
    // Stack
    // Path exists
    stack<int> s;
    vector<bool> visited(m->GetSize(), false);
    s.push(a);
    while(!s.empty())
    {
        int curr = s.top();
        s.pop();
        cout << curr << ": ";
        
        for (int i = 0; i < m->GetSize(); i++)
        {
            
            if (m->matrix[curr-1][i] && i+1 == b) {
                cout << i+1 << endl;
                return true;
            }
            else if (!visited[i+1] && m->matrix[curr-1][i])
            {
                s.push(i+1);
                cout << i+1 << " ";
                visited[i+1] = true;
            }
        }
        cout << endl;
    }
    return false;
}

bool DFSAdj(AdjacencyList* list, int a, int b) {
    // Depth First Search for Adjacency list
    // Stack
    // Path exists
    stack<Vertex*> s;
    vector<bool> visited(list->getSize(), false);
    Vertex* start = list->FindVert(a);
    s.push(start);
    visited[start->getData()] = true;
    while(!s.empty())
    {
        Vertex* curr = s.top();
        s.pop();
        cout << curr->getData() << ": ";
        if (curr->EdgeSearch(b)) {
            cout << b << endl;
            return true;
        }
        else 
        {
            for (int j = 0; j < curr->adj.size(); j++)
            {
                int element = curr->adj[j];
                if (!visited[element])
                {
                    s.push(list->FindVert(element));
                    cout << element << " ";
                    visited[element] = true;
                }
            }
            
            
        }
        cout << endl;
    }
    return false;
}

int main() {

    // Directed Graphs

    cout << "Matrix: " << endl;
    Matrix* m = new Matrix(5);
    m->AddEdge(1,2);
    m->AddEdge(2,3);
    m->AddEdge(4,5);
    m->AddEdge(4,4);
    m->AddEdge(5,1);
    m->AddEdge(3,5);
    m->AddEdge(2,5);
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

    cout << "BFS Matrix: " << endl;
    cout << "The shorest path from 1 to 5 is " << endl;
    BFSMat(m, 1, 5);
    cout << "DFS Matrix: " << endl;
    b = "false";
    if (DFSMat(m, 1, 5))
    {
        b = "true";
    }
    cout << "There is a path from 1 to 5: " << b << endl;
    b = "false";
    if (DFSMat(m, 2, 4))
    {
        b = "true";
    }
    cout << "There is a path from 2 to 4: " << b << endl;

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
    a->AddEdge(2,5);
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
    
    cout << "BFS Adjacency List: " << endl;
    cout << "The shorest path from 1 to 5 is " << endl;
    BFSAdj(a, 1, 5);
    cout << "DFS Matrix: " << endl;
    b = "false";
    if (DFSAdj(a, 1, 5))
    {
        b = "true";
    }
    cout << "There is a path from 1 to 5: " << b << endl;
    b = "false";
    if (DFSAdj(a, 2, 4))
    {
        b = "true";
    }
    cout << "There is a path from 2 to 4: " << b << endl;
    return 0;
}