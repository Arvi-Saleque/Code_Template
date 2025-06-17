// Stores information needed to undo a union operation
struct dsu_save {
  int v, rnkv, u, rnku;
  dsu_save() {}
  dsu_save(int _v, int _rnkv, int _u, int _rnku)
    : v(_v), rnkv(_rnkv), u(_u), rnku(_rnku) { }
};

// Disjoint Set Union (DSU) with rollback support
struct dsu_with_rollbacks {
  vector<int> p, rnk;     // Parent and rank arrays
  int comps;              // Number of connected components
  stack<dsu_save> op;     // Stack to store history for rollback

  dsu_with_rollbacks() {}
  dsu_with_rollbacks(int n) {
    p.resize(n);
    rnk.resize(n);
    for (int i = 0; i < n; i++) {
      p[i] = i;           // Each node is its own parent
      rnk[i] = 0;         // Initial rank is 0
    }
    comps = n;            // Initially, each node is a separate component
  }

  // Find representative of a set (no path compression)
  int find_set(int v) { return (v == p[v]) ? v : find_set(p[v]); }

  // Union two sets, return true if merged
  bool unite(int v, int u) {
    v = find_set(v);
    u = find_set(u);
    if (v == u) return false; // Already in the same set

    comps--; // One less component after union

    // Union by rank
    if (rnk[v] > rnk[u]) swap(v, u);

    // Save state before union for rollback
    op.push(dsu_save(v, rnk[v], u, rnk[u]));

    p[v] = u; // Union
    if (rnk[u] == rnk[v]) rnk[u]++; // Increase rank if same

    return true;
  }

  // Undo the last union operation
  void rollback() {
    if (op.empty()) return;
    dsu_save x = op.top(); op.pop();
    comps++; // Restore component count

    // Restore parent and rank values
    p[x.v] = x.v;
    rnk[x.v] = x.rnkv;
    p[x.u] = x.u;
    rnk[x.u] = x.rnku;
  }
};

// Represents a union query
struct query {
  int v, u;
  bool united; // Whether this union actually merged components
  query(int _v, int _u) : v(_v), u(_u) {}
};

// Segment tree structure to handle time intervals of queries
struct QueryTree {
  vector<vector<query>> t;  // Segment tree nodes store query lists
  dsu_with_rollbacks dsu;   // DSU with rollback support
  int T;                    // Total time steps

  QueryTree() {}
  QueryTree(int _T, int n) : T(_T) {
    dsu = dsu_with_rollbacks(n); // Initialize DSU
    t.resize(4 * T + 4);         // Resize segment tree
  }

  // Add query to segment tree in range [ul, ur]
  void add_to_tree(int v, int l, int r, int ul, int ur, query& q) {
    if (ul > ur) return;
    if (l == ul && r == ur) {
      t[v].push_back(q);
      return;
    }
    int mid = (l + r) / 2;
    add_to_tree(2 * v, l, mid, ul, min(ur, mid), q);
    add_to_tree(2 * v + 1, mid + 1, r, max(ul, mid + 1), ur, q);
  }

  // Public method to insert query in range [l, r]
  void add_query(query q, int l, int r) {
    add_to_tree(1, 0, T - 1, l, r, q);
  }

  // DFS traversal of segment tree to apply queries and compute answers
  void dfs(int v, int l, int r, vector<int>& ans) {
    // Apply all queries at current segment
    for (query& q : t[v]) {
      q.united = dsu.unite(q.v, q.u);
    }

    // If leaf node, store current number of components
    if (l == r) {
      ans[l] = dsu.comps;
    } else {
      int mid = (l + r) / 2;
      dfs(2 * v, l, mid, ans);       // Recurse on left child
      dfs(2 * v + 1, mid + 1, r, ans); // Recurse on right child
    }

    // Rollback changes for this segment
    for (query q : t[v]) {
      if (q.united) dsu.rollback();
    }
  }

  // Start processing and return final answers
  vector<int> solve() {
    vector<int> ans(T);
    dfs(1, 0, T - 1, ans);
    return ans;
  }
};
