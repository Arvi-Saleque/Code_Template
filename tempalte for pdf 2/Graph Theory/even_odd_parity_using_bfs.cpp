// problem link: https://codeforces.com/problemset/problem/1272/E

int a[N+5], dis[N+5], ans[N+5];
vector<int> graph[N+5];
void bfs(vector<int> &src,int n) {
    for(int i=1;i<=n;i++) {
        dis[i] = inf;
    }
    queue<int> Q;
    for(auto x : src) {
        Q.push(x);
        dis[x] = 0;
    }
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for(auto v : graph[u]) {
            if(dis[v] == inf) {
                dis[v] = dis[u] + 1;
                Q.push(v);
            }
        }
    }
}
void solve() {
    int n;
    cin >> n;
    vector<int> ev, odd;
    for(int i=1;i<=n;i++) {
        cin >> a[i];
        int left = i - a[i], right = i + a[i];
        if(left >= 1) {
            graph[left].push_back(i);
        }
        if(right <= n) {
            graph[right].push_back(i);
        }
        if(a[i] & 1) odd.push_back(i);
        else ev.push_back(i);
    }
    for(int i=1;i<=n;i++) {
        ans[i] = inf;
    }
    bfs(ev, n);
    for(auto x : odd) {
        ans[x] = dis[x];
    }
    bfs(odd, n);
    for(auto x : ev) {
        ans[x] = dis[x];
    }
    for(int i=1;i<=n;i++) {
        if(ans[i] == inf) cout << "-1 ";
        else cout << ans[i] << " ";
    }
}  