> string str;
getline(cin, str);
stringstream mystream(str);
int l, r, v;
mystream >> l >> r;
string tmp;
mystream << tmp;

>ll find_sq_root(ll n) {
    ll k = sqrtl(n);
    while(k*k < n) ++k;
    while(k*k > n) --k;
    return k;
}
__int128 power(__int128 base, int exp) {
    __int128 result = 1;
    while(exp) {
        if(exp & 1)
            result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}
string toString(__int128 num) {
    if(num == 0)
        return "0";
    string s;
    while(num > 0) {
        s.push_back('0' + (int)(num % 10));
        num /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main(){
    // Read inputs x and y
    long long x, y;
    cin >> x >> y;
    long long g = gcd(x, y);
    __int128 answer = power(g, 6);
    cout << toString(answer) << endl;
    return 0;
}


// traverse on diagonal.cpp
vector<vector<int>> mp(n + m + 2, vector<int>());
for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
        mp[i + j - 2].push_back(v[i][j]); // i + j - 2 is the diagonal
    }
}
int ans = 0;
for(int d = 0; d < (n + m - 1) / 2; d++) { // skip middle diagonal 
    int zero = 0, one = 0;
    auto vv = mp[d];
    for(auto x : vv) {
        (x == 0) ? zero++ : one++; 
    }
    vv = mp[n + m - 2 - d]; // alter diagonal
    for(auto x : vv) {
        (x == 0) ? zero++ : one++; 
    }
    ans += min(zero, one);
}

