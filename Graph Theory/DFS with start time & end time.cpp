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

/* DFS by start and end time.
mainly you can create the tree into an array with this*/
void dfs(int u)
{
    vis[u] = 1;
    timeOfU[u].first = countOfTime++;
    for(auto x : graph[u])
    {
        if(!vis[x])
        {
            dfs(x);
        }
    }
    timeOfU[u].second = countOfTime++;
}
int main() 
{
    return 0;
} 