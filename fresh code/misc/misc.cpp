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
ios_base::sync_with_stdio(0); cin.tie(0);
// palindrome count
// odd <= 1
// so Xor = 0 means odd = 0
// Xor = 1 means odd = 1 for this
// i need to fllip exactly one bit of a-z
map<int, ll> freq;
int mask = 0;
// before processing any characters, we have one occurrence of mask 0
freq[mask] = 1;
ll result = 0;
// iterate over each character in the string
for (char c : s) {
    // Toggle the bit corresponding to the current character
    mask ^= (1 << (c - 'a'));
    // count substrings ending here that are already balanced (exact match)
    result += freq[mask];
    // count substrings ending here that differ by exactly one bit
    for (int b = 0; b < 26; ++b) {
        result += freq[mask ^ (1 << b)];
    }
    // update frequency for the current mask
    freq[mask]++;
}
cout << result << "\n";

// sliding window min-max deque.cpp
deque<int> dq;
for(int i = 1; i <= n; i++) {
    while(!dq.empty() && v[dq.back()] < v[i]) {
        dq.pop_back();
    }
    dq.push_back(i);
    if(dq.front() <= i - k) {
        dq.pop_front();
    }
    if(i >= k) {
        cout << v[dq.front()] << " ";
    }
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

// uqnieu OR among all subarray.cpp
int ans = 0;
map<int, bool> has;
for(int i = 1; i <= n; i++) {
    int cur = 0, next = i, cnt = 0;
    while(next <= n) {
        cur |= tree.query(1, 1, n, i, next).val;
        if(!has.count(cur)) cnt++;
        has[cur] = 1;
        int mn = n + 2;
        for(int j = 0; j < 30; j++) {
            if(!(cur & (1 << j))) {
                if(bitv[j].size() > 0) {
                    auto it = lower_bound(bitv[j].begin(), bitv[j].end(), i);
                    if(it != bitv[j].end()) {
                        mn = min(mn, *it);
                    }
                }
            }
        }
        next = mn;
    }
}