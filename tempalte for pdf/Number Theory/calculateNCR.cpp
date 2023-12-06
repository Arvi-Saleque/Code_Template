const int N = 1e5+9;
void calcualteFactorial()
{
    fact[0] = fact[1] = 1;
    for(int i=2;i<=MAX;i++)
    {
        fact[i] = (fact[i-1]*i)%MOD;
    }
}
ll bigMod(ll a,ll b,ll MOD) 
{
    ll res = 1;
    bool flag = a >= MOD;
    while(b)
    {
        if (b & 1)
        {
            res *= a;
            if (res >= MOD)
            {
                flag = true;
                res %= MOD;
            }
        }
        a *= a;
        if (a >= MOD)
        {
            flag = 1;
            a %= MOD;
        }
        b >>= 1;
    }
    return res + (flag * MOD);
}
ll calculateNCR(ll n, ll r)
{
    if (r == 0)
        return 1;
    if (r > n)
        return 0;
    ll N = fact[n]%MOD;
    ll R = bigMod(fact[r],MOD-2,MOD)%MOD;
    ll N_R = bigMod(fact[n-r],MOD-2,MOD)%MOD;
    return ((N*R)%MOD*N_R)%MOD;
}