#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
class basicSegT 
{
public:
    struct node
    {
        int l_v, l_v_c, r_v, r_v_c, sz;
        node() {};
        node (int a,int b,int c,int d,int e) {
            l_v = a;
            l_v_c = b;
            r_v = c;
            r_v_c = d;
            sz = e;
        }
        node (int v) {
            l_v = l_v_c = r_v = r_v_c = sz = v;
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
        if(L.l_v == -1) ND = R;
        if(R.l_v == -1) ND = L;
        ND.l_v = L.l_v;
        ND.l_v_c = L.l_v_c;
        if(L.l_v == R.l_v) {
            ND.l_v_c += R.l_v_c;
        }
        ND.r_v = R.r_v;
        ND.r_v_c = R.r_v_c;
        if(R.r_v == L.r_v) {
            ND.r_v_c += L.r_v_c;
        }
        ND.sz = max(L.sz, R.sz);
        if(L.r_v == R.l_v) {
            ND.sz = max(ND.sz, L.r_v_c+R.l_v_c);
        }
    } 
    void build(int nd,int b,int e) {
        if(b == e) {
            t[nd].l_v = t[nd].r_v = a[b];
            t[nd].l_v_c = t[nd].r_v_c = t[nd].sz = 1;
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
            
            return; 
        }
        int mid = b + e >> 1, l = nd << 1, r = l | 1;
        upd(l,b,mid,pos,x);
        upd(r,mid+1,e,pos,x);
        merge(t[nd], t[l], t[r]);
    }
    node query(int nd,int b,int e,int i,int j) {
        if(j < b || e < i) return {-1,-1,-1,-1,-1};
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
    int n, c, q;
    cin >> n >> c >> q;
    basicSegT A(n);
    A.takeInput();
    while(q--) {
        int i, j;
        cin >> i >> j;
        auto ans = A.query(1, 1, n, i, j);
        cout << ans.sz << "\n";
    }
}   
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    cin >> t;
    while(t--) {
        cout << "Case " << cs++ << ":\n";
        solve();
    }
    return 0;
}