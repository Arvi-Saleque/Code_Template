const int N = 5e5 + 9;
const int inf = (1 << 30);
vector<int> g[N];
bool vis[N];
int color[N];

/* Bi coloring with DFS*/
void dfs(int u, bool &ok) {
    if(!ok) return;
    vis[u] = 1;
    for(auto v : g[u]) {
        if(!vis[v]) {
            color[v] = color[u] ^ 1;
            dfs(v, ok);
        }
        else {
            if(color[v] == color[u]) {
                ok = false; // non bicolorable.
                return;
            }
        }
    }
}