#include <bits/stdc++.h>
using namespace std;
const int MAX = 200000;
vector<int> graph[MAX+10];
int color[MAX+10];
bool vis[MAX+10];

/* Bi coloring with DFS*/
void dfs(int u,int clr,bool &flag)
{
    color[u] = clr;
    vis[u] = 1;
    for(auto x : graph[u])
    {
        if(!vis[x])
        {
            if(clr == 1) dfs(x,2,flag);
            else dfs(x,1,flag);
            if(!flag) return;
        }
        if(color[x] == color[u])
        {
            flag = false; // non bicolorable.
            return;
        }
    }
}
int main() 
{
    return 0;
} 