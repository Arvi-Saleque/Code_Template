/*
int curidx = i & 1;
int nextidx = curidx ^ 1;
dp[curidx] = dp[nextidx]; // automatically handle skip part
*/

void solve() {
    int n;
    cin >> n;
    vector<int> s(n), c(n);
    for(auto &x : s) cin >> x;
    for(auto &x : c) cin >> x;

    vector<vector<vector<ll>>> dp(2, vector<vector<ll>>(n + 1, vector<ll>(5, 1e18)));
    vector<vector<ll>> best(n + 1, vector<ll>(n + 1, 1e18));

    for(int i = 0; i < n; i++) {
        dp[0][i][4] = 0; 
        dp[1][i][4] = 0; 
    }    

    for(int i = n - 1; i >= 0; i--) {
        int curidx = i & 1;
        int nextidx = curidx ^ 1;
        dp[curidx] = dp[nextidx];
        for(int cur = 3; cur >= 2; cur--) {
            for(int last = 0; last < i; last++) {
                ll ans = dp[nextidx][last][cur];
                if(s[last] < s[i]) {
                    ans = min(ans, c[i] + dp[nextidx][i][cur + 1]);
                }
                dp[curidx][last][cur] = ans;
            }
        }
        best[i + 1][i] = dp[curidx][i][2];
    }

    ll ans = 1e18;
    for(int i = 0; i < n; i++) {
        ans = min(ans, c[i] + best[i + 1][i]);
    }
    if(ans == 1e18) ans = -1;
    cout << ans << "\n";
}