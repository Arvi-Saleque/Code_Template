#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
class basicSegT 
{
public:
    #define lc (nd << 1)
    #define rc (lc | 1)
    struct node
    {
        ll val;
        node() {
            val = 0;
        }
        node(ll v) {
            val = v;
        }
    };
    vector<int> a;
    vector<node> t;
    int n;
    basicSegT() {
        a.clear();
        t.clear();
        n = 0;
    }   
    basicSegT(int n) {
        this -> n = n;
        a.resize(n + 1, 0);
        t.resize(4*n + 1, node());
    }
    void takeInput() {
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        build(1, 1, n);
    }
    void merge(node &ND, node L, node R) {
        ND.val = L.val + R.val;
    } 
    void build(int nd,int b,int e) {
        if(b == e) {
            t[nd] = a[b];
            return;
        }
        int mid = b + e >> 1;
        build(lc, b, mid);
        build(rc, mid+1, e);
        merge(t[nd], t[lc], t[rc]);
    } 
    void upd(int nd,int b,int e,int pos,int x) {
        if(pos < b || e < pos) return;
        if(b == pos && b == e) {
            t[nd].val = x;
            return; 
        }
        int mid = b + e >> 1;
        upd(lc, b, mid, pos, x);
        upd(rc, mid+1, e, pos, x);
        merge(t[nd], t[lc], t[rc]);
    }
    node query(int nd,int b,int e,int i,int j) {
        if(j < b || e < i) return 0;
        if(i <= b && e <= j) return t[nd];
        int mid = (b+e) >> 1;
        auto left = query(lc, b, mid, i, j);
        auto right = query(rc, mid+1, e, i, j);
        node res;
        merge(res, left, right);
        return res;
    }
};
void solve() {
    int n,m;
    cin >> n >> m;
    basicSegT A(n);
    A.takeInput();
    while(m--) {
        int ty; cin >> ty;
        if(ty == 1) {
            int i, v; cin >> i >> v;
            A.upd(1, 1, n, i + 1, v);
        }
        else {
            int l, r; cin >> l >> r;
            auto res = A.query(1, 1, n, l+1, r);
            cout << res.val << "\n";
        }
    }
}   
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    //cin >> t;
    while(t--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}