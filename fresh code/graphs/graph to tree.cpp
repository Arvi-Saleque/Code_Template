/*
convert the cycle to a node
make a tree then apply LCA
*/
int component = 0;
vector<int> which(n + 1), col;
col.push_back(0); // make 1 based
vector<bool> vis(n + 1);
vector<int> path;

function<void(int, int)> dfs = [&](int u, int p) -> void {
    vis[u] = 1;
    path.push_back(u);
    for(auto v : g[u]) if(v != p) {
        if(!vis[v]) {
            dfs(v, u);
        }
        else if(!which[v]){
            ++component;
            col.push_back(1);
            int x;
            do {
                x = path.back(); path.pop_back();
                which[x] = component;
            } while (x != v);
        }
    }
    if(!which[u]) {
        ++component;
        col.push_back(0);
        which[u] = component;
        path.pop_back();
    }
};
for(int i = 1; i <= n; i++) {
    if(!vis[i]) dfs(i, -1);
}
vector<vector<int>> tree(component + 1);
for(int u = 1; u <= n; u++) {
    for(auto v : g[u]) {
        if(which[u] != which[v]) {
            tree[which[u]].push_back(which[v]);
        }
    }
}
for(int i = 1; i <= component; i++) {
    auto & adj = tree[i];
    sort(adj.begin(), adj.end());
    adj.erase(unique(adj.begin(), adj.end()), adj.end());
}
