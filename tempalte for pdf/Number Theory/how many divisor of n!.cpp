/*
Given a number, find the total number of divisors of the factorial of the number.
*/
bool comp[N+5];
vector<int> primes;
void sieve()
{
    for(int i=2;i*i<=N;i++)
    {
        if(!comp[i])
        {
            for(int j=i*2;j<=N;j+=i)
            {
                comp[j] = 1;
            }
        }
    }
    primes.emplace_back(2);
    for(int i=3;i<=N;i+=2)
    {
        if(!comp[i]) primes.emplace_back(i);
    }
}
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
void solve()
{
    int n;
    cin >> n;
    ll ans = prime_factorization(n);
    cout << ans << "\n";
}