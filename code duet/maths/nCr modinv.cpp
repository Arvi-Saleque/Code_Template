int const N = 1e6 + 2, mod = 1000003;
int f[N], invf[N];
void pre() {
    f[0] = 1;
    for (int i = 1; i < N; i++) {
        f[i] = 1LL * i * f[i - 1] % mod;
    }
    invf[N - 1] = power(f[N - 1], mod - 2);
    for (int i = N - 2; i >= 0; i--) {
        invf[i] = 1LL * invf[i + 1] * (i + 1) % mod;
    }
}
int nCr(int n, int r) {
    if (n < r or n < 0) return 0;
    return 1LL * f[n] * invf[r] % mod * invf[n - r] % mod;
}
// ll Catalan_Number = (nCr(2*n, n) % mod - nCr(2*n, n+1) % mod + mod) % mod;
// Formula: Cn = (1 / (n + 1)) * (2n choose n)
// 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862
// Examples: Valid parentheses, binary search trees, Dyck paths, polygon triangulations
// Non-crossing handshakes, stack-sortable permutations, rooted planar trees, non-crossing partitions
struct combi
{
    typedef long long ll;
    const ll md = 10056;

    ll add(ll a, ll b)
    {
        ll res = (a + b) % md;
        if (res < 0)
            res += md;
        return res;
    }
    ll mul(ll a, ll b)
    {
        ll res = (a * b) % md;
        if (res < 0)
            res += md;
        return res;
    }
    ll modpw(ll a, ll b)
    {
        if (b == 0)
        {
            return 1 % md;
        }
        ll v = modpw(a, b / 2);
        v = mul(v, v);
        if (b % 2 == 1)
        {
            v = mul(v, a);
        }
        return v;
    }

    vector<ll> facts;
    vector<ll> invs;
    vector<ll> finvs;
    vector<ll> derangements;
    vector<vector<ll>> stirling_second;
    vector<vector<ll>> stirling_first;
    int sz;

    void init(int n)
    {
        sz = n;
        facts.assign(n + 1, 1);
        invs.assign(n + 1, 1);
        finvs.assign(n + 1, 1);

        // Calculate derangements and factorials
        for (int i = 2; i <= n; i++)
        {
            invs[i] = modpw(i, md - 2);
        }
        for (int i = 1; i <= n; i++)
        {
            facts[i] = mul(facts[i - 1], i);
            finvs[i] = mul(finvs[i - 1], invs[i]);
        }
    }
    void init_derangement(int n)
    {
        sz = n;
        derangements.assign(n + 1, 0);
        derangements[0] = 1;
        derangements[1] = 0;
        // Calculate derangements and factorials
        for (int i = 2; i <= n; i++)
        {
            derangements[i] = mul(i - 1, add(derangements[i - 1], derangements[i - 2]));
        }
    }
    ll fact(int n)
    {
        return facts[n];
    }

    ll inv(int n)
    {
        return invs[n];
    }

    ll finv(int n)
    {
        return finvs[n];
    }

    ll ncr(int n, int r)
    {
        if (r > n || r < 0)
            return 0;
        return mul(facts[n], mul(finvs[r], finvs[n - r]));
    }

    ll npr(int n, int r)
    {
        if (r > n || r < 0)
            return 0;
        return mul(facts[n], finvs[n - r]);
    }

    ll catalan(int n)
    {
        if (n == 0)
            return 1;
        return mul(ncr(2 * n, n), inv(n + 1));
    }
    // Function to calculate the number of derangements of n items
    ll derangement(ll n)
    {
        return derangements[n];
    }
};
