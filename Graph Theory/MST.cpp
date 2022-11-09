#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MAX = 10000;
int par[MAX+10];
struct Edge
{
    int u,v,cost;
    Edge () {};
    Edge(int _u,int _v,int _cost)
    {
        u = _u;
        v = _v;
        cost = _cost;
    };
};
bool isLess(Edge a, Edge b)
{
    return a.cost < b.cost;
}
int findParent(int u)
{
    if(par[u] == u) return u;
    return par[u] = findParent(par[u]);
}
void join(int u,int v)
{
    int parU = findParent(u);
    int parV = findParent(v);
    par[parU] = parV;
}
ll findTheMST(vector<Edge> &edges)
{
    sort(edges.begin(),edges.end(),isLess);
    ll res = 0;
    for(auto &node : edges)
    {
        int parU = findParent(node.u);
        int ParV = findParent(node.v);
        if(parU != ParV)
        {
            res += node.cost;
            join(node.u,node.v);
        }
    }
    return res;
}
int main() 
{
    int n,m;
    scanf("%d %d",&n,&m);
    vector<Edge> edges;
    for(int i=1;i<=n;i++)
    {
        par[i] = i;
    }
    while(m--)
    {
        int a,b,cost;
        scanf("%d %d %d",&a,&b,&cost);
        edges.push_back({a,b,cost});
    }
    cout << findTheMST(edges) << "\n";
    return 0;
}