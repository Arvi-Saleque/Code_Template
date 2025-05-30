int time = 0;
vector<bool> vis(n + 1);
vector<int> disc(n + 1), low(n + 1);
function<void(int, int)> dfs = [&](int u, int p) -> void {
    vis[u] = 1;
    disc[u] = low[u] = time++;
    int children = 0;
    for(auto v : g[u]) if (v != p) {
        if(vis[v]) {
            low[u] = min(low[u], disc[v]);
        }
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            // for bridge low[v] > disc[u]
            if(low[v] >= disc[u] && p != -1) { 
                ans.insert(names[u]);
            }
            children++;
        }
    }
    if(p == -1 && children > 1) {
        ans.insert(names[u]);
    }
};