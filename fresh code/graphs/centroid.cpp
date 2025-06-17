struct CentroidTree {
    int n;                              // Number of nodes in the original tree
    vector<int> adj[MX];                // Original tree adjacency list
    vector<int> ctree[MX];              // Centroid tree adjacency list (optional)
    int subsize[MX];                    // Subtree sizes
    bool blocked[MX];                   // Marks centroided (used) nodes
    int cpar[MX];                       // Parent in centroid tree

    CentroidTree(int nodes) : n(nodes) {
        for (int i = 0; i < n; ++i) {
            adj[i].clear();
            ctree[i].clear();
            subsize[i] = 0;
            blocked[i] = false;
            cpar[i] = -1;
        }
    }

    // Adds an undirected edge to the original tree
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Computes subtree sizes
    void calculate_size(int u, int par) {
        subsize[u] = 1;
        for (int v : adj[u]) {
            if (v != par && !blocked[v]) {
                calculate_size(v, u);
                subsize[u] += subsize[v];
            }
        }
    }

    // Finds the centroid of a subtree
    int get_centroid(int u, int par, int size) {
        for (int v : adj[u]) {
            if (v != par && !blocked[v]) {
                if (subsize[v] > size / 2) {
                    return get_centroid(v, u, size);
                }
            }
        }
        return u;
    }

    // Recursively decomposes the tree
    void decompose(int u, int parent) {
        calculate_size(u, -1);
        int centroid = get_centroid(u, -1, subsize[u]);
        blocked[centroid] = true;
        cpar[centroid] = parent;
        if (parent != -1) {
            ctree[parent].push_back(centroid);
            ctree[centroid].push_back(parent);
        }
        for (int v : adj[centroid]) {
            if (!blocked[v]) {
                decompose(v, centroid);
            }
        }
    }

    // Optional: get centroid parent
    int get_centroid_parent(int u) {
        return cpar[u];
    }

    // Optional: get centroid children
    vector<int>& get_centroid_children(int u) {
        return ctree[u];
    }
};
