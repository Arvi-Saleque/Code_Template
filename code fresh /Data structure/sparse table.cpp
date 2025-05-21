// not final 
struct Spares_table { // must be 0-based
    vector<int> a;
    vector<vector<int>> t;
    int n, q, lg;
    Spares_table(){}
    Spares_table(int n, int q) {
        this->n = n;
        this->q = q;
        a.assign(n, 0);
        lg = log2(n) + 1;
        t.assign(n, vector<int>(lg));
        take_input();
    }
    void take_input() {
        for(auto &x : a) {
            cin >> x;
        }
        build();
    }
    void build() {
        for(int i = 1; i < n; i++) {
            t[i][0] = abs(a[i] - a[i - 1]);
        }
        for(int j = 1; j < lg; j++) {
            for(int i = 0; i + (1 << (j - 1)) < n; i++) {
                t[i][j] = gcd(t[i][j - 1], t[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    void print() {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < lg; j++) {
                cout << t[i][j] << " ";
            }
            cout << "\n";
        }
    }
    int query(int l, int r) { // must be 0 based index
        int len = r - l + 1;
        int k = log2(len);
        return gcd(t[l][k], t[l + len - (1 << k)][k]);
    }
    void solve() {
        //print();
        while(q--) {
            int l, r;
            cin >> l >> r;
            l--; r--;   
            if(l == r) cout << 0 << " ";
            else cout << query(l + 1, r) << " ";
        }
        cout << "\n";
    }
};
struct Spares_table { // must be 0-based
    vector<vector<pair<int, int>>> t;
    int n, q, lg, sz;
    Spares_table(){}
    Spares_table(int n, int q, int sz, vector<int> a, vector<int> b) {
        this->n = n;
        this->q = q;
        this->sz = sz;
        lg = log2(n) + 1;
        t.assign(n, vector<pair<int, int>>(lg));
        for(int i = 0; i < n; i++) {
            t[i][0].first = a[i + 1];
            t[i][0].second = b[i + 1];
        }
        build();
    }
    void build() {
        for(int j = 1; j < lg; j++) {
            for(int i = 0; i + (1 << (j - 1)) < n; i++) {
                t[i][j].first = max(t[i][j - 1].first, t[i + (1 << (j - 1))][j - 1].first);
                t[i][j].second = min(t[i][j - 1].second, t[i + (1 << (j - 1))][j - 1].second);
            }
        }
    }
    pair<int, int> query(int l, int r) { // must be 0 based index
        int len = r - l + 1;
        int k = log2(len);
        int mx = max(t[l][k].first, t[l + len - (1 << k)][k].first);
        int mn = min(t[l][k].second, t[l + len - (1 << k)][k].second);
        return {mx, mn};
    }
    void solve() {
        //print();
        string ans(q, '0');
        for(int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--; r--;   
            auto [mx, mn] = query(l, r);
            //cout << l << " " << r << " " << mx << " " << mn << "\n";
            if(mx >= sz && mn >= l + 1) {
                ans[i] = '1'; 
            }
        }
        cout << ans << "\n";
    }
};