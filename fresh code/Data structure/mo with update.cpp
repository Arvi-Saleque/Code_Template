vector<int> freq;

// change a[pos] = val;
// ans sum of L..R % 3

struct MOupd {
    int n, q, bl_sz;
    ll  sum = 0;
    vector<int> v;          // compressed array
    vector<ll>  ans;        // answers (1 … #queries)

    /* internals */
    struct Update { int pos, oldId, newId; };
    struct Q      { int l, r, idx, t; };      // t = updates done before it
    vector<Update> updates;
    vector<Q>      queries;
    vector<ll>     id2val;                    // decompress table
    MOupd(int N, int Qall) : n(N), q(Qall) {

        bl_sz = max(1, int(round(pow(n, 2.0/3.0))));

        vector<ll> raw(n);
        for (ll &x : raw) cin >> x; // array inputs

        struct Op { int tp, a; ll b; };
        vector<Op> ops(q);
        for (auto &o : ops) { cin >> o.tp >> o.a >> o.b; --o.a; }

        vector<ll> pool;
        for (ll x : raw) if (x % 3 == 0) pool.push_back(x);
        for (auto &o : ops) if (o.tp==0 && o.b%3==0) pool.push_back(o.b); // only updated value
        sort(pool.begin(), pool.end());
        pool.erase(unique(pool.begin(), pool.end()), pool.end());
        id2val   .assign(pool.size() + 1, 0);          // id 0 = "not kept"
        for (size_t i = 0; i < pool.size(); ++i) id2val[i+1] = pool[i];

        auto ID = [&](ll x)->int {                     // 0 ⇒ not counted
            if (x % 3) return 0;
            return int(lower_bound(pool.begin(), pool.end(), x) - pool.begin()) + 1;
        };

        v.resize(n);
        for (int i = 0; i < n; ++i) v[i] = ID(raw[i]);
        int t_cnt = 0;
        for (auto &o : ops) {
            if (o.tp == 0) {              // update
                int newId = ID(o.b);
                updates.push_back({o.a, 0, newId});   // oldId later
                ++t_cnt;
            } else {                      // query
                queries.push_back({o.a, int(o.b)-1,
                                   int(queries.size()), t_cnt});
            }
        }

        vector<int> tmp = v;
        for (auto &u : updates) { u.oldId = tmp[u.pos]; tmp[u.pos] = u.newId; }

        freq.assign(id2val.size() + 5, 0);
        ans .assign(queries.size() + 1, 0);
    }

    inline void add(int i) {
        ++freq[v[i]];
        if (v[i] && freq[v[i]] == 1) sum += id2val[v[i]];
    }
    inline void remove(int i) {
        --freq[v[i]];
        if (v[i] && freq[v[i]] == 0) sum -= id2val[v[i]];
    }
    void apply(int k, int L, int R) {
        const auto &u = updates[k];
        if (L <= u.pos && u.pos <= R) {
            if (u.oldId) { --freq[u.oldId]; if (!freq[u.oldId]) sum -= id2val[u.oldId]; }
            if (u.newId) { ++freq[u.newId]; if ( freq[u.newId]==1) sum += id2val[u.newId]; }
        }
        v[u.pos] = u.newId;
    }
    void undo(int k, int L, int R) {
        const auto &u = updates[k];
        if (L <= u.pos && u.pos <= R) {
            if (u.oldId) { ++freq[u.oldId]; if (freq[u.oldId]==1) sum += id2val[u.oldId]; }
            if (u.newId) { --freq[u.newId]; if (!freq[u.newId])  sum -= id2val[u.newId]; }
        }
        v[u.pos] = u.oldId;
    }

    void solve() {

        /* sort queries in 3-D Mo order */
        sort(queries.begin(), queries.end(), [&](const Q& A, const Q& B){
            int b1 = A.l / bl_sz, b2 = B.l / bl_sz;
            if (b1 != b2) return b1 < b2;
            int br1 = A.r / bl_sz, br2 = B.r / bl_sz;
            if (br1 != br2) return br1 < br2;
            return A.t < B.t;
        });

        int L = 0, R = -1, T = 0;
        for (const auto &q : queries) {

            while (T < q.t) apply(T++, L, R);
            while (T > q.t) undo(--T, L, R);

            while (L > q.l) add(--L);
            while (R < q.r) add(++R);
            while (L < q.l) remove(L++);
            while (R > q.r) remove(R--);

            ans[q.idx] = sum;
        }

        for (size_t i = 0; i < queries.size(); ++i)
            cout << ans[i] << '\n';
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    MOupd mo(N, Q);   // struct reads the rest of the input
    mo.solve();       // computes and prints
    return 0;
}
