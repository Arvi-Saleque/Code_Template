ll find_the_number_of_divisor(ll n)
{
    ll ans = 1;
    for(int i=0;(1LL*primes[i]*primes[i]) <= n; i++)
    {
        int cnt = 0;
        if(n % primes[i] == 0)
        {
            while(n % primes[i] == 0)
            {
                cnt++;
                n /= primes[i];
            }
        }
        ans *= (cnt+1);
    }
    if(n > 1) ans *= 2;
    return ans;
}