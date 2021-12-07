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
int par[10000]; //just global purpose
int inMST[10000];
#define INF 1000000000
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
    //cout<<"Kruskal Sum "<<sumKruskal<<endl;

    cout<<"List of edges selected by Kruskal's: {";

    printf("(%d, %d)", resKruskal[0].first, resKruskal[0].second);
    for (int i = 1; i < resKruskal.size(); i++)
        printf(",(%d,%d)", resKruskal[i].first, resKruskal[i].second);
    cout<<"}"<<endl;

//    for(int i=0; i<resKruskal.size(); i++)
//        cout<<resKruskal[i].first<<gap<<resKruskal[i].second<<gap<<gap;
//    cout<<endl;




}

void prim(int n)
{
    double primSum=0;
    priority_queue< pair<double, pii>,
                    vector <pair<double, pii>>,
                    greater<pair<double, pii>> > pq; //eivabe korle min priority queue hobe
    int src = 0;

    vector<pair<int,int>> primResult;
    int key[n];
    for(int i=0; i<n; i++)
        key[i]=INF;

    //edge gula pawar jonno
    int parent[n];
    for(int i=0; i<n; i++)
        parent[i]=-1;

    // To keep track of vertex included in MST
    int inMST[n]= {0};

    pq.push({0, {src,src}});
    key[src] = 0;

    /* Looping till priority queue becomes empty */
    while (!pq.empty())
    {
        int u = pq.top().second.first;
        double tempWeight=pq.top().first;


        pair<double, pii> tempo=pq.top();
        pq.pop();


        //same vertex abar same key diye dhukar chance ache
        if(inMST[u] == true)
        {
            continue;
        }

        inMST[u] = true;  // Include vertex in MST
        primSum+=tempWeight;
        if (tempo.second.first!=tempo.second.second)
            primResult.push_back({tempo.second.first, tempo.second.second});

        // 'i' is used to get all adjacent vertices of a vertex
        for (pair<double, int> i : adj[u])
        {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = i.second;
            double weight = i.first;

            //  If v is not in MST and weight of (u,v) is smaller
            // than current key of v
            if (inMST[v] == false && key[v] > weight)
            {
                // Updating key of v
                key[v] = weight;
                pq.push({key[v], {v, u}});
                parent[v] = u;
            }
        }
    }


    cout<<fixed<<setprecision(2)<<"Cost of the minimum spanning tree : "<<primSum<<endl;
    //cout<<"Primsum is "<<primSum<<endl;
    // Print edges of MST using parent array
    cout<<"List of edges selected by Prim's: {";

//    printf("(%d, %d)", parent[1], 1);
//    for (int i = 2; i < n; ++i)
//        printf(",(%d,%d)", parent[i], i);
//    cout<<"}"<<endl;

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

    freopen("mst.txt", "r", stdin);
    int n, m, a, b;
    double w;
    cin>>n>>m;

    //cout<<n<<gap<<m<<endl;

    for(int i=0; i<n; i++)
        par[i]=-1;

    for(int i=0; i<m; i++)
    {
        cin>>a>>b>>w;
        ar[i].a=a, ar[i].b=b, ar[i].w=w;
        adj[a].push_back({w, b});
        adj[b].push_back({w, a});
    }

    //cout<<"I am here"<<endl;


    prim(n);
    Kruskal(m);


}
