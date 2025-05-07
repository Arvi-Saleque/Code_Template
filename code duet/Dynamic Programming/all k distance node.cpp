// We'll use a 2D vector where dp[u][d] is the number of nodes in the subtree
// of u that are at distance d from u.
vector<vector<int>> dp;
// DFS function: computes dp[u] for node u.
void dfs(int u, int parent) {
    dp[u][0] = 1; // the node itself is at distance 0
    for (int v : adj[u]) {
        if(v == parent) continue;
        dfs(v, u);
        // For each pair of distances from u and v,
        // if d1 (from u's current dp) and d2 (from v's dp) satisfy d1 + d2 + 1 == k,
        // then these pairs of nodes are at distance k.
        for (int d1 = 0; d1 < k; d1++) {
            // d1 is distance from u, d2 from v must satisfy: d1 + d2 + 1 == k
            int d2 = k - d1 - 1;
            if(d2 < 0 || d2 >= k) continue;
            ans += (ll) dp[u][d1] * dp[v][d2];
        }
        // Now, merge dp[v] into dp[u]:
        // For each distance d in v, nodes in v are at distance (d + 1) from u.
        for (int d = k - 1; d >= 0; d--) {
            dp[u][d + 1] += dp[v][d];
        }
    }
}