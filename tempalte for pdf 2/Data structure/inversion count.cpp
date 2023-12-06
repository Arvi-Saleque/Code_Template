void solve() {
    int n;
    cin >> n;
    int a[n];
    for(int i=0;i<n;i++) {
        cin >> a[i];
    }
    o_set<int> ost;
    ll ans = 0;
    for(int i=n-1;i>=0;i--) {
        ans += ost.order_of_key(a[i]);
        ost.insert(a[i]);
    }
    cout << ans << "\n";
} 