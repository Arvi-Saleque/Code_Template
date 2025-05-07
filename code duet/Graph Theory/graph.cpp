struct Graph {
    int V;                      // Number of vertices
    vector<vector<int>> adj;    // Adjacency list
    vector<vector<int>> adjrev; // Reverse adjacency list for SCC

    bool isCyclicUtil(int v, vector<bool> &visited, vector<bool> &recStack) {
        if (!visited[v]) {
            visited[v] = true;
            recStack[v] = true;
            for (int u : adj[v]) {
                if (!visited[u] && isCyclicUtil(u, visited, recStack)) {
                    return true;
                }
                else if (recStack[u]) {
                    return true;
                }
            }
        }
        recStack[v] = false;
        return false;
    }
    bool isCyclic() {
        vector<bool> visited(V + 1, false);
        vector<bool> recStack(V + 1, false);
        for (int v = 1; v <= V; v++) {
            if (isCyclicUtil(v, visited, recStack)) {
                return true;
            }
        }
        return false;
    }

    vector<int> bfs(int s) {
        vector<bool> visited(V + 1, false);
        vector<int> result; // do operation in this vector
        queue<int> q;
        q.push(s);
        visited[s] = true;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            result.push_back(v);
            for (int u : adj[v]) {
                if (!visited[u]) {
                    visited[u] = true;
                    q.push(u);
                }
            }
        }
        return result;
    }

    void dfs(int v, vector<bool> &visited, vector<int> &result) {
        visited[v] = true;
        result.push_back(v);
        for (int u : adj[v]) {
            if (!visited[u]) {
                dfs(u, visited, result);
            }
        }
    }

    vector<vector<int>> connectedComponents() {
        vector<bool> visited(V + 1, false);
        vector<vector<int>> components;
        for (int v = 1; v <= V; ++v) {
            if (!visited[v]) {
                vector<int> component;
                dfs(v, visited, component);
                components.push_back(component);
            }
        }
        return components;
    }
    void bridgeUtil(int vr, vector<bool> &visited, vector<int> &disc, vector<int> &low, vector<int> &parent, vector<pair<int, int>> &ans) {
        static int time = 0;
        visited[vr] = true;
        disc[vr] = low[vr] = ++time;

        for (int ch : adj[vr]) {
            if (!visited[ch]) {
                parent[ch] = vr;
                bridgeUtil(ch, visited, disc, low, parent, ans);
                low[vr] = min(low[vr], low[ch]);
                if (low[ch] > disc[vr]) {
                    ans.push_back({vr, ch});
                }
            }
            else if (ch != parent[vr]) {
                low[vr] = min(low[vr], disc[ch]);
            }
        }
    }
    vector<pair<int, int>> findBridges() {
        vector<bool> visited(V + 1, false);
        vector<int> disc(V + 1, -1);
        vector<int> low(V + 1, -1);
        vector<int> parent(V + 1, -1);
        vector<pair<int, int>> ans;
        for (int i = 1; i <= V; i++) {
            if (!visited[i]) {
                bridgeUtil(i, visited, disc, low, parent, ans);
            }
        }
        return ans;
    }

    void articulationPointUtil(int u, vector<bool> &visited, vector<int> &disc, vector<int> &low, vector<int> &parent, vector<bool> &ap) {
        static int time = 0;
        int children = 0;
        visited[u] = true;
        disc[u] = low[u] = ++time;

        for (int v : adj[u]) {
            if (!visited[v]) {
                children++;
                parent[v] = u;
                articulationPointUtil(v, visited, disc, low, parent, ap);
                low[u] = min(low[u], low[v]);
                if (parent[u] == -1 && children > 1)
                    ap[u] = true;
                if (parent[u] != -1 && low[v] >= disc[u])
                    ap[u] = true;
            }
            else if (v != parent[u]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    vector<bool> findArticulationPoints() {
        vector<bool> visited(V + 1, false);
        vector<int> disc(V + 1, -1);
        vector<int> low(V + 1, -1);
        vector<int> parent(V + 1, -1);
        vector<bool> ap(V + 1, false);
        vector<int> ans;
        for (int i = 1; i <= V; i++) {
            if (!visited[i]) {
                articulationPointUtil(i, visited, disc, low, parent, ap);
            }
        }

        return ap;
    }

    void fillOrder(int v, vector<bool> &visited, stack<int> &Stack) // topological sort stores in stack
    {
        visited[v] = true;
        for (int u : adj[v]) {
            if (!visited[u]) {
                fillOrder(u, visited, Stack);
            }
        }
        Stack.push(v);
    }

    void dfsrev(int v, vector<bool> &visited, vector<int> &result) {
        visited[v] = true;
        result.push_back(v);
        for (int u : adjrev[v]) {
            if (!visited[u]) {
                dfsrev(u, visited, result);
            }
        }
    }

    vector<vector<int>> findSCCs() {
        stack<int> Stack;
        vector<bool> visited(V + 1, false);
        vector<vector<int>> ans;
        for (int i = 1; i <= V; i++) {
            if (!visited[i]) {
                fillOrder(i, visited, Stack);
            }
        }
        fill(visited.begin(), visited.end(), false);

        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();
            if (!visited[v]) {
                vector<int> scc;
                dfsrev(v, visited, scc);
                ans.push_back(scc);
            }
        }
        return ans;
    }
    bool bipartite(int source) {
        queue<int> q;
        q.push(source);
        vector<int> col(V + 1, -1);
        col[source] = 0;
        while (q.empty() == 0) {
            int u = q.front();
            q.pop();
            for (auto it : adj[u]) {
                if (col[it] == -1) {
                    col[it] = 1 - col[u];
                    q.push(it);
                }
                else if (col[it] == col[u]) {
                    return 0;
                }
            }
        }
        return 1;
    }
    void SCCUtil(int u, vector<int> &disc, vector<int> &low, stack<int> &st, vector<bool> &stackMember) {
        static int time = 0;

        // Initialize discovery time and low value
        disc[u] = low[u] = ++time;
        st.push(u);
        stackMember[u] = true;

        // Go through all vertices adjacent to this
        for (int v : adj[u]) {
            // If v is not visited yet, then recur for it
            if (disc[v] == -1) {
                SCCUtil(v, disc, low, st, stackMember);

                // Check if the subtree rooted at v has a connection back to one of the ancestors of u
                low[u] = min(low[u], low[v]);
            }
            else if (stackMember[v]) {
                // Update low value of u for parent function calls
                low[u] = min(low[u], disc[v]);
            }
        }

        // Head node found, pop the stack and print an SCC
        if (low[u] == disc[u]) {
            while (st.top() != u) {
                int w = st.top();
                cout << w << " ";
                stackMember[w] = false;
                st.pop();
            }
            cout << st.top() << "\n";
            stackMember[st.top()] = false;
            st.pop();
        }
    }
    void SCC() {
        vector<int> disc(V, -1);
        vector<int> low(V, -1);
        vector<bool> stackMember(V, false);
        stack<int> st;
        for (int i = 0; i < V; i++) {
            if (disc[i] == -1) {
                SCCUtil(i, disc, low, st, stackMember);
            }
        }
    }
};
