function<void(int, bool&)> dfs = [&](int u, bool &flag) { 
    if(!flag) return;
    vis[u] = 1;
    for(auto v : g[u]) {
        if(vis[v]) {
            if(col[v] == col[u]) {
                flag = 0;
                return;
            }
            continue;
        }
        col[v] = col[u] ^ 1;
        dfs(v, flag);
    }
};