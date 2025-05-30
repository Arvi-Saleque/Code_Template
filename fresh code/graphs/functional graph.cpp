/*
In a functional graph:
- Each node has exactly one outgoing edge (outdegree = 1).
- Each connected component contains exactly one cycle.
- All other nodes form directed trees with edges pointing toward the cycle.
- Every non-cyclic (tree) node has a unique path leading to the cycle.
*/
struct Functional_graph {
    vector<vector<int>> rg, up;
    vector<int> t, whichcmp, cyclepos, cyclelen, depth;
    int n, q, compid, lg;
    Functional_graph(int n, int q) : n(n), q(q) {
        rg.resize(n + 1);
        whichcmp.assign(n + 1, 0);
        cyclepos.assign(n + 1, -1);
        cyclelen.assign(n + 1, 0);
        depth.assign(n + 1, -1);
        t.assign(n + 1, 0);
        compid = 0;
        lg = __lg(n) + 1;
        up.assign(n + 1, vector<int>(lg + 1));
        take_input();
    }
    void take_input() {
        for(int u = 1; u <= n; u++) {
            cin >> t[u]; // u -> v  u -> t[u]
            rg[t[u]].push_back(u);
        }
        build();
    }
    void build() {
        // find cycles and label the compid to nodes 
        vector<int> state(n + 1), path;
        function<void(int)> dfs = [&](int u) -> void {
            state[u] = 1;
            path.push_back(u);
            int v = t[u];
            if(state[v] == 0) {
                dfs(v);
            }
            else if(state[v] == 1) {
                vector<int> cycle;
                while(1) {
                    int x = path.back(); path.pop_back();
                    cycle.push_back(x);
                    if(x == v) break;
                }
                compid++;
                int len = cycle.size();
                for(int i = len - 1; i >= 0; i--) {
                    int cycle_node = cycle[i];
                    whichcmp[cycle_node] = compid;
                    cyclepos[cycle_node] = len - 1 - i;
                }
                cyclelen[compid] = len;
            }   
            state[u] = 2;
            if(!path.empty() && path.back() == u) path.pop_back();
        };

        for(int i = 1; i <= n; i++) {
            if(state[i] == 0) dfs(i);
        }

        // calculate the min distances
        queue<int> Q;
        for(int u = 1; u <= n; u++) {
            if(cyclepos[u] >= 0) {
                Q.push(u);
                depth[u] = 0;
            }
        }
        while(not Q.empty()) {
            int u = Q.front(); Q.pop();
            for(auto v : rg[u]) {
                if(depth[v] == -1) {
                    depth[v] = depth[u] + 1;
                    whichcmp[v] = whichcmp[u];
                    Q.push(v);
                }
            } 
        }

        // build the binary lifting upents array
        // toward the cycle like 
        // a -> b -> c where c cycle node
        // up[a][0] = b up[a][1] = c 
        for(int j = 0; j <= lg; j++) {
            for(int u = 1; u <= n; u++) {
                if(j == 0) {
                    up[u][0] = t[u];
                }
                else {
                    up[u][j] = up[up[u][j - 1]][j - 1];
                }
            }
        }
    }
    int kth(int u, int k) {
        for(int i = 0; i <= lg; i++) {
            if((k >> i) & 1) {
                u = up[u][i];
            }
        }
        return u;
    }
    int query(int a, int b) { // min distance of (a, b)
        if(whichcmp[a] != whichcmp[b]) {
            return -1;
        }
        if(cyclepos[b] < 0) { // b is not in the cycle
            if(depth[a] < depth[b]) {
                return -1;  // b -> c -> d -> a // b -> a
            }
            int d = depth[a] - depth[b];
            return (kth(a, d) == b ? d : -1);
        }
        // b in cycle
        int d = depth[a]; // a theke cycle node er distance
        int cycle_node = kth(a, d); // cycle node
        int cycle_id = whichcmp[cycle_node];
        int len = cyclelen[cycle_id];
        int pos1 = cyclepos[cycle_node];
        int pos2 = cyclepos[b];
        return d + ((pos2 - pos1 + len) % len);
    }
};