#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

/// Persistent Disjoint Set Union (DSU) with rollback functionality
/// Used for answering connectivity queries offline in dynamic graph problems
struct PersistentDSU {
    struct State {
        int u, v, rnku, rnkv;

        State() : u(-1), v(-1), rnku(-1), rnkv(-1) {}

        State(int _u, int _rnku, int _v, int _rnkv)
            : u(_u), rnku(_rnku), v(_v), rnkv(_rnkv) {}
    };

    stack<State> st;       // Stack to track state changes for rollback
    int par[N];            // Parent array for DSU
    int depth[N];          // Rank array
    int comp;              // Number of connected components

    PersistentDSU() {
        comp = 0;
        memset(par, -1, sizeof(par));
        memset(depth, 0, sizeof(depth));
    }

    /// Initialize DSU for 'n' nodes
    void init(int n) {
        comp = n;
        for (int i = 0; i <= n; i++) {
            par[i] = i;
            depth[i] = 1;
        }
    }

    /// Find root of a node
    int root(int x) {
        if (x == par[x]) return x;
        return root(par[x]);
    }

    /// Check if two nodes are connected
    bool connected(int x, int y) {
        return root(x) == root(y);
    }

    /// Union of two sets with rollback state tracking
    void unite(int x, int y) {
        int rx = root(x), ry = root(y);
        if (rx == ry) {
            st.push(State());  // Dummy state (no merge)
            return;
        }

        // Union by rank
        if (depth[rx] < depth[ry]) {
            par[rx] = ry;
        } else if (depth[ry] < depth[rx]) {
            par[ry] = rx;
        } else {
            par[rx] = ry;
            depth[rx]++;
        }
        comp--;
        st.push(State(rx, depth[rx], ry, depth[ry]));  // Save state for rollback
    }

    /// Rollback the last 'c' union operations
    void backtrack(int c) {
        while (!st.empty() && c--) {
            if (st.top().u == -1) {
                st.pop();  // Dummy state
                continue;
            }
            par[st.top().u] = st.top().u;
            par[st.top().v] = st.top().v;
            depth[st.top().u] = st.top().rnku;
            depth[st.top().v] = st.top().rnkv;
            st.pop();
            comp++;
        }
    }
};

PersistentDSU dsu;
vector<pair<int, int>> alive[4 * N];  // Segment tree to track edge lifetimes

//This inserts an edge into the segment tree nodes that fully cover the time range [i, j], 
//i.e., the time interval during which this edge is alive (exists in the graph).
void updateEdge(int node, int l, int r, int i, int j, pair<int, int>& edge) {
    if (l > j || r < i) return;
    if (l >= i && r <= j) {
        alive[node].push_back(edge);
        return;
    }
    int mid = (l + r) >> 1;
    updateEdge(2 * node, l, mid, i, j, edge);
    updateEdge(2 * node + 1, mid + 1, r, i, j, edge);
}

int ans[N];  // Stores number of connected components for each query

/// Recursively process queries on the segment tree
void processQueries(int node, int l, int r) {
    if (l > r) return;
    int prevStackSize = dsu.st.size();

    // Add all edges that are active in this segment
    for (auto p : alive[node]) dsu.unite(p.first, p.second);

    if (l == r) {
        ans[l] = dsu.comp;  // Save answer for query
        dsu.backtrack(dsu.st.size() - prevStackSize);
        return;
    }

    int mid = (l + r) >> 1;
    processQueries(2 * node, l, mid);
    processQueries(2 * node + 1, mid + 1, r);

    dsu.backtrack(dsu.st.size() - prevStackSize);
}

/// Custom hash function for pair<int, int>
struct HASH {
    size_t operator()(const pair<int, int>& x) const {
        return hash<long long>()(((long long)x.first) ^ (((long long)x.second) << 32));
    }
};

// startTime[edge] stores the time when an edge was added to the graph.

unordered_map<pair<int, int>, int, HASH> startTime;  // Edge -> insertion time
set<pair<int, int>> currentEdges;  // Active edges
bool isQuery[N];  // Flags for query lines
// true means query 
// false means add/remvoe

int main() {

    startTime.reserve(1 << 20);

    int n, m;
    cin >> n >> m;
    dsu.init(n);  // Initialize DSU for n nodes

    for (int i = 1; i <= m; i++) {
        string type;
        cin >> type;

        if (type == "?") {
            isQuery[i] = true;
        } else {
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v);
            pair<int, int> edge = {u, v};

            if (type == "+") {
                currentEdges.insert(edge);
                startTime[edge] = i;  // Mark start time
            } else {
                currentEdges.erase(edge);
                updateEdge(1, 1, m, startTime[edge], i - 1, edge);  // Add to segment tree
            }
        }
    }

    // Add all remaining edges (still alive till end)
    for (auto edge : currentEdges) {
        updateEdge(1, 1, m, startTime[edge], m, edge);
    }

    // Process all queries and generate answers
    processQueries(1, 1, m);

    // Output answers
    for (int i = 1; i <= m; i++) {
        if (isQuery[i]) cout << ans[i] << '\n';
    }

    return 0;
}
