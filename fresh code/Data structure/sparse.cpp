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
    int query(int l, int r) { // must be 0 based index
        int len = r - l + 1;
        int k = log2(len);
        return gcd(t[l][k], t[l + len - (1 << k)][k]);
    }
};