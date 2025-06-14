// a + ar + arto2 + arto3 + ... + arton-1 = a(rto(n) - 1) / (r - 1)
// 1 + a + ato2 + ato3 + ato4 + .... + ato(n-1) = (aton - 1) / (a - 1)

// sum of from l to r
ll f(ll l, ll r) {
    ll val = (l + r) * (r - l + 1) / 2;
    return val;
}

gcd(a, b) = gcd(a, b - a)
so gcd(a1 + bj, a2 + bj) = gcd(a1 + bj, a2 - a1)