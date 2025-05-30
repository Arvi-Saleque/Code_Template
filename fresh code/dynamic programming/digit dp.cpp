string a, b;
a < b must
function<int(int, int, bool, bool, bool)> f = [&](int pos, int rem, bool lf, bool uf, bool lz) {
    if(pos == a.size()) {
        if(rem == 0) return 1;
        return 0;
    }
    int &ans = dp[pos][rem][lf][uf][lz];
    if(ans != -1) return ans;
    ans = 0;
    int da = a[pos] - '0', db = b[pos] - '0';
    for(int i = 0; i <= 9; i++) {
        if(i < da && !lf) continue;
        if(i > db && !uf) continue;
        bool lff = lf, uff = uf, lzz = lz;
        if(i > da) lff = 1;
        if(i < db) uff = 1;
        if(i != 0) lzz = 0;
        ans = (ans + f(pos + 1, (rem + i) % d, lff, uff, lzz)) % mod;
    }
    return ans;
};
