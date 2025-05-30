// https://codeforces.com/problemset/problem/920/E

// if i need to clauclate connected componenet on reverse graph 
// means the edge are connected which are not present in the input
// so just simple as normal connected component

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 1e6 + 2, mod = 1000000007;
class DSU
{
public:
    vector<int> par, sz;
    DSU(int n) : par(n+1), sz(n+1)
    {
        for(int i=1;i<=n;i++)
        {
            par[i] = i;
            sz[i] = 1;
        }
    }
    int find_par(int u)
    {
        if(par[u] == u) return u;
        return par[u] = find_par(par[u]);
    }
    void join(int u,int v)
    {
        u = find_par(u);
        v = find_par(v);
        if(u != v)
        {
            if(sz[u] < sz[v]) swap(u,v); // make sure always sz(u) > sz(v)
            par[v] = u;
            sz[u] += sz[v];
        }
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n + 1);
    vector<set<int>> has(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        has[u].insert(v);
        has[v].insert(u);
    }
    set<int> all;
    for(int i = 1; i <= n; i++) {
        all.insert(i);
    }
    function<void(int)> dfs = [&](int u) {
        vector<int> tmp;
        for(auto v : all) {
            if(!has[u].count(v)) {
                tmp.push_back(v);
                dsu.join(u, v);
            }
        }
        for(auto x : tmp) {
            all.erase(x);
        }
        for(auto x : tmp) {
            dfs(x);
        }
    };
    while(!all.empty()) {
        int nd = *all.begin();
        all.erase(nd);
        dfs(nd);
    }
    set<int> st;
    for(int i = 1; i <= n; i++) {
        st.insert(dsu.find_par(i));
    }
    vector<int> ans;
    for(auto x : st) {
        ans.push_back(dsu.sz[x]);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(auto x : ans) {
        cout << x << " ";
    }
}   
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    //acin >> t;
    while(t--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}