#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int N = 32768;
ll find_sq_root(ll n)
{
    ll k = sqrtl(n);
    while(k*k < n) ++k;
    while(k*k > n) --k;
    return k;
}