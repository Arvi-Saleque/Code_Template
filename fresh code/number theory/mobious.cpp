/*
 *  mu[1]  =  1
 *  mu[n]  =  0   if n has any squared prime factor
 *  mu[n]  = ±1   depending on whether n has an even
 *                 ( +1) or odd (–1) number of primes
 *
 *  Complexity:  O(N log log N)
 * ---------------------------------------------------- */
void build_mu(vector<int>& mu) {
    int N = (int)mu.size() - 1;
    vector<int> primes;
    vector<int> is_comp(N + 1, 0);

    mu[1] = 1;
    for (int i = 2; i <= N; ++i) {
        if (!is_comp[i]) {
            primes.push_back(i);
            mu[i] = -1;               // prime -> odd count -> −1
        }
        for (int p : primes) {
            if (1LL * p * i > N) break;
            int x = p * i;
            is_comp[x] = 1;

            if (i % p == 0) {         // p divides i  -> square factor
                mu[x] = 0;
                break;                // important: stop here
            } else {
                mu[x] = -mu[i];       // flip sign because +1 prime factor
            }
        }
    }
}

// comprime paris

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    const int MAXA = 1000000;
    vector<int> freq(MAXA + 1, 0);

    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        ++freq[x];
    }

    /* cntMult[d] = number of array elements divisible by d
       (classic divisor sieve, O(MAXA log MAXA)) */
    vector<int> cntMult(MAXA + 1, 0);
    for (int d = 1; d <= MAXA; ++d) {
        for (int mult = d; mult <= MAXA; mult += d)
            cntMult[d] += freq[mult];
    }

    /* Mobius array */
    vector<int> mu(MAXA + 1, 0);
    build_mu(mu);

    /* Inclusion–exclusion:
       pairs with gcd == 1  =  sum_{d≥1}  μ(d) * C(cntMult[d], 2)  */
    ll ans = 0;
    for (int d = 1; d <= MAXA; ++d) {
        if (mu[d] == 0) continue;
        ll c = cntMult[d];
        if (c >= 2)
            ans += (ll)mu[d] * (c * (c - 1) / 2);
    }

    cout << ans << '\n';
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

