struct numth {
    // Segmented sieve to find primes in a range
    vector<ll> segmented_sieve(ll l, ll r) {
        vector<ll> segpr;
        vector<bool> pr(r - l + 5, 1);
        if (l == 1) {
            pr[0] = false;
        }
        for (ll i = 0; svp[i] * svp[i] <= r; i++) {
            ll cur = svp[i];
            ll base = cur * cur;
            if (base < l) {
                base = ((l + cur - 1) / cur) * cur;
            }
            for (ll j = base; j <= r; j += cur) {
                pr[j - l] = false;
            }
        }
        for (ll i = 0; i <= r - l; i++) {
            if (pr[i]) {
                segpr.push_back(l + i);
            }
        }
        return segpr;
    }

    // Euler's Totient Function for a single number
    ll eulerTotientFunction(ll n) {
        ll result = n;
        for (ll i = 0; i < svp.size() && svp[i] * svp[i] <= n; ++i) {
            if (n % svp[i] == 0) {
                while (n % svp[i] == 0) {
                    n /= svp[i];
                }
                result -= result / svp[i];
            }
        }
        if (n > 1) {
            result -= result / n;
        }
        return result;
    }

    // Compute Euler's Totient Function for all numbers up to N
    vector<ll> computeTotientUpToN(ll n) {
        vector<ll> phi(n + 1);
        for (ll i = 1; i <= n; ++i) {
            phi[i] = i;
        }
        for (ll i = 2; i <= n; ++i) {
            if (phi[i] == i) {
                for (ll j = i; j <= n; j += i) {
                    phi[j] *= (i - 1);
                    phi[j] /= i;
                }
            }
        }
        return phi;
    }
};