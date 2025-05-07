struct numth {
    struct exgcd {
        ll gcd, x, y; // gcd of a and b, coefficients x and y for the equation ax + by = gcd(a, b)
    };

    // Extended Euclidean Algorithm to solve ax + by = gcd(a, b)
    exgcd exEuclid(ll a, ll b) {
        if (b == 0) {
            exgcd nd = {a, 1, 0}; // Base case: gcd(a, 0) = a
            return nd;
        }
        exgcd sml = exEuclid(b, a % b); // Recursive call
        exgcd bg = {sml.gcd, sml.y, sml.x - (a / b) * sml.y};
        return bg;
    }

    // Function to find the modular inverse of a under modulo m using the Extended Euclidean Algorithm
    ll multiInverse(ll a, ll m) {
        exgcd sml = exEuclid(a, m);
        if (sml.gcd != 1) {
            return -1; // Inverse doesn't exist
        }
        return (sml.x % m + m) % m;
    }

    // Function to find the modular inverse of a under modulo m using Fermat's Little Theorem
    ll modInverseFermatsMethod(ll a, ll m) {
        ll inv = __gcd(a, m);
        if (inv != 1) {
            return -1; // Inverse doesn't exist
        }
        return binaryExpo(a, m - 2, m);
    }

    vector<ll> svp;       // List of all prime numbers up to n (sieve primes)
    vector<ll> svl;       // Smallest prime factor for each number up to n
    bitset<200005> check; // Bitset array to mark non-prime numbers

    // Prime factorization for large numbers using precomputed primes
    vector<pair<ll, ll>> primeFactorizationLarge(ll n) {
        vector<pair<ll, ll>> factors;
        for (ll i = 0; i < svp.size() && svp[i] * svp[i] <= n; ++i) {
            ll prime = svp[i];
            if (n % prime == 0) {
                ll count = 0;
                while (n % prime == 0) {
                    n /= prime;
                    count++;
                }
                factors.push_back({prime, count});
            }
        }
        if (n > 1) {
            factors.push_back({n, 1});
        }
        return factors;
    }

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

    // Chinese Remainder Theorem to solve simultaneous congruences
    ll chineseRemainderTheorem(vector<ll> nums, vector<ll> rems) {
        ll prod = accumulate(nums.begin(), nums.end(), 1LL, multiplies<ll>());
        ll result = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            ll pp = prod / nums[i];
            result += rems[i] * multiInverse(pp, nums[i]) * pp;
        }
        return result % prod;
    }
};

