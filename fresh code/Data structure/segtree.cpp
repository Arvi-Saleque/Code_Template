// must filled what leafs hold
// make sure node() what return when out of bounds

class SegTlazy {
public:
    #define lc (nd << 1)
    #define rc (lc | 1)
    #define MAX_BIT 25
    struct node {
        ll lazy, mn, mncnt;
        bool haslazy;
        node() {
            mncnt = lazy = 0;
            haslazy = 0;
            mn = 1e18;
        };
        node(ll _m, ll _mc) : mn(_m), mncnt(_mc), lazy(0), haslazy(0) {}
    };   
    struct node {
        int bitCount[MAX_BIT];
    };
    vector<ll> a;
    vector<node> t;
    int n; 
    SegTlazy() {
        n = 0;
        a.clear();
        t.clear();
    }
    SegTlazy(int n) {
        this -> n = n;
        a1.resize(n + 1, 0);
        a2.resize(n + 1, 0);
        t.resize(4*n + 1, node());
    }
    void takeInput() {
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        build(1, 1, n);
    }
    // merge sort tree
    void merge(node &ND, node L, node R) {
        int l = 0, r = 0;
        while(l < L.vec.size() && r < R.vec.size()) {
            if(L.vec[l] <= R.vec[r]) {
                ND.vec.push_back(L.vec[l++]);
            }
            else {
                ND.vec.push_back(R.vec[r++]);
            }
        }
        while(l < L.vec.size()) {
            ND.vec.push_back(L.vec[l++]);
        }
        while(r < R.vec.size()) {
            ND.vec.push_back(R.vec[r++]);
        }
    }
    // sub array sum
    void merge(node &nd, node l, node r) {
        if(l.tot_sum == inf) {
            nd = r;
            return;
        }
        if(r.tot_sum == inf) {
            nd = l;
            return;
        }
        nd.max_sub = max({l.max_sub, r.max_sub, 
            l.suf_sum + r.pre_sum});
        nd.pre_sum = max(l.pre_sum, l.tot_sum + 
            r.pre_sum);
        nd.suf_sum = max(r.suf_sum, r.tot_sum + 
            l.suf_sum);
        nd.tot_sum = l.tot_sum + r.tot_sum;
    }
    void apply(int nd, int b, int e, int lazy) {
        t[nd].mn += t[nd].lazy;
        int nodes = e-b+1;
        for(int k=0;k<MAX_BIT;k++) {
            if(lazy[nd] & (1 << k)) {
                t[nd].bitCount[k] = nodes - t[nd].bitCount[k];
            }
        }
        // addition and min/max 
        t[nd] += lazy[nd];
        lazy[l] += lazy[nd];
        // multiplication and sum
        t[nd] = (t[nd] * lazy[nd]) % MOD;
        lazy[l] = (lazy[l] * lazy[nd]) % MOD;
        // addition and sum
        t[nd].val = t[nd].val + (1LL * (e - b + 1) * lazy[nd]);
        lazy[l] += lazy[nd];
        // assignment and min/max
        t[nd] = lazy[nd];
        lazy[l] = lazy[nd];
        // assignment and sum
        t[nd] = (1LL*(e-b+1) * lazy[nd]);
        lazy[l] = lazy[nd];
        // arithamatic progression
        t[nd].mn += lazy[nd]; t[nd].mx += lazy[nd];
    }
    void push(int nd, int b, int e) {
        if(!t[nd].haslazy) return;
        apply(nd, b, e, t[nd].lazy);
        if(b != e) {
            t[lc].lazy += t[nd].lazy; t[lc].haslazy = 1;
            t[rc].lazy += t[nd].lazy; t[rc].haslazy = 1;
        }
        t[nd].lazy = 0;
        t[nd].haslazy = 0;
    }
    void upd(int nd, int b, int e, int i, int j, ll v) {
        push(nd, b, e);
        if(j < b || e < i) return;
        // arithmatic
        if(i <= b && e <= j) {
            lazy[nd] += v;
            t[nd].hasLazy = true;
            push(nd, b, e);
            return;
        }
        int mid = b + e >> 1;
        upd(lc, b, mid, i, j, v);
        upd(rc, mid + 1, e, i, j, v);
        merge(t[nd], t[lc], t[rc]);
    }
    void build(int nd, int b, int e) {
        if(b == e) {
            t[nd] = node(0, 1);
            return;
        }
        int mid = b + e >> 1;
        build(lc, b, mid);
        build(rc, mid + 1, e);
        merge(t[nd], t[lc], t[rc]);
    }
    node query(int nd, int b, int e, int i, int j) {
        push(nd, b, e);
        if(j < b || e < i) return 0;
        if(i <= b && e <= j) {
            return t[nd];
        }
        int mid = b + e >> 1;
        auto left = query(lc, b, mid, i, j);
        auto right = query(rc, mid + 1, e, i, j);
        node res;
        merge(res, left, right);
        return res;
    }
    // merge sort tree
    int query(int nd,int b,int e,int i,int j, int k) {
        if(j < b || e < i) {
            return 0;
        }
        if(i <= b && e <= j) {
            return lower_bound(t[nd].vec.begin(), 
                t[nd].vec.end(), k) - t[nd].vec.begin();
        }
        int mid = (b+e) >> 1;
        return query(lc, b, mid, i, j, k) + 
        query(rc, mid+1, e, i, j, k);
    }
};

// arithmatic progression
tree.upd(1, 1, n, l, l, a);
if(l + 1 <= r) tree.upd(1, 1, n, l + 1, r, d);
if(r + 1 <= n) tree.upd(1, 1, n, r + 1, r + 1, -(a + 1LL * (r - l) * d));

vector<pair<int, int>> vec;
node(vector<pair<int, int>> v) {
    vec.swap(v);
    int mn = 1e9;
    for(auto &p: vec){
        mn = min(mn, p.second);
        p.second = mn;
    }
}
void merge(node &ND, node &L, node &R) {
    if(L.vec.empty()) {ND = R; return;}
    if(R.vec.empty()) {ND = L; return;}
    ND.vec.clear();
    int l = 0, r = 0, mn = 1e9;
    while(l<L.vec.size() || r<R.vec.size()){
        pair<int,int> cur;
        if(r==R.vec.size() || (l<L.vec.size() && L.vec[l].first<=R.vec[r].first))
            cur = L.vec[l++];
        else cur = R.vec[r++];
        mn = min(mn, cur.second);
        ND.vec.push_back({cur.first, mn});                           
    }
}
void build(int nd, int b, int e) {
    if(b == e) {
        t[nd].vec.push_back({b + a[b] - 1, a[b]});
        return;
    }
    int mid = (b + e) >> 1;
    build(lc, b, mid);
    build(rc, mid + 1, e);
    merge(t[nd], t[lc], t[rc]);
}
int query(int nd, int b, int e, int i, int j, int k){         
    if(j < b || e < i) return 1e9;
    if(i <= b && e <= j) {
        auto &v = t[nd].vec;
        if(v.empty() || v.front().first > k) return 1e9;
        int cnt = upper_bound(v.begin(), v.end(), k, [](int val, pair<int, int> &p){
            return (val < p.first);
        }) - v.begin();
        return v[cnt - 1].second;
    }              
    int mid = b + e >> 1;
    return min(query(lc, b, mid, i, j, k), query(rc, mid + 1, e, i, j, k));
}


