ll dp[N][N][2];
int a[N];
ll max_score_of_first_player(int i,int j,bool player) {
    if(i > j) return 0;
    ll &ans = dp[i][j][player];
    if(ans != -1) return ans;
    ans = 0;
    if(player == 0) {
        ll ans1 = a[i] + max_score_of_first_player(i+1, j, player ^ 1);
        ll ans2 = a[j] + max_score_of_first_player(i, j-1, player ^ 1);
        ans = max(ans1, ans2);    
    }
    else {
        ll ans1 = max_score_of_first_player(i+1, j, player ^ 1);
        ll ans2 = max_score_of_first_player(i, j-1, player ^ 1);
        ans = min(ans1, ans2);  
    }
    return ans;
}
void solve() {
    int n;
    cin >> n;
    for(int i=1;i<=n;i++) {
        cin >> a[i];
    }
    memset(dp, -1, sizeof dp);
    cout << max_score_of_first_player(1, n, 0) << "\n";
} 