/* Hungarian Algorithm for Minimum Cost Maximum Matching
 * Complexity: O(n^3), but optimized
 * Finds **minimum cost** perfect matching in a complete bipartite graph.
 * To find **maximum cost** matching, negate all edge costs and negate final answer.
 * 1-indexed input.
 */

struct Hungarian {
  static const int N = 505;
  long long c[N][N];      // Cost matrix: c[u][v] = cost of matching u with v
  long long fx[N], fy[N]; // fx = potentials for left side, fy = for right
  long long d[N];         // d[v] = reduced cost estimates during BFS
  int l[N], r[N];         // l[u] = match for u in left set, r[v] = match for v in right set
  int arg[N], trace[N];   // arg[v] = best left node for v, trace = path reconstruction
  queue<int> q;           // Queue for BFS
  int start, finish, n;
  const long long inf = 1e18;

  Hungarian() {}

  // Constructor: Initialize for matching between n1 and n2 nodes (1-indexed)
  Hungarian(int n1, int n2) : n(max(n1, n2)) {
    for (int i = 1; i <= n; ++i) {
      fy[i] = l[i] = r[i] = 0;
      for (int j = 1; j <= n; ++j) c[i][j] = inf;
    }
  }

  // Add edge with cost from node u (left) to v (right)
  void add_edge(int u, int v, long long cost) {
    c[u][v] = min(c[u][v], cost); // If multiple edges exist, keep the minimum cost
  }

  // Returns reduced cost of matching u and v
  inline long long getC(int u, int v) {
    return c[u][v] - fx[u] - fy[v];
  }

  // Initializes BFS for current left node `start`
  void initBFS() {
    while (!q.empty()) q.pop();
    q.push(start);
    for (int i = 0; i <= n; ++i) trace[i] = 0;
    for (int v = 1; v <= n; ++v) {
      d[v] = getC(start, v);
      arg[v] = start;
    }
    finish = 0;
  }

  // Performs BFS to find an augmenting path from `start`
  void findAugPath() {
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v = 1; v <= n; ++v) {
        if (!trace[v]) {
          long long w = getC(u, v);
          if (!w) { // Edge is tight (reduced cost 0)
            trace[v] = u;
            if (!r[v]) {
              finish = v; // Found an augmenting path to unmatched right node
              return;
            }
            q.push(r[v]);
          }
          if (d[v] > w) { // Relax the edge
            d[v] = w;
            arg[v] = u;
          }
        }
      }
    }
  }

  // Updates potentials when no augmenting path found
  void subX_addY() {
    long long delta = inf;
    // Find smallest slack over all unvisited right nodes
    for (int v = 1; v <= n; ++v) {
      if (!trace[v] && d[v] < delta) {
        delta = d[v];
      }
    }

    // Update potentials
    fx[start] += delta;
    for (int v = 1; v <= n; ++v) {
      if (trace[v]) {
        int u = r[v];
        fy[v] -= delta;
        fx[u] += delta;
      } else {
        d[v] -= delta;
      }
    }

    // Try to extend the tree with tight edges
    for (int v = 1; v <= n; ++v) {
      if (!trace[v] && d[v] == 0) {
        trace[v] = arg[v];
        if (!r[v]) {
          finish = v;
          return;
        }
        q.push(r[v]);
      }
    }
  }

  // Augments the matching using the path traced to `finish`
  void Enlarge() {
    while (finish) {
      int u = trace[finish];
      int nxt = l[u];
      l[u] = finish;
      r[finish] = u;
      finish = nxt;
    }
  }

  // Computes the minimum cost maximum matching
  // Returns the total cost of the matching
  long long maximum_matching() {
    // Initialize potentials fx and fy
    for (int u = 1; u <= n; ++u) {
      fx[u] = c[u][1];
      for (int v = 1; v <= n; ++v) {
        fx[u] = min(fx[u], c[u][v]);
      }
    }

    for (int v = 1; v <= n; ++v) {
      fy[v] = c[1][v] - fx[1];
      for (int u = 1; u <= n; ++u) {
        fy[v] = min(fy[v], c[u][v] - fx[u]);
      }
    }

    // Try to match each node from left side
    for (int u = 1; u <= n; ++u) {
      start = u;
      initBFS();
      while (!finish) {
        findAugPath();
        if (!finish) subX_addY();
      }
      Enlarge();
    }

    // Calculate total cost of the final matching
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
      if (c[i][l[i]] != inf) ans += c[i][l[i]];
      else l[i] = 0; // No match
    }
    return ans;
  }
};
