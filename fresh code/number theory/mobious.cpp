#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 9, mod = 1e9 + 7;

int mob[N + 2];
void pre() {
    vector<bool> is_prime(N + 2, true);
    mob[1] = 1;
    vector<int> prm;
    for(int i = 2; i < N; i++) {
        if(is_prime[i]) {
            prm.push_back(i);
            mob[i] = -1;
        }
        for(auto p : prm) {
            if(1LL * i * p >= N) break;
            int x = i * p;
            is_prime[x] = 0;
            if(i % p == 0) {
                mob[x] = 0;
                break;
            }
            else {
                mob[x] = mob[i] * -1;
            }
        }
    }
}

void solve() {
    int n; 
    cin >> n;
    vector<int> v(n);
    for(auto &x : v) cin >> x;
    int mx = *max_element(v.begin(), v.end());
    vector<int> freq(mx + 2), cnt(mx + 2);
    for(auto x : v) cnt[x]++;

    for(int i = 1; i <= mx; i++) {
        for(int j = i; j <= mx; j += i) {
            freq[i] += cnt[j];
        }
    }
    
    auto f = [&](int x) {
        if(x < 2) return 0LL;
        return (1LL * x * (x - 1)) >> 1;
    };

    ll ans = f(n), bad = 0;
    for(int d = 2; d <= mx; d++) {
        if(mob[d] == 0) continue;
        bad += (f(freq[d]) * mob[d]);
    }
    cout << ans + bad << "\n"; // bad already has its proper sign so + 
}

int main() {
    pre();
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int tc = 1;
    // cin >> tc;
    while(tc--) {
        solve();
    }
    return 0;
}


// co prime subsequnce

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    const int MAXA = 100000;            // problem limit (≤1e5)
    vector<int> freq(MAXA + 1, 0);

    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        ++freq[x];
    }

    /* cntMult[d] = #elements divisible by d */
    vector<int> cntMult(MAXA + 1, 0);
    for (int d = 1; d <= MAXA; ++d)
        for (int mult = d; mult <= MAXA; mult += d)
            cntMult[d] += freq[mult];

    /* Mobius */
    vector<int> mu(MAXA + 1, 0);
    build_mu(mu);

    /* pre-compute powers of two */
    vector<int> pow2(n + 1);
    pow2[0] = 1;
    for (int i = 1; i <= n; ++i)
        pow2[i] = (pow2[i - 1] * 2LL) % MOD;

    /* Inclusion–exclusion over all subsequences */
    ll ans = 0;
    for (int d = 1; d <= MAXA; ++d) {
        if (mu[d] == 0) continue;
        int c = cntMult[d];
        if (c == 0) continue;

        int add = (pow2[c] - 1 + MOD) % MOD;   // (2^c − 1) mod M
        ans += (ll)mu[d] * add;
        if (ans >= MOD || ans <= -MOD)         // keep in range of 64-bit
            ans %= MOD;
    }

    ans %= MOD;
    if (ans < 0) ans += MOD;                  // ensure positive

    cout << ans << '\n';
    return 0;
}

