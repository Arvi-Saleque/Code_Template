#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MAX = 200000;
const int mod = 1000000007;

/*The function return a^b % M
NOTE: Don't Forget To mod the final ans*/ 

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
    ll a,b,MOD;
    cin >> a >> b >> MOD;
    cout << bigMod(a,b,MOD)%MOD << endl; //*** Be carefull with (%MOD) 
    return 0;
}