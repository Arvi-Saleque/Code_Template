void solve() {
    int n, k;
    cin >> n >> k;
    int a[n+1];
    for(int i=1;i<=n;i++) {
        cin >> a[i];
    }
    vector<int> dp(n+5, inf);
    dp[2] = abs(a[2] - a[1]);
    for(int i=3;i<=min(k+1,n);i++) {
        dp[i] = abs(a[i] - a[1]);
    }
    for(int i=2;i<=n;i++) {
        for(int j=1;j<=k;j++) {
            if(i+j <= n) {
                dp[i+j] = min(dp[i+j], abs(a[i+j] - a[i]) + dp[i]);
            }
        }
    }
    cout << dp[n] << "\n";
}