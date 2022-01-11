// Ford-Fulkerson algorith in C++

#include <bits/stdc++.h>
using namespace std;

int nodes, edges;
int graph[100][100];
int rGraph[100][100];


bool bfs(int s, int t, int parent[])
{
    bool visited[nodes];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < nodes; v++)
        {
            if (visited[v] == false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return (visited[t] == true);
}

// Applying fordfulkerson algorithm
int fordFulkerson( int s, int t)
{
    int u, v;

    for (u = 0; u < nodes; u++)
        for (v = 0; v < nodes; v++)
            rGraph[u][v] = graph[u][v];

    int parent[nodes];
    int max_flow = 0;

    // Updating the residual values of edges
    while (bfs( s, t, parent))
    {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Adding the path flows
        max_flow += path_flow;
    }

    return max_flow;
}

int main()
{

    cin>>nodes>>edges;

    int a, b, cap;
    for(int i=0; i<edges; i++)
    {
        cin>>a>>b>>cap;
        graph[a][b]=cap;
    }

    int s, t;
    cin>>s>>t;
    cout << "Max Flow: " << fordFulkerson( s, t) << endl;
}
