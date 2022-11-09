#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MAX = 10000000;
bool comp[MAX+10];

/* comp[i] = 0 means I is a prime   
NOTE: comp[1] = 1 and (i*i) <= MAX*/ 
void sieve()
{
    comp[1] = 1;
    for(int i=2;i*i<=MAX;i++)
    {
        if(!comp[i])
        {
            for(int j=i*2;j<=MAX;j+=i)
            {
                comp[j] = 1;

            }
        }
    }
}
 
int main() {
    sieve();
    return 0;
}