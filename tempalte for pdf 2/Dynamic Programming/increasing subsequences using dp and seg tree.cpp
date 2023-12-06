int t[4*N];
void upd(int n, int b, int e, int i, int x) {
    if (b > i || e < i) return;
    if (b == e && b == i) {
        t[n] = max(t[n], x);
        return;
    }
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    upd(l, b, mid, i, x);
    upd(r, mid + 1, e, i, x);
    t[n] = max(t[l], t[r]);
}
int query(int nd,int b,int e,int i,int j) {
    if(j < b || e < i) return -1e9;
    if(i <= b && e <= j) return t[nd];
    int mid = (b+e) >> 1, l = (nd << 1), r = l | 1;
    return max(query(l,b,mid,i,j),query(r,mid+1,e,i,j));
}
int a[N], dp[N];
void solve() {
    int n;
    cin >> n;
    // co-ordinate compression
    set<int> st;
    for(int i=1;i<=n;i++) {
        cin >> a[i];
        st.insert(a[i]);
    }
    map<int,int> mp;
    int id = 1;
    for(auto x : st) {
        mp[x] = id++;
    }
    for(int i=1;i<=n;i++) {
        a[i] = mp[a[i]];
    }
    // co-ordinate compression
    for(int i=1;i<=n;i++) {
        dp[i] = 1;
        // int mx = 0;
        // for (int j = 1; j < i; j++) {
        //   if (a[j] < a[i]) {
        //     mx = max(mx, dp[j]);
        //   }
        // }
        // optimized the loop
        if(a[i] != 1) {
            int mx = query(1,1,n,1,a[i]-1);
            mx++;
            dp[i] = max(dp[i], mx);
        }
        upd(1,1,n,a[i],dp[i]);
    }
    int ans = 0;
    for(int i=1;i<=n;i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << "\n";
} 