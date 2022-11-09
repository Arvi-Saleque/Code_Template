#include <bits/stdc++.h>
using namespace std;
#define left st,(st+en)/2,nod+nod
#define right (st+en)/2+1,en,nod+nod+1
typedef long long int ll;
const int MAX = 200000;
vector<int> graph[MAX+10];
pair<int,int> timeOfU[MAX+10];
bool vis[MAX+10];
int  countOfTime = 1;
ll curArr[2*MAX+10], tree[8*MAX+10];

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
int main() 
{
    return 0;
} 