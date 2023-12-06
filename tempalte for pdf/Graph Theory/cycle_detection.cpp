
vector<int> graph[N+10];
int vis[N+10];
//for undirected graph
void dfs(int u,int par,bool &status)
{
  vis[u] = 1;
  for(auto v : graph[u])
  {
    if(vis[v]==0)
    {
      dfs(v,u,status);
    }
    if(vis[v]==1 && v != par)
    {
      status = true; // cycle detected
      return;
    }
  }
  vis[u] = 2;
}


//for directed graph 
void dfs(int u,bool &status)
{
  vis[u] = 1;
  for(auto v : graph[u])
  {
    if(vis[v]==0)
    {
      dfs(v,status);
    }
    if(vis[v]==1)
    {
      status = true; // cycle detected
      return;
    }
  }
  vis[u] = 2;
}