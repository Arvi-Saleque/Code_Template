/*
There is a tree with N vertices numbered 1,2,3....N.
Taro has decided to paint each vertex in white or black. 
Here, it is not allowed to paint two adjacent vertices both in black.

Input : 
3
1 2
2 3
Output : 5
Explanation : 
1(w)-2(w)-3(w)
1(b)-2(w)-3(w)
1(w)-2(b)-3(w)
1(w)-2(w)-3(b)
1(b)-2(w)-3(b)
*/

const int N = 2e5 + 9;
const int inf = (1 << 30);
const int MOD = 1000000007;
enum colors {black=1, white};
vector<int> g[N+5];
int color[N+5];
int dp[N+5][3];
int dfs(int u,int color,int p) {
    int &ans = dp[u][color];
    if(ans != -1) return ans;
    ans = 1;
    for(auto v : g[u]) {
        if(v != p) {
            if(color == black) {
                ans = (1LL * ans * dfs(v, white, u)) % MOD;
            }
            else {
                int val1 = dfs(v, white, u);
                int val2 = dfs(v, black, u);
                ans = (1LL * ans * (val1 + val2)) % MOD;
            }
        }
    }
    return ans;
}
void solve() {
    int n;
    cin >> n;
    for(int i=1;i<n;i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    memset(dp, -1, sizeof dp);
    int ans = 0;
    ans = (ans + dfs(1, black, 0)) % MOD;
    ans = (ans + dfs(1, white, 0)) % MOD;
    cout << ans << "\n";
}