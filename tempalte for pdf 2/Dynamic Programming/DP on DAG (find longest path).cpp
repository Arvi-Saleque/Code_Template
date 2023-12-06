int dp[N];
vector<int> g[N+5];
int dfs(int u) {
    if(dp[u] != -1) return dp[u];
    int ans = 0;
    for(auto v : g[u]) {
        ans = max(ans, 1 + dfs(v));
    }
    return dp[u] = ans;
}
void solve() {
    int n, m;
    cin >> n >> m;
    for(int i=1;i<=m;i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
    memset(dp, -1, sizeof dp);
    int ans = 0;
    for(int i=1;i<=n;i++) {
        ans = max(ans, dfs(i));
    }
    cout << ans << "\n";
}