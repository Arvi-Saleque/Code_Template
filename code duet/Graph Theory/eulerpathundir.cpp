class Graph {
public: 
    int n, m;
    vector<vector<pair<int, int>>> g; 
    vector<int> path, done, vis, deg;
    Graph(){}
    Graph(int n, int m = 0) {
        this -> n = n;
        this -> m = m;
        g.assign(n + 1, vector<pair<int, int>>());
        done.assign(n + 1, 0);
        vis.assign(m + 1, 0);
        deg.assign(m + 1, 0);
        take_input();
    }
    void take_input() {
        for(int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            deg[u]++;
            deg[v]++;
            g[u].push_back({v, i});
            g[v].push_back({u, i});
        }
    }
    void dfs(int u) {
        while (done[u] < g[u].size()) {
            auto e = g[u][done[u]++];
            if (vis[e.second]) continue;
            vis[e.second] = 1;
            dfs(e.first);
        }
        path.push_back(u);
    }
    int find_root() {
        // change the condition according to the problem
        if((deg[1] & 1) || (g[1].empty())) {
            return -1;
        }
        int odd = 0;
        for(int i = 1; i <= n; i++) {
            odd += (deg[i] & 1);
        }
        if(odd > 0) return -1;
        return 1;
    }
    void calc() {
        int root = find_root();
        if(root == -1) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        dfs(root);
        if (path.size() != m + 1) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        reverse(path.begin(), path.end());
        for(auto x : path) {
            cout << x << " ";
        }
    }
} G;