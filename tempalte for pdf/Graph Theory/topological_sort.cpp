vector<int> g[N+5];
bool vis[N+5];
int color[N+5];
void dfs(int u,stack<int> &stck) {
    vis[u] = 1;
    for(auto x : g[u]) {
        if(!vis[x]) {
            dfs(x, stck);
        }
    }
    stck.push(u);
}
void check_cycle(int u,bool &ok) {
    if(ok) return;
    color[u] = 1;
    for(auto v : g[u]) {
        if(color[v] == 0) {
            check_cycle(v, ok);
            if(ok) return;
        }
        if(color[v] == 1) {
            ok = true;
            return;
        }
    }
    color[u] = 2;
}
void solve() {
    int n, m;
    cin >> n >> m;
    for(int i=1;i<=m;i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
    bool ok = false;
    for(int i=1;i<=n;i++) {
        if(color[i] == 0) {
            check_cycle(i, ok);
            if(ok) break;
        }
    }
    if(ok) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    stack<int> ans;
    for(int i=1;i<=n;i++) {
        if(!vis[i]) {
            dfs(i, ans);
        }
    }
    while(!ans.empty()) {   
        if(ans.size() == 1) cout << ans.top() << "\n";
        else cout << ans.top() << " ";
        ans.pop();
    }
}  