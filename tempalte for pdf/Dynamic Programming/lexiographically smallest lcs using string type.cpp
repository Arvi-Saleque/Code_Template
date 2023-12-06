string dp[N][N], a, b;
bool vis[N][N];
string lexiographically_smallest_lcs(int i,int j) {
    if(i == a.size() || j == b.size()) return "";
    if(vis[i][j]) return dp[i][j];
    vis[i][j] = 1;
    string &ans = dp[i][j];
    ans = "";
    if(a[i] == b[j]) {
        ans = string(1, a[i]) + lexiographically_smallest_lcs(i+1,j+1);
    }
    else {
        string x = lexiographically_smallest_lcs(i+1, j);
        string y = lexiographically_smallest_lcs(i, j+1);
        if(x.size() > y.size()) {
            ans = x;
        }
        else if(x.size() < y.size()) {
            ans = y;
        }
        else {
            ans = min(x, y);
        }
    }
    return ans;
}
void solve() {
    cin >> a >> b;
    memset(vis, 0, sizeof vis);
    string ans = lexiographically_smallest_lcs(0, 0);
    if(ans.empty()) ans = ":(";
    cout << ans << "\n";
} 