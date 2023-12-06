/* DFS by start and end time.
mainly you can create the tree into an array with this*/

const int N = 1e5+9;
bool vis[N];
int strt[N], End[N], deg[N];
int Time = 1;
vector<int> graph[N];
void dfs(int u) {
    vis[u] = 1;
    strt[u] = Time++;
    for(auto x : graph[u]) {
        if(vis[x]) continue;
        dfs(x);
    }
    End[u] = Time++;
}