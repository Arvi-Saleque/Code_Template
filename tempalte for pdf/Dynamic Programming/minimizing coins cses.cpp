/*
produce a sum of money x using the available coins in such a way 
that the number of coins is minimal. 
if the coins are {1, 5, 7} and x is 11 then 
an optimal solution is 5+5+1 which requires 3 coins
*/

const int N = 1e6 + 9, MOD = 100000007, inf = 1e9;
int a[N], dp[2][N];
void solve() {
    int n, x;
    cin >> n >> x;
    for(int i=1;i<=n;i++) {
        cin >> a[i];
    }
    dp[0][0] = 0;
    for(int sum = 1; sum <= x; sum++) {
        dp[0][sum] = inf;
    }
    for(int i = 1; i <= n; i++) {
        for(int sum = 0; sum <= x; sum++) {
            dp[1][sum] = dp[0][sum];
            if(sum - a[i] >= 0) dp[1][sum] = min(dp[1][sum], 1 + dp[1][sum - a[i]]);
        }
        for(int sum = 0; sum <= x; sum++) {
            dp[0][sum] = dp[1][sum];
        }
    }
    cout << (dp[1][x] >= inf ? -1 : dp[1][x]) << "\n";
} 