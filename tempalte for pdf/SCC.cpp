#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MAX = 1000000;
vector<int> gr[MAX+10], rgr[MAX+10];
bool vis[MAX+10];
void dfs(int u, stack<int> &nd)
{
    vis[u] = 1;
    for(auto x : gr[u])
    {
        if(!vis[x])
        {
            dfs(x,nd);
        }
    }
    nd.push(u);
}
void dfs2(int u)
{
    vis[u] = 1;
    for(auto x : rgr[u])
    {
        if(!vis[x])
        {
            dfs2(x);
        }
    }
}
void findThescc(vector<vector<int>> &vec,int n)
{
    stack<int> nodes;
    dfs(1,nodes);
    memset(vis,0,sizeof vis);
    vector<int> tmp_vec;
    while(!nodes.empty())
    {
        auto par = nodes.top();
        nodes.pop();
        if(!vis[par])
        {
            if(tmp_vec.size() != 0) vec.push_back(tmp_vec);
            tmp_vec.clear();
            dfs2(par);
            tmp_vec.push_back(par);
        }
        else 
        {
            tmp_vec.push_back(par);
        }
    }
    if(tmp_vec.size()>0) vec.push_back(tmp_vec);
}
int main() 
{
    int n, m;
    scanf("%d %d",&n,&m);
    while(m--)
    {
        int a,b;
        scanf("%d %d",&a,&b);
        gr[a].push_back(b);
        rgr[b].push_back(a);
    }
    vector<vector<int>> nodes_of_scc;
    findThescc(nodes_of_scc,n);

    cout << "Number Of SCC : " << nodes_of_scc.size() << "\n";
    int cnt = 1;
    for(auto x : nodes_of_scc)
    {
        cout << "SCC " << cnt++ << " :";
        for(auto node : x)
        {
            cout << node << " ";
        }
        cout << "\n";
    }
    return 0;
}