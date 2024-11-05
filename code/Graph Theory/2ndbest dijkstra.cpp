#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int N = 5e3 + 9;
vector<vector<pair<int, int>>>  adj;
pair<ll, ll> dis[N + 2];
void bfs() {
    queue<pair<int, int>> Q;
    Q.push({1, 0});
    dis[1].first = 0;
    while(!Q.empty()) {
        auto [pn, pw] = Q.front();
        Q.pop();
        for(auto [w, v] : adj[pn]) {
            //cout << v << " " << w << "\n";
            //cout << dis[v].second << " " << (pw + w) << "\n"; 
            if(dis[v].second > (pw + w)) {
                if(dis[v].first > (pw + w)) {
                    dis[v].second = dis[v].first;
                    dis[v].first = (pw + w);
                    Q.push({v, pw + w});
                }
                else if(dis[v].first != (pw + w)) {
                    dis[v].second = (pw + w);
                    Q.push({v, pw + w});
                }
            }
        }
    }
}
void solve() {  
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n + 1; i++) {
        dis[i].first = dis[i].second = 1e15; 
    }
    adj.assign(n + 1, {});
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }
    bfs();
    cout << dis[n].second << "\n";
}   
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1, cs = 1;
    cin >> t; 
    while(t--) {
        cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}