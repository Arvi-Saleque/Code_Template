struct DSU {
    vector<int> par, sz;
    int cmp;

    DSU(int n) : par(n + 1), sz(n + 1, 1), cmp(n) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int v) {
        if (par[v] != v) {
            return find(par[v]);
        }
        return par[v];
    }

    bool join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) {
            return false;
        }
        if (sz[u] < sz[v]) {
            swap(u, v);
        }
        history.push_back({v, sz[v]});
        history.push_back({u, sz[u]});
        par[v] = u;
        sz[u] += sz[v];
        --cmp;

        return true;
    }

    void rollback() {
        auto [u, oldszU] = history.back();
        history.pop_back();
        auto [v, oldszV] = history.back();
        history.pop_back();
        par[v] = v;
        sz[u] = oldszU;
        sz[v] = oldszV;
        cmp++;
    }
};
