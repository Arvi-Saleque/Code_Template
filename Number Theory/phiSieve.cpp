#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MAX = 10000000;

/* Phi(N) means how many values from 1 to N-1 which is co-prime with N
the function give you all phi values upto MAX*/

int phi[MAX + 10];
void sievePhi(){
    for(int i=1;i<=MAX;i++)
        phi[i] = i;
 
    for(int i=2;i<=MAX;i++){
        if(phi[i] == i){
            for(int j=i; j<= MAX; j += i){
                phi[j] -= (phi[j]/i);
            }
        }
    }
}