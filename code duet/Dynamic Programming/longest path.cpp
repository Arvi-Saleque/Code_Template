function<int(int)> f = [&](int u) -> int {
    int &ans = dp[u];
    if(ans != -1e9) return ans;
    if(u == n) return ans = 0;
    int mx = -1e9, node = -1;
    for(auto v : g[u]) {
        int cur = f(v);
        if(cur != -1e9 && cur + 1 > mx) {
            mx = cur + 1;
            child[u] = v;
        }
    }
    return ans = mx;
};
f(1);
queue<int> Q;
for(int i = 1; i <= n; i++) {
    if(indeg[i] == 0) Q.push(i);
}
vector<int> topo;
while(!Q.empty()) {
    int u = Q.front(); Q.pop();
    topo.push_back(u);
    for(auto v : g[u]) {
        if(--indeg[v] == 0) {
            Q.push(v);
        }
    }
}
vector<int> dp(n + 1, -1e9);
vector<int> par(n + 1, 0);
dp[1] = 1;
for(auto u : topo) {
    if(dp[u] == -1e9) continue;
    for(auto v : g[u]) {
        if(dp[u] + 1 > dp[v]) {
            dp[v] = dp[u] + 1;
            par[v] = u;
        }
    }
}
 
