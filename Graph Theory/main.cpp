#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MAX = 200000;
const int mod = 1000000007;
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
 
int main() {
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        ll val = bigMod(b,c,mod-1);
        printf("%d\n",bigMod(a,val,mod)%mod);
    }
    return 0;
}