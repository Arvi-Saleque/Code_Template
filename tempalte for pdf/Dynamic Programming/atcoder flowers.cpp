ll t[4*N + 10];
void upd(int n, int b, int e, int i, ll x) {
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
ll query(int nd,int b,int e,int i,int j) {
    if(j < b || e < i) return -1e18;
    if(i <= b && e <= j) return t[nd];
    int mid = (b+e) >> 1, l = (nd << 1), r = l | 1;
    return max(query(l,b,mid,i,j),query(r,mid+1,e,i,j));
}
int h[N], a[N];
ll dp[N];
void solve() {
    int n;
    cin >> n;
    for(int i=1;i<=n;i++) {
        cin >> h[i];
    }
    for(int i=1;i<=n;i++) {
        cin >> a[i];
    }
    for(int i=1;i<=n;i++) {
        dp[i] = a[i];
        /*ll mx = 0;
        for(int j=1;j<i;j++) {
            if(h[j] < h[i]) {
                mx = max(mx, dp[j]);
            }
        }
        dp[i] = max(mx + a[i], dp[i]);*/
        // optimize the loop using segment tree
        if(h[i] != -1) {
            ll mx = query(1,1,n,1,h[i]-1);
            mx += a[i];
            dp[i] = max(dp[i], mx);
        }
        upd(1,1,n,h[i],dp[i]);
    }
    ll ans = 0;
    for(int i=1;i<=n;i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << "\n";
} 