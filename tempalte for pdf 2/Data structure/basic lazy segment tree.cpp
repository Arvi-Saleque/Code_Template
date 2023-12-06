class SegTlazy
{
public:
    #define lc (nd << 1)
    #define rc (lc | 1)
    struct node
    {
        ll val;
        node() {
            val = 0;
        };
        node (ll v) {
            val = v;
        }
    };
    vector<int> a;
    vector<ll> lazy;
    vector<node> t;
    int n;
    SegTlazy() {
        a.clear();
        t.clear();
        lazy.clear();
        n = 0;
    }   
    SegTlazy(int n) {
        this -> n = n;
        a.resize(n + 1, 0);
        t.resize(4*n + 1, node());
        lazy.resize(4*n + 1, 0);
    }
    void takeInput() {
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        build(1, 1, n);
    }
    inline void merge(node &ND, node L, node R) {
        ND.val = L.val + R.val;
    } 
    void push(int nd, int b, int e) {
        if(lazy[nd] == 0) return;
        t[nd].val = t[nd].val + (1LL * (e - b + 1) * lazy[nd]);
        if(b != e) {
            lazy[lc] += lazy[nd];
            lazy[rc] += lazy[nd];
        }
        lazy[nd] = 0;
    }
    void build(int nd, int b, int e) {
        lazy[nd] = 0;
        if(b == e) {
            t[nd].val = a[b];
            return;
        }
        int mid = b + e >> 1;
        build(lc, b, mid);
        build(rc, mid + 1, e);
        merge(t[nd], t[lc], t[rc]);
    }
    void upd(int nd, int b, int e, int i, int j, ll v) {
        push(nd, b, e);
        if(j < b || e < i) return;
        if(i <= b && e <= j) {
            lazy[nd] = v;
            push(nd, b, e);
            return;
        }
        int mid = b + e >> 1;
        upd(lc, b, mid, i, j, v);
        upd(rc, mid + 1, e, i, j, v);
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
};