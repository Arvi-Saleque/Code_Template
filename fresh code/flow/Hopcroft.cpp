// Hopcroft-Karp Algorithm for Maximum Bipartite Matching
// Complexity: O(E * sqrt(V))
// 1-indexed input nodes
// Usage:
//   HK hk(n);                    // Initialize with number of left side nodes
//   hk.addEdge(u, v);           // Add edge from node u (left) to v (right)
//   int result = hk.max_match(); // Returns size of maximum matching

struct HK {
  static const int inf = 1e9;
  int n;  // Number of nodes on the left side of bipartite graph

  vector<int> matchL, matchR, dist;
  // matchL[u] = matched node of u in Right set
  // matchR[v] = matched node of v in Left set
  // dist[u] = distance in BFS level graph
  vector<vector<int>> adj;  // Adjacency list for left set

  // Constructor: initializes internal structures
  HK(int n) : n(n), matchL(n + 1), matchR(n + 1), dist(n + 1), adj(n + 1) {}

  // Adds an edge from node u (Left) to node v (Right)
  void addEdge(int u, int v) {
    adj[u].push_back(v);
  }

  // BFS to build level graph
  // Returns true if there's an augmenting path
  bool bfs() {
    queue<int> q;
    for (int u = 1; u <= n; u++) {
      if (!matchL[u]) {
        dist[u] = 0;  // Free node, start BFS
        q.push(u);
      } else {
        dist[u] = inf;
      }
    }
    dist[0] = inf;  // 0 represents null node

    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (auto v : adj[u]) {
        if (dist[matchR[v]] == inf) {
          dist[matchR[v]] = dist[u] + 1;
          q.push(matchR[v]);
        }
      }
    }
    return dist[0] != inf;  // If null node is reached, path exists
  }

  // DFS to find and augment augmenting path from node u
  // Returns true if path is found
  bool dfs(int u) {
    if (!u) return true;  // Null node reached, path found
    for (auto v : adj[u]) {
      if (dist[matchR[v]] == dist[u] + 1 && dfs(matchR[v])) {
        matchL[u] = v;
        matchR[v] = u;
        return true;
      }
    }
    dist[u] = inf;  // Mark as dead end
    return false;
  }

  // Computes and returns maximum matching
  int max_match() {
    int matching = 0;
    while (bfs()) {
      for (int u = 1; u <= n; u++) {
        if (!matchL[u] && dfs(u)) {
          matching++;
        }
      }
    }
    return matching;
  }
};
