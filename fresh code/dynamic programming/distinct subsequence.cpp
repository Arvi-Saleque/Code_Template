// dp[i] represent number of distincs subsequence with first i char
// where last[ch] is the index of last occur of ch
string s; cin >> s; s = '.' + s;
vector<int> dp(n + 1, 0), last(26, -1);
dp[0] = 1;
for(int i = 0; i < n; i++) {
    dp[i + 1] = (2LL * dp[i]) % mod;
    if(last[s[i + 1] - 'A'] != -1) {
        dp[i + 1] = (dp[i + 1] - dp[last[s[i + 1] - 'A'] - 1] + mod) % mod;
    } 
    last[s[i + 1] - 'A'] = i + 1;
}