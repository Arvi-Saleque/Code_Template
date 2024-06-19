ll prime_factorization(int n)
{
    ll ans = 1;
    for(int i=0;primes[i] <= n; i++)
    {
        int cnt = 0;
        for(int j=primes[i];; j *= primes[i])
        {
            if(j > n) break;
            cnt += (n/j);
        }
        ans = (ans * (cnt+1))%M;
    }
    return ans;
}