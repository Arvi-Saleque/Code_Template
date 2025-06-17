vector<map<ll, ll>> dp;

ll f(int pos, ll mask) { 
    if(pos == n) {
        vector<int> v(n);
        ll tmpmask = mask;
        for(int i = n - 1; i >= 0; i--) {
            v[i] = (tmpmask % (m + 1));
            tmpmask /= (m + 1); 
        }
        ll tmp = 0;
        for(auto [a, b, c, d] : Q) {
            tmp += (v[b] - v[a] == c ? d : 0);
        }
        return tmp;
    }
    if(dp[pos].count(mask)) return dp[pos][mask];
    ll &ans = dp[pos][mask];
    int start = 1;
    if(pos > 0) start = mask % (m + 1);
    for(int j = start; j <= m; j++) {
        ll tmpmask = (mask * (m + 1) + j);
        ans = max(ans, f(pos + 1, tmpmask));
    }
    
    return ans;
}
