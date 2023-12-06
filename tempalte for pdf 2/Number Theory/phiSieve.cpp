/* Phi(N) means how many values from 1 to N-1 which is co-prime with N
the function give you all phi values upto N*/
int phi[N + 10];
void sievePhi(){
    for(int i=1;i<=N;i++)
        phi[i] = i;
 
    for(int i=2;i<=N;i++){
        if(phi[i] == i){
            for(int j=i; j<= N; j += i){
                phi[j] -= (phi[j]/i);
            }
        }
    }
}