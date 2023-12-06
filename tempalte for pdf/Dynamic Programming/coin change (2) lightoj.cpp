int dp[105][N];
int a[105];
int ways(int pos,int sum) {
    if(pos == 0) {
        return (sum == 0);
    }
    int &ans = dp[pos][sum];
    if(ans != -1) return ans;
    ans = ways(pos - 1, sum);
    if(sum - a[pos] >= 0) ans += ways(pos, sum - a[pos]);
    ans %= MOD;
    return ans;
}
void solve() {
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    // memset(dp, -1, sizeof dp);
    // cout << ways(n, k) << "\n";
    for(int i = 0; i <= n; i++) {
        for(int sum = 0; sum <= k; sum++) {
            if(i == 0) {
                dp[i][sum] = (sum == 0);
            }
            else {
                dp[i][sum] = dp[i - 1][sum];
                if(sum - a[i] >= 0) dp[i][sum] += dp[i][sum - a[i]];
                dp[i][sum] %= MOD;
            }
        }
    }
    cout << dp[n][k] << "\n";
} 