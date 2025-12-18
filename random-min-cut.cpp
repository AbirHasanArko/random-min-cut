#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

struct Edge
{
    int u, v;
};

struct Graph
{
    int V;
    int E;
    vector<Edge> edges;
};

// DSU Structure
int findParent(vector<int> &parent, int i)
{
    if (parent[i] != i)
        parent[i] = findParent(parent, parent[i]);
    return parent[i];
}

void unite(vector<int> &parent, vector<int> &rank, int x, int y)
{
    int xroot = findParent(parent, x);
    int yroot = findParent(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else
    {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

// Random Min Cut
int randomMinCut(Graph &graph)
{
    int V = graph.V;
    int E = graph.E;

    vector<int> parent(V);
    vector<int> rank(V, 0);

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int vertices = V;

    while (vertices > 2)
    {
        int i = rand() % E;

        int subset1 = findParent(parent, graph.edges[i].u);
        int subset2 = findParent(parent, graph.edges[i].v);

        if (subset1 != subset2)
        {
            unite(parent, rank, subset1, subset2);
            vertices--;
        }
    }

    int cutEdges = 0;
    for (int i = 0; i < E; i++)
    {
        int subset1 = findParent(parent, graph.edges[i].u);
        int subset2 = findParent(parent, graph.edges[i].v);
        if (subset1 != subset2)
            cutEdges++;
    }

    return cutEdges;
}

int main()
{
    srand(time(NULL));

    Graph graph;

    cout << "Enter no of vertices and edges: ";
    cin >> graph.V >> graph.E;

    graph.edges.resize(graph.E);

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < graph.E; i++)
    {
        cin >> graph.edges[i].u >> graph.edges[i].v;
    }

    int minCut = INF;

    // run multiple times for better accuracy
    for (int i = 0; i < 30; i++)
    {
        int cut = randomMinCut(graph);
        minCut = min(minCut, cut);
    }

    cout << "\nMinimum Cut: " << minCut << endl;

    return 0;
}
