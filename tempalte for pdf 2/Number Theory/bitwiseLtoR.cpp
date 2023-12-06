ll bitwiseANDfromLtoR(ll l, ll r) {
    if(l == r) return l;
    ll res = 0;
    for(int i = 0; i < 63; i++) {
        if(!(l & (1LL << i))) continue;

        ll tmp = 1LL << i;
        ll x = r - l + l % tmp + 1;
        if(x <= tmp) {
            res |= tmp;
        }
    }
    return res;
}