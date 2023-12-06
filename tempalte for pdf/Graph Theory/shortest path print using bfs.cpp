const int N = 1e5 + 9;
const int inf = (1 << 30);
vector<int> graph[N+5];
void solve() {
    int n, m;
    cin >> n >> m;
    while(m--) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    vector<int> dis(n+1, -1);
    vector<int> par(n+1, 0);
    dis[1] = 0;
    par[1] = -1;
    queue<int> Q;
    Q.push(1);
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for(auto x : graph[u]) {
            if(dis[x] == -1) {
                dis[x] = dis[u] + 1;
                par[x] = u;
                Q.push(x);
            }
        }
    }
    if(dis[n] == -1) {
        cout << "IMPOSSIBLE\n";
        return; 
    }
    else {
        vector<int> ans;
        int child = n;
        while(child != -1) {
            ans.push_back(child);
            child = par[child];
        }
        reverse(ans.begin(), ans.end());
        cout << ans.size() << "\n";
        for(auto x : ans) {
            cout << x << " ";
        }
    }
} 