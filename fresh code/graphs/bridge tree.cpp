// compress all nodes to one component
// where no bridges

// store all bridges (min,max) to map

vis.assign(n + 1, 0);
vector<int> whichcmp(n + 1, 0), path;
int cmpid = 0;

function<void(int)> dfs2 = [&](int u) -> void {
    vis[u] = 1;
    path.push_back(u);
    for(auto v : g[u]) if(!vis[v]) {
        if(mp.count({min(u, v), max(u, v)})) continue;
        dfs2(v);
    }
};

for(int i = 1; i <= n; i++) {
    if(!vis[i]) {
        path.clear();
        dfs2(i);
        cmpid++;
        for(auto x : path) {
            whichcmp[x] = cmpid;
        }
    }
}
// this is the compressed graph
vector<vector<int>> bridgetree(cmpid + 1);
for(int u = 1; u <= n; u++) {
    for(auto v : g[u]) {
        if(whichcmp[u] != whichcmp[v]) {
            bridgetree[whichcmp[u]].push_back(whichcmp[v]);
            bridgetree[whichcmp[v]].push_back(whichcmp[u]);
        }
    }
}  