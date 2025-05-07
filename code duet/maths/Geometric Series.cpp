// a + ar + arto2 + arto3 + ... + arton-1 = a(rto(n) - 1) / (r - 1)
// 1 + a + ato2 + ato3 + ato4 + .... + ato(n-1) = (aton - 1) / (a - 1)
ll bigsum(ll a, ll n) {
    if(n == 0 || n == 1) return n % mod;
    if(n & 1) return ((a % mod) * bigsum(a % mod, n - 1) + 1) % mod;
    ll x = bigsum((a * a) % mod, n / 2);
}
inline ll modInverse(ll a) { return power(a, mod - 2); }
ll formula(ll a, ll n){
    if(a == 1) return n;
    return ((power(a, n) - 1) * (modInverse(a - 1))) % mod; // if mod is prime
}