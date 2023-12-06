ll knapsack(int i,int cap) {
    if(i < 1) return 0;
    if(dp[i][cap] != -1) return dp[i][cap];
    ll ans = 0;
    if(cap - w[i] >= 0) {
        ans = v[i] + knapsack(i-1, cap - w[i]);
    }
    ans = max(ans, knapsack(i-1, cap));
    return dp[i][cap] = ans;
}

void solve() {
    int n, cap;
    cin >> n >> cap;
    pair<int,int> arr[n+1];
    for(int i=1;i<=n;i++) {
        cin >> arr[i].first >> arr[i].second;
    }
    sort(arr+1,arr+n+1);
    ll dp[n+1][cap+1] = {0};
    for(int i=1;i<=cap;i++) {
        if(i - arr[1].first >= 0) dp[1][i] = arr[1].second;
        else dp[1][i] = 0;
    }
    for(int i=2;i<=n;i++) {
        for(int w=1;w<=cap;w++) {
            if(w - arr[i].first >= 0) {
                int num = w - arr[i].first;
                dp[i][w] = max({dp[i-1][w], dp[i][w-1], arr[i].second + dp[i-1][num]});
            }
            else {
                dp[i][w] = max(dp[i-1][w], dp[i][w-1]);
            }
        }
    }
    cout << dp[n][cap] << "\n";
}