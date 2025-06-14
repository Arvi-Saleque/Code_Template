class SegTlazy {
public:
    struct node {
        ll mn, mx, lazy;
        node *l, *r;      
        node() : mn(0), mx(0), lazy(0), l(nullptr), r(nullptr) {}
        node(ll mn, ll mx) : mn(mn), mx(mx), lazy(0), l(nullptr), r(nullptr) {}
    };
 
    node *root; 
    ll n;      
 
    explicit SegTlazy(ll _n) : n(_n) { root = new node(); }
    inline void merge(node *nd) {
        nd->mn = min(nd->l ? nd->l->mn : 0LL,
                          nd->r ? nd->r->mn : 0LL);
        nd->mx = max(nd->l ? nd->l->mx : 0LL,
                          nd->r ? nd->r->mx : 0LL);
    }
    inline void push(node *nd, ll b, ll e) {
        if (!nd || nd->lazy == 0) return;
        if (b != e) {    
            if (!nd->l) nd->l = new node();
            if (!nd->r) nd->r = new node();
            nd->l->lazy += nd->lazy;
            nd->r->lazy += nd->lazy;
            nd->l->mn   += nd->lazy;
            nd->l->mx   += nd->lazy;
            nd->r->mn   += nd->lazy;
            nd->r->mx   += nd->lazy;
        }
        nd->lazy = 0;
    }
    
    void upd(node *nd, ll b, ll e, ll i, ll j, ll v) {
        if (j < b || e < i) return;        // no overlap
        if (i <= b && e <= j) {            // fully inside
            nd->lazy += v;
            nd->mn   += v;
            nd->mx   += v;
            return;
        }
        push(nd, b, e);
        ll mid = (b + e) >> 1;
        if (!nd->l) nd->l = new node();
        if (!nd->r) nd->r = new node();
        upd(nd->l, b, mid, i, j, v);
        upd(nd->r, mid + 1, e, i, j, v);
        merge(nd);
    }
    
    void upd(ll l, ll r, ll v) { upd(root, 1, n, l, r, v); }
    node query(node *nd, ll b, ll e, ll i, ll j) {
        if (j < b || e < i) return node(inf, -inf);      // neutral (mn big, mx small)
        if(!nd) return node();
        if (i <= b && e <= j) return *nd;
        push(nd, b, e);
        ll mid = (b + e) >> 1;
        node left  = query(nd->l, b, mid, i, j);
        node right = query(nd->r, mid + 1, e, i, j);
        node res;
        res.mn = min(left.mn, right.mn);
        res.mx = max(left.mx, right.mx);
        return res;
    }
    node query(ll l, ll r) { return query(root, 1, n, l, r); }
};
