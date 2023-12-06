#include <bits/stdc++.h>
using namespace std;
#define FAST  ios_base::sync_with_stdio(0); cin.tie(0);
typedef long long int ll;
const int MAX = 10000;
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
int main() 
{

    return 0;
} 