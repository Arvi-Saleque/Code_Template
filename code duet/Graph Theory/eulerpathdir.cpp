class Graph {
public: 
    int n, m;
    vector<vector<int>> g; 
    vector<int> indeg, outdeg, path, edge, done;
    Graph(){}
    Graph(int n, int m = 0) {
        this -> n = n;
        this -> m = m;
        g.assign(n + 1, vector<int>());
        indeg.assign(n + 1, 0);
        outdeg.assign(n + 1, 0);
        done.assign(n + 1, 0);
        take_input();
    }
    void take_input() {
        for(int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            indeg[v]++;
            outdeg[u]++;
            g[u].push_back(v);
        }
    }
    void dfs(int u) {
        while(done[u] < g[u].size()) dfs(g[u][done[u]++]);
        path.push_back(u);
    }
    int find_root() {
        int root = -1, in = 0, out = 0, ok = 1;
        int end = 0, eq = 0;
        for(int i = 1; i <= n; i++) {
            if(indeg[i] == outdeg[i]) eq++;
            if(indeg[i] - outdeg[i] == 1) in++, end = i;
            if(outdeg[i] - indeg[i] == 1) out++, root = i;
            if(abs(indeg[i] - outdeg[i]) > 1) ok = 0;
        }
        // change the condition according to the problem
        if(root != 1 || end != n) return -1;
        if(!(eq == n - 2 && in == 1 && out == 1)) return -1;
        if(!ok) return -1;
        return root;
    }
    void calc() {
        int root = find_root();
        if(root == -1) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        dfs(root);
        reverse(path.begin(), path.end());
 
        if(path.size() != m + 1) {
            cout << "IMPOSSIBLE\n";
            return;
        }

        //cout << "Yes\n";
        for(int i = 0; i < path.size(); i++) {
            cout << path[i] << (i + 1 == path.size() ? '\n' : ' ');
        }
    }
} G;