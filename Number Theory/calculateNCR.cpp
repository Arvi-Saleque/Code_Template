#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 1000000;
const ll mod = 1000000007;
ll fact[MAX+10];
void calcualteFactorial()
{
    fact[0] = fact[1] = 1;
    for(int i=2;i<=MAX;i++)
    {
        fact[i] = (fact[i-1]*i)%mod;
    }
}
ll bigMod(ll a,ll b,ll M)
{
    if(b == 0) return 1;
    if(!(b&1))
    {
        ll val = bigMod(a,b/2,M)%M;
        return (val*val)%M;
    }
    else 
    {
        return (a * bigMod(a,b-1,M)%M)%M;
    }
}
ll calculateNCR(ll n, ll r)
{
    ll N = fact[n]%mod;
    ll R = bigMod(fact[r],mod-2,mod)%mod;
    ll N_R = bigMod(fact[n-r],mod-2,mod)%mod;
    return ((N*R)%mod*N_R)%mod;
}
int main()
{
    calcualteFactorial();
    ll n,r;
    scanf("%lld %lld",&n,&r);
    printf("%lld\n",calculateNCR(n,r));
    
    return 0;
}