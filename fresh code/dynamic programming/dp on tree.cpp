vector<int> down(n + 1);
vector<int> best1(n + 1, -1), best2(n + 1, -1);
function<int(int, int)> dfs1 = [&](int u, int p) -> int {
    for(auto v : g[u]) if(v != p) {
        int cand = 1 + dfs1(v, u);                          
        if (cand > best1[u]) { best2[u] = best1[u]; best1[u] = cand; }
        else if (cand > best2[u]) best2[u] = cand;
        down[u] = max(down[u], cand); 
    }
    return down[u];
};
dfs1(1, 0);

vector<int> up(n + 1);
function<void(int, int)> dfs2 = [&](int u, int p) -> void {
    for(auto v : g[u]) if(v != p) {
        int val = (down[v] + 1 == best1[u]) ? best2[u] : best1[u];
        up[v] = 1 + max(up[u], val);
        dfs2(v, u);
    } 
    
};
dfs2(1, 0);

// knapsack
vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, neg));
function<void(int, int)> dfs = [&](int u, int p) -> void {
    dp[u][1] = cost[u];

    for(auto v : g[u]) if ( v != p) {
        dfs(v, u);

        vector<ll> ndp(k + 1, neg);
        for(int x = 1; x <= k; x++) {
            if(dp[u][x] == neg) continue;
            for(int y = 0; x + y <= k; y++) {
                if(dp[v][y] == neg) continue;
                ndp[x + y] = max(ndp[x + y], dp[u][x] + dp[v][y]);
            }
        }

        for(int i = 1; i <= k; i++) {
            dp[u][i] = max(ndp[i], dp[u][i]);
        }
    }
}