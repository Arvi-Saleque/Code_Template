struct node
{
    int st, en, cost;
    node(){};
    node(int _s, int _e, int _c) {
        st = _s;
        en = _e;
        cost = _c;
    }
};
vector<node> vec;
vector<pair<int,int>> store;
bool cmp(node a, node b) {
    return (a.st == b.st) ? (a.en < b.en) : a.st < b.st;
}
ll dp[N];
/*ll maxMoney(int pos) {
    if(pos == n) return 0;
    ll &ans = dp[pos];
    if(ans != -1) return ans;
    ans = 0;
    if(pos == n - 1) {
        ans = vec[pos].cost;
    }
    else {
        ans = maxMoney(pos + 1);
        if(idx == n) {
            ans = max(ans, 1LL*vec[pos].cost);
        }
        else {
            ans = max(ans, vec[pos].cost + maxMoney(idx));
        }
    }
    return ans;
}*/
void solve() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        vec.push_back({a, b, c});
    }
    sort(vec.begin(), vec.end(), cmp);
    for(int i = 0; i < vec.size(); i++) {
        store.push_back({vec[i].st, i});
        //cout << vec[i].st << " " << vec[i].en << " " << vec[i].cost << "\n";
    }
    /*auto pos = lower_bound(store.begin(), store.end(), make_pair(6, 10));
    cout << pos - store.begin() << "\n";*/
    for(int i = n; i >= 0; i--) {
        if(i == n) {
            dp[i] = 0;
        }
        else {
            dp[i] = dp[i+1];
            int idx = lower_bound(store.begin(), store.end(), make_pair(vec[i].en, inf)) - store.begin();
            if(idx == n) {
                dp[i] = max(dp[i], 1LL * vec[i].cost);
            }
            else {
                dp[i] = max(dp[i], vec[i].cost + dp[idx]);
            }
        }
    }
    ll mx = 0;
    for(int i = 0; i < n; i++) {
        mx = max(mx, dp[i]);
    }
    cout << mx << "\n";
} 