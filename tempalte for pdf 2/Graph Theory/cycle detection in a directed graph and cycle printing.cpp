vector<int> g[N+5];
int vis[N+5], par_arr[N+5];
void dfs(int u,bool &status,int &node)
{
    if(status) return;
    vis[u] = 1;
    for(auto v : g[u]) {
        if(vis[v]==0) {
            par_arr[v] = u;
            dfs(v,status,node);
            if(status) return;
        }
        if(vis[v]==1) {
            status = true; // cycle detected
            node = v;
            par_arr[v] = u;
            return;
        }      
    }
    vis[u] = 2;
}
void solve() {
    int n, m;
    cin >> n >> m;
    for(int i=1;i<=m;i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }
    bool ok = false;
    int node;
    for(int i=1;i<=n;i++) {
        if(!vis[i]) {
            dfs(i, ok, node);
        }
        if(ok) break;
    }
    if(!ok) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        vector<int> ans;
        ans.push_back(node);
        int child = par_arr[node];
        while(child != node) {
            ans.push_back(child);
            child = par_arr[child];
        }
        ans.push_back(node);
        reverse(ans.begin(), ans.end());
        cout << ans.size() << "\n";
        for(auto x : ans) {
            cout << x << " ";
        }
    }
}