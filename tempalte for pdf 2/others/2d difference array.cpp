/*
2d differences array 
*/
void solve() {
    int n, m;
    cin >> n >> m;
    char grid[n + 1][m + 1];
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> grid[i][j];
        }
    }
    int q; cin >> q;
    int pre[n + 2][m + 2] = {0};
    while(q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        pre[x1][y1]++;
        pre[x2 + 1][y2 + 1]++;
        pre[x1][y2 + 1]--;
        pre[x2 + 1][y1]--;
    }
    for(int i = 1; i <= m; i++) {
        for(int j = 2; j <= n; j++) {
            pre[j][i] += pre[j - 1][i];
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 2; j <= m; j++) {
            pre[i][j] += pre[i][j - 1];
        }
    }   
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            sum += pre[i][j];
        }
    } 
}