ll dp[N][N];
int a[N];
/*Choose two adjacent slimes, and combine them into a new slime. 
The new slime has a size of x+y, where x and y are the sizes of the slimes 
before combining them. Here, a cost of x+y is incurred. 
The positional relationship of the slimes does not change while combining slimes.*/
// dp[l][r] returns If we combine a[l].....a[r] what is the merged maximum sum 
// dp[l][r] returns If we split a[l].....a[r] what is final maximum sum
/*
Input: 
6
7 6 8 6 1 1
Output: 
68

(7, 6, 8, 6, 1, 1) → (7, 6, 8, 6, 2)
(7, 6, 8, 6, 2) → (7, 6, 8, 8)
(7, 6, 8, 8) → (13, 8, 8)
(13, 8, 8) → (13, 16)
(13, 16) → (29)
*/

ll minimum_cost(int l,int r) {
    if(l == r) return 0;
    ll &ans = dp[l][r];
    if(ans != -1) return ans;
    ans = inf;
    ll current_cost = 0;
    for(int i=l;i<=r;i++) {
        current_cost += a[i];
    }
    for(int i=l;i<r;i++) {
        ans = min(ans, current_cost + minimum_cost(l, i) + minimum_cost(i+1, r));
    }
    return ans;
}
void solve() {
    int n;
    cin >> n;
    for(int i=1;i<=n;i++) {
        cin >> a[i];
    }
    for(int len = 1; len <= n; len++) {
        for(int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            if(l == r) continue;
            ll current_cost = 0;
            for(int i = l; i <= r; i++) {
                current_cost += a[i];
            }
            dp[l][r] = inf;
            for(int i = l; i < r; i++) {
                dp[l][r] = min(dp[l][r], current_cost + dp[l][i] + dp[i + 1][r]);
            } 
        }
    }

    cout << dp[1][n] << "\n";
}