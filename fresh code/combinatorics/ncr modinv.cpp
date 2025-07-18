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
ll nCr(ll n, int r) {
    if(n < r || n < 0) return 0;
    ll ans = 1;
    for(int c = 1; c <= r; c++) {
        ans = (1LL * ans * n--) % mod;
    }
    return (1LL * ans * invf[r]) % mod;       
}
