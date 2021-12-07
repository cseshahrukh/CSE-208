#include <bits/stdc++.h>
using namespace std;

#define gap ' '
#define pii pair<int,int>
struct edge
{
    int a;
    int b;
    double w;
};

edge ar[100000]; //just global purpose
int par[10000];
vector<pair<double, int>> adj[10000]; //assuming highest node is 10000
bool cmp(edge a, edge b)
{
    if (a.w<b.w)
        return true;
    return false;
}

int find(int a)
{
    if (par[a]==-1)
        return a;
    return par[a]=find(par[a]); //just doing path compression
}

void merge(int a, int b)
{
    par[a]=b;
}

void Kruskal(int m)
{
    int a, b;
    sort(ar, ar+m, cmp);
    double sumKruskal=0;
    vector<pair<int,int>> resKruskal;
    for(int i=0; i<m; i++)
    {
        a=find(ar[i].a);
        b=find(ar[i].b); //finding parents

        if (a!=b)
        {
            sumKruskal+=ar[i].w;
            merge(a,b);
            resKruskal.push_back({ar[i].a, ar[i].b});
        }
    }


    //cout<<"Cost of the minimum spanning tree :"<<sumKruskal<<endl;

    cout<<"List of edges selected by Kruskal's: {";

    printf("(%d,%d)", resKruskal[0].first, resKruskal[0].second);
    for (int i = 1; i < resKruskal.size(); i++)
        printf(",(%d,%d)", resKruskal[i].first, resKruskal[i].second);
    cout<<"}"<<endl;

}


void prim(int n)
{
    double primSum=0;
    priority_queue< pair<double, pii>,
                    vector <pair<double, pii>>,
                    greater<pair<double, pii>> > pq; //eivabe korle min priority queue hobe
                    //weight, destNode, fromNode
    int src = 0;

    pair<double, pii> triple;
    vector<pair<int,int>> primResult;
    int visited[n]={};



    pq.push({0, {src,src}});
    visited[src] = 1;

    int dest, beginNode;
    double nowWeight;
    /* Looping till priority queue becomes empty */
    while (!pq.empty())
    {
        triple=pq.top();
        pq.pop();

        dest=triple.second.second;
        beginNode=triple.second.first;
        nowWeight=triple.first;

        if (visited[dest]==1 and dest!=beginNode)
            continue; //checking cycle or handleing source case


        primSum+=nowWeight;
        if (beginNode!=dest)
            primResult.push_back({beginNode, dest});

        visited[dest]=1;
        for(pair<double, int> childOfDest: adj[dest])
        {
            if (!visited[childOfDest.second])
            {
                pq.push({childOfDest.first, {dest, childOfDest.second}}) ;//weight, source, destination
            }

        }
    }


    cout<<fixed<<setprecision(2)<<"Cost of the minimum spanning tree : "<<primSum<<endl;

    cout<<"List of edges selected by Prim's: {";


    int counter=0;
    for(pair<int, int> i: primResult)
    {
        if (counter!=0)
            printf(",(%d,%d)", i.first, i.second); //leading ,
        else
            printf("(%d,%d)", i.first, i.second);
        counter++; //just like a flag
    }
    cout<<"}"<<endl;

}
int main ()
{

    freopen("mst.in", "r", stdin);
    int n, m, a, b;
    double w;
    cin>>n>>m;

    for(int i=0; i<n; i++)
        par[i]=-1;

    for(int i=0; i<m; i++)
    {
        cin>>a>>b>>w;
        ar[i].a=a, ar[i].b=b, ar[i].w=w;
        adj[a].push_back({w, b});
        adj[b].push_back({w, a});
    }

    prim(n);
    Kruskal(m);

    return 0;
}
