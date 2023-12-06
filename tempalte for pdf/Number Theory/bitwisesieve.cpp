#include <bits/stdc++.h>
using namespace std; 
const int N = 1e7 + 9; 
bool Check(int N,int pos){return (bool)(N & (1<<pos));}
int Set(int N,int pos){ return N=N | (1<<pos);}
int comp[(N/32)+2];
void sieve()
{
    comp[1>>5]=Set(comp[1>>5],1 & 31);
    for(int i = 3; (1LL*i*i)<=N; i += 2 ) 
    {
        if(Check(comp[i>>5],i&31)==0)
        {
            for(int j = i*i; j <= N; j += (i<<1) )
            {
                comp[j>>5]=Set(comp[j>>5],j & 31);
            }
        }
    }
}