 void solve1() {
    string s;
    getline(cin, s);
    memset(dp, 0, sizeof dp);
    for(int len = 1; len <= s.size(); len++) {
        for(int l = 0; l + len - 1 < s.size(); l++) {
            int r = l + len - 1;
            int &ans = dp[l][r];
            if(l == r) {
                ans = 1;
            }
            else {
                ans = 0;
                if(s[l] == s[r]) {
                    ans = 2 + dp[l+1][r-1];
                }
                else {
                    ans = max(dp[l][r-1], dp[l+1][r]);
                }
            }
        }
    }

    cout << dp[0][s.size()-1] << "\n";
}