/*
difference array using map
*/

void solve() {
    int n,q;
    cin >> n >> q;
    map<int,int> mp, cummp;
    while(n--) {
        int a,b;
        cin >> a >> b;
        mp[a]++;
        mp[b+1]--;
    }
    auto it = mp.begin();
    int pre = it->second;
    cummp[it->first] = it->second;
    it++;
    for(;it!=mp.end();it++) {
        cummp[it->first] = it->second + pre;
        pre = cummp[it->first];
    }

    while(q--) {
        int x; cin >> x;
        it = cummp.lower_bound(x);
        if(it != cummp.begin() && it->first != x) it--;
        cout << it->second << "\n";
    }

}