for(int i = 0; i < bit; i++) {
    for(int m = 0; m < mask; m++) {
        if(m & (1 << i)) {
            sosdp[m] += sosdp[m ^ (1 << i)];
        } 
    }
}

for(int i = bit - 1; i >= 0; i--) {
    for(int m = mask - 1; m >= 0; m--) {
        if(!(m & (1 << i))) {
            supersetdp[m] += supersetdp[m ^ (1 << i)];
        } 
    }
}
// complement of x = (1 << bit) - 1 - x 

cnt[m] = supermask
pw -> 2 powers array

vector<ll> sup(mask);
for(int m = 0; m < mask; m++) {
    sup[m] = (pw[cnt[m]] - 1 + mod) % mod;
}
auto exact = sup;
for(int i = 0; i < bit; i++) {
    for(int m = 0; m < mask; m++) {
        if(!(m & (1 << i))) {
            exact[m] = (exact[m] - exact[m | (1 << i)] + mod) % mod;
        }
    }
}

// exact[k] = count of subset whose AND == k