#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int N = 1e6+9;
bool comp[N+5];
vector<int> primes;
void sieve() {
    comp[1] = 1;
    for(int i=2;(1LL*i*i) <= N; i++) {
        if(!comp[i]) {
            for(int j=i*2;j<=N;j+=i) {
                comp[j] = 1;
            }
        }
    }
    primes.emplace_back(2);
    for(int i=3;i<=N;i+=2) {
        if(!comp[i]) primes.emplace_back(i);
    }
}
void find_prime_factor(ll n, map<int,int> &mp) {
    if(n < 0) n *= -1;
    for(int i=0;(1LL * i * i) <= n; i++) {
        if(n % primes[i] == 0) {
            while(n % primes[i] == 0) {
                mp[primes[i]]++;
                n /= primes[i];
            }
        }
    }
    if(n > 1) mp[n] = 1; 
}