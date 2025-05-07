// for counting distinct subsequence 
// go from a to next a
// for example from a to next b,c,d,....z
// here main thing is you cant do take or not take
// another appraoch is 
// dp[i] represent number of distincs subsequence with first i char
// where last[ch] is the index of last occur of ch
void solve() {
    string s; cin >> s;
    int n = s.size();
    s = '.' + s;
    vector<int> dp(n + 1, 0);
    vector<int> last(26, -1);
    dp[0] = 1;
    for(int i = 0; i < n; i++) {
        dp[i + 1] = (2LL * dp[i]) % mod;
        if(last[s[i + 1] - 'A'] != -1) {
            dp[i + 1] = (dp[i + 1] - dp[last[s[i + 1] - 'A'] - 1] + mod) % mod;
        } 
        last[s[i + 1] - 'A'] = i + 1;
    }
    cout << dp[n] << "\n";
} 