const int N = 1e5+9;
int n;
int cost[N+5][4], dp[N+5][4];
int find_max_points(int i,int j) {
    if(i > n || j < 1 || j > 3) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    int ans = 0;
    ans = cost[i][j] + find_max_points(i+1,j-2);
    ans = max(ans, cost[i][j] + find_max_points(i+1,j-1));
    ans = max(ans, cost[i][j] + find_max_points(i+1,j+1));
    ans = max(ans, cost[i][j] + find_max_points(i+1,j+2));
    return dp[i][j] = ans;
}
void solve() {
    /*cin >> n;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=3;j++) {
            cin >> cost[i][j];
        }
    }
    memset(dp, -1, sizeof(dp));
    int ans = 0;
    ans = find_max_points(1,1);
    ans = max(ans, find_max_points(1,2));
    ans = max(ans, find_max_points(1,3));
    cout << ans << "\n";*/

    int n;
    cin >> n;
    int a[n+1][4];
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=3;j++) {
            cin >> a[i][j];
        }
    }
    ll dp[n+1][4] = {0};
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=3;j++) {
            dp[i][j] += a[i][j];
            if(j == 1) dp[i][j] += max(dp[i-1][2], dp[i-1][3]);
            else if(j == 2) dp[i][j] += max(dp[i-1][1], dp[i-1][3]);
            else dp[i][j] += max(dp[i-1][1], dp[i-1][2]);
        }
    }
    cout << max({dp[n][1], dp[n][2], dp[n][3]}) << "\n";
} 