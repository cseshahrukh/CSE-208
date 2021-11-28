vi ar[1000]; 
vi tr[1000]; 

vi order; 
vi SCC; 

int vis[1000]; 

void dfs(int node) 
{
  vis[node]=1; 
  for(int child: ar[node])
    if (vis[child]==0)
      dfs(child)
      
   order.pb(node); 
  
}

void dfs1(int node)
{
  vis[node]=1;
  for(int child : tr[node])
    if (vis[child]==0)
      dfs1(child); 
  
  SCC.pb(node); 
}

int main()
{
  int n, m, a, b, t; 
  cin>>n>>m; 
  
  for(int i=1; i<1000; i++)
    ar[i].clear(), tr[i].clear(), vis[i]=0; 
  order.clear(); 
  
  for(int i=1; i<=m; i++)
  {
    cin>>a>>b; 
    ar[a].pb(b); 
    tr[b].pb(a); 
  }
  
  for(int i=1; i<=n; i++)
    if (vis[i]==0)
      dfs(i); 
    
  for (int i=1; i<=n; i++)
    vis[i]=0; 
  
  for(int i=1; i<=n; i++)
  {
    if (vis[order[n-i]]==0)
    {
      SCC.clear(); 
      dfs1(order[n-i]); 
      
      cout<<"printing one scc"<<endl; 
      
      for(int node: SCC)
        cout<<node<<" " ; 
      cout<<endl; 
    }
  }
}
