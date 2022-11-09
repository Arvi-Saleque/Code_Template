#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MAX = 100000000;
int comp[5000000];

/* Bitwise sieve mainly is a memory efficient sieve.
Here we use int so that we can store prime upto 32*1e7 
be carefuull if you use long long then it will be 64 and 63 instead of 32 and 31*/

int setBit(int n,int pos) // set bit means The pos'th bit of n is 1
{
    n = (n | (1 << pos));
    return n;
}
bool checkBit(int n,int pos) // if checkbit(comp[n],pos) = 0 that means n is a prime 
{
    return (n & (1 << pos));
}
void sieve()
{
    comp[0] = setBit(comp[0], 0);
    comp[0] = setBit(comp[0], 1);
    for(int i=4;i<=MAX;i+=2) 
        comp[i >> 5] = setBit(comp[i >> 5], i&31); // i>>5 = i/32 i&31 it is actually 31th position of N 
    for(int i=3;i*i<=MAX;i+=2)
    {
        if(!checkBit(comp[i >> 5],i & 31))
        {
            for(int j=i+i;j<=MAX;j+=i)
            {
                comp[j>>5] = setBit(comp[j>>5],j&31);
            }
        }
    }
}
 
int main() {
    sieve();
    return 0;
}