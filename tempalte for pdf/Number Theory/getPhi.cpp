/* Phi(N) means how many values from 1 to N-1 which is co-prime with N
the function return phi(n) with a efficient way*/

ll getPhi(ll n)
{
    ll ans = 1LL*n;
    for(ll i=0;(1LL*primes[i]*primes[i])<=n;i++)
    {
        if(n%primes[i]==0)
        {
            ans -= (ans/primes[i]);
            while(n%primes[i]==0) n /= primes[i];
        }
    }
    if(n>1)
    {
        ans -= (ans/n);
    }
    return ans;
}