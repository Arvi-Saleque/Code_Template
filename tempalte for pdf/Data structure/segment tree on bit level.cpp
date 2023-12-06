#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
class SegTlazy
{
public:
    #define lc (nd << 1)
    #define rc (lc | 1)
    #define MAX_BIT 25
    struct node
    {
        int bitCount[MAX_BIT];
        node () {
            memset(bitCount, 0, sizeof(bitCount));
        }
    };
    vector<int> a, lazy;
    //vector<ll> lazy;
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
        for(int k = 0; k < MAX_BIT; k++) {
            ND.bitCount[k] = L.bitCount[k] + R.bitCount[k];
        }
    } 
    void push(int nd, int b, int e) {
        if(lazy[nd] == 0) return;
        int nodes = e - b + 1;
        for(int k = 0; k < MAX_BIT; k++) {
            if(lazy[nd] & (1 << k)) {
                t[nd].bitCount[k] = nodes - t[nd].bitCount[k];
            }
        }
        if(b != e) {
            lazy[lc] ^= lazy[nd];
            lazy[rc] ^= lazy[nd];
        }
        lazy[nd] = 0;
    }
    void build(int nd, int b, int e) {
        lazy[nd] = 0;
        if(b == e) {
            for(int k = 0; k < MAX_BIT; k++) {
                if(a[b] & (1 << k)) {
                    t[nd].bitCount[k]++;
                }
            }
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
        if(j < b || e < i) {
            node res;
            memset(res.bitCount, 0, sizeof (res.bitCount));
            return res;
        }
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
void solve() {
    int n;
    cin >> n;
    SegTlazy A(n);
    A.takeInput();
    int m; cin >> m;
    while(m--) {
        int ty; cin >> ty;
        if(ty == 1) {
            int l, r;
            cin >> l >> r;
            auto ans = A.query(1, 1, n, l, r);
            ll res = 0;
            for(int k = 0; k < MAX_BIT; k++) {
                res += (1LL * ans.bitCount[k] * (1 << k));
            }
            cout << res << "\n";
        }
        else {
            int l, r, x;
            cin >> l >> r >> x;
            A.upd(1, 1, n, l, r, x);
        }
    }
}   
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    //cin >> t;
    while(t--) {
        //cout << "Case " << cs++ << ":\n";
        solve();
    }
    return 0;
}