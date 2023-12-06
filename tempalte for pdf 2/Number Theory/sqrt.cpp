ll find_sq_root(ll n)
{
    ll k = sqrtl(n);
    while(k*k < n) ++k;
    while(k*k > n) --k;
    return k;
}