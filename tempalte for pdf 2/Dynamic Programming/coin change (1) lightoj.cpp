#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int N = 100, MOD = 100000007;
void solve() {
    int n, k;
    cin >> n >> k;
    int a[n+1], c[n+1];
    for(int i=1;i<=n;i++) {
        cin >> a[i];
    }
    for(int i=1;i<=n;i++) {
        cin >> c[i];
    }
    int dp[n+1][k+1];
    memset(dp, 0, sizeof dp);
    for(int i=0;i<=n;i++) {
        dp[i][0] = 1;
    }
    for(int i=1;i<=n;i++) { // i tomo coin porjonto niye try kora hosse
        for(int amount=1;amount <= k; amount++) { // i tomo coin porjonto niye 1 to k sob coin gula bananor try kora hosse
            for(int cnt = 0; cnt <= c[i]; cnt++) { // i tomo coin 0 to c[i] bar neoa hosse
                if(cnt*a[i] <= amount) { // jodi cnt ta i neoa jay
                    dp[i][amount] = (dp[i][amount] + dp[i-1][amount - (cnt*a[i])]) % MOD;
                    //cout << i << " " << amount << " " << cnt << " -> " << dp[i][amount] << "\n";
                }
            }
        }
    }
    /*for(int i=1;i<=n;i++) {
        for(int j=1;j<=k;j++) {
            cout << dp[i][j] << " "; 
        }
        cout << "\n";
    }*/
    cout << dp[n][k] << "\n";
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