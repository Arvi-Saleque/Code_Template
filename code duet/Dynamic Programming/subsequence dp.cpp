// https://codeforces.com/gym/102911/problem/B1
// for any subsequecen always work with frequency because
// order does not matter here 
// and just map and store them in vector and take each element 
// at least one with maintining extra in DP 
void solve() {
    auto C = [&](ll n, ll r) {
        if(n < r) return 0LL;
        if(r > n - r) r = n - r;
        ll ans = 1;
        for(int i = 1; i <= r; i++) {
            ans *= n - r + i;
            ans /= i;
        }
        return ans;
    };
    int n, k;
    cin >> n >> k;
    int nn = n;
    map<int, int> mp;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        mp[x]++;
    }    
    vector<pair<int, int>> vpp;
    for(auto [x, y] : mp) {
        vpp.push_back({x, y});
    }
    n = vpp.size();
    vector<vector<ll>> dp(nn + 1, vector<ll>(nn + 1, -1));
    function<ll(int, int)> f = [&](int pos, int rem)  {
        if(pos == n) {
            if(rem == 0) return 1LL;
            return 0LL;
        }
        ll &ans = dp[pos][rem];
        if(ans != -1) return ans;
        ans = 0;
        for(int k = 0; k <= rem; k++) {
            ans = (ans + C(vpp[pos].second, k + 1) * f(pos + 1, rem - k));
        }
        return ans;
    };
    ll ans = 0;
    for(int i = k; i <= nn; i++) {
        ans += f(0, i - k);
    }
    cout << ans << "\n";
}