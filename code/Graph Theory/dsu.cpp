struct DSU {
    vector<ll> par, rank, sz;
    int n;
    DSU(int n) : n(n), par(n + 1), rank(n + 1, 0), sz(n + 1, 1) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int v) {
        return (par[v] == v ? v : (par[v] = find(par[v])));
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
    int get_size(int v) {
        return sz[find(v)];
    }
    int count() {
        return n; 
    }
    void join(int u, int v) {
        u = find(u);
        v = find(v);
        n--;
        if (rank[v] > rank[u]) swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
        if (rank[u] == rank[v]) rank[u]++;
        // u is the parent;
    }
};
