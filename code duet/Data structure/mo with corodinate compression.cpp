int freq[N + 2]; // frequnecy array must be global
 
struct MO { // 0-based
 
    int n, q, cnt, bl_sz;
    vector<int> v, ans;
 
    struct Q {
        int l, r, idx;
    };
 
    vector<Q> queries;
 
    MO(){}
    MO(int n, int q) : n(n), q(q), cnt(0) {
        bl_sz = sqrt(n);
        v.assign(n, 0);
        ans.assign(q + 1, 0);
        take_input();
    }
 
    void take_input() {
        for(auto &x : v) {
            cin >> x;
            //freq[x] = 0;
        }
        compress();
        query_input();
    }
    void compress() {
        vector<int> tmp = v;
        sort(tmp.begin(), tmp.end());
        tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
        for(int i = 0; i < n; i++) {
            v[i] = lower_bound(tmp.begin(), tmp.end(), v[i]) - tmp.begin();
            freq[v[i]] = 0;
        }
    }
    void query_input() {
        for(int i = 1; i <= q; i++) {
            int l, r;
            cin >> l >> r;
            queries.push_back({--l, --r, i});
        }
        sort(queries.begin(), queries.end(), [&](const Q &a, const Q &b) {
            if (a.l / bl_sz != b.l / bl_sz) return a.l / bl_sz < b.l / bl_sz;
            return a.r < b.r;
        });
    }
    void add(int x) {
        if(freq[v[x]] == 0) cnt++;
        freq[v[x]]++;
    }
    void remove(int x) {
        if(freq[v[x]] == 1) cnt--;
        freq[v[x]]--;
    }
    void print() {
        for(int i = 1; i <= q; i++) {
            cout << ans[i] << "\n";
        }
    }
    void solve() {
        int cur_l = 0, cur_r = -1;
        for(auto qi : queries) {
            while(cur_l > qi.l) add(--cur_l);
            while(cur_r < qi.r) add(++cur_r);
            while(cur_l < qi.l) remove(cur_l++);
            while(cur_r > qi.r) remove(cur_r--);
            ans[qi.idx] = cnt;
        }
        print();
    }
};
