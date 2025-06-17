#include <bits/stdc++.h>
using namespace std;
 
//maximum bipartite matcher

struct Kuhn {
    int nL, nR;                       // |Left| (boys), |Right| (girls)
    vector<vector<int>> adj;          // adj[u] = list of rights v s.t. (u,v) is an edge
    vector<int> matchR;               // matchR[v] = matched left vertex or -1
    vector<char> seen;                // DFS marker

    Kuhn(int nL, int nR) : nL(nL), nR(nR), adj(nL), matchR(nR, -1), seen(nR) {}

    // add an edge u∈[0,nL)  ↔  v∈[0,nR)
    void addEdge(int u, int v) { adj[u].push_back(v); }

    // classic DFS attempt to find an augmenting path from left vertex u
    bool dfs(int u) {
        for (int v : adj[u]) {
            if (seen[v]) continue;
            seen[v] = true;
            if (matchR[v] == -1 || dfs(matchR[v])) {
                matchR[v] = u;
                return true;
            }
        }
        return false;
    }

    // returns list of matched pairs {u, v} (0-based) of maximum size
    vector<pair<int,int>> maxMatching() {
        for (int u = 0; u < nL; ++u) {
            fill(seen.begin(), seen.end(), 0);
            dfs(u);                           // try to augment starting from u
        }
        vector<pair<int,int>> res;
        for (int v = 0; v < nR; ++v)
            if (matchR[v] != -1)
                res.push_back({matchR[v], v});
        return res;                           // maximum matching
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;

    Kuhn matcher(n, m);               // boys = left, girls = right
    while (k--) {
        int a, b;
        cin >> a >> b;
        --a; --b;                     // convert to 0-based
        matcher.addEdge(a, b);
    }

    auto match = matcher.maxMatching();

    cout << match.size() << '\n';
    for (auto [u, v] : match)
        cout << (u + 1) << ' ' << (v + 1) << '\n';   // back to 1-based
    return 0;
}
