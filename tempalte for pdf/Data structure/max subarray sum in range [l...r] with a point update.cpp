#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
class basicSegT 
{
public:
    const int inf = 1e9;
    struct node
    {
        int max_sub, pre_sum, suf_sum, tot_sum;
        node() {};
        node(int _ms, int _ps, int _ss, int _ts) {
            max_sub = _ms;
            pre_sum = _ps;
            suf_sum = _ss;
            tot_sum = _ts;
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
    void merge(node &nd, node l, node r) {
        if(l.tot_sum == inf) {
            nd = r;
            return;
        }
        if(r.tot_sum == inf) {
            nd = l;
            return;
        }
        nd.max_sub = max({l.max_sub, r.max_sub, l.suf_sum + r.pre_sum});
        nd.pre_sum = max(l.pre_sum, l.tot_sum + r.pre_sum);
        nd.suf_sum = max(r.suf_sum, r.tot_sum + l.suf_sum);
        nd.tot_sum = l.tot_sum + r.tot_sum;
    } 
    void build(int nd,int b,int e) {
        if(b == e) {
            t[nd].max_sub = t[nd].suf_sum = t[nd].pre_sum = t[nd].tot_sum = a[b];
            return;
        }
        int mid = b + e >> 1, l = nd << 1, r = l | 1;
        build(l,b,mid);
        build(r,mid+1,e);
        merge(t[nd], t[l], t[r]);
    } 
    void upd(int nd,int b,int e,int pos,int x) {
        if(pos < b || e < pos) return;
        if(b == pos && b == e) {
             t[nd].max_sub = t[nd].suf_sum = t[nd].pre_sum = t[nd].tot_sum = x;
            return; 
        }
        int mid = b + e >> 1, l = nd << 1, r = l | 1;
        upd(l,b,mid,pos,x);
        upd(r,mid+1,e,pos,x);
        merge(t[nd], t[l], t[r]);
    }
    node query(int nd,int b,int e,int i,int j) {
        if(j < b || e < i) return {inf,inf,inf,inf};
        if(i <= b && e <= j) return t[nd];
        int mid = (b+e) >> 1, l = nd << 1, r = l | 1;
        auto left = query(l,b,mid,i,j);
        auto right = query(r,mid+1,e,i,j);
        node res;
        merge(res, left, right);
        return res;
    }
};
void solve() {
    int n; cin >> n;
    basicSegT A(n);
    A.takeInput();
    int q; cin >> q;
    while(q--) {
        int ty; cin >> ty;
        if(ty == 0) {
            int i, x; cin >> i >> x;
            A.upd(1, 1, n, i, x);
        }
        else {
            int l, r; cin >> l >> r;
            cout << A.query(1, 1, n, l, r).max_sub << "\n";
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