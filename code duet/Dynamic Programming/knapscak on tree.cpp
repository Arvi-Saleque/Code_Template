vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, neg));
function<void(int, int)> dfs = [&](int u, int p) -> void {
    dp[u][1] = cost[u];
    for(auto v : g[u]) if ( v != p) {
        dfs(v, u);
        vector<ll> ndp(k + 1, neg);
        for(int x = 1; x <= k; x++) {
            if(dp[u][x] == neg) continue;
            for(int y = 0; x + y <= k; y++) {
                if(dp[v][y] == neg) continue;
                ndp[x + y] = max(ndp[x + y], dp[u][x] + dp[v][y]);
            }
        }   
        for(int i = 1; i <= k; i++) {
            dp[u][i] = max(ndp[i], dp[u][i]);
        }
    }
};

vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(3, vector<ll>(x + 1, 0)));
function<void(int, int)> dfs = [&](int u, int p) -> void {   
    vector<vector<ll>> cur(3, vector<ll>(x + 1, 0));
    cur[0][0] = k - 1;
    cur[1][1] = 1;
    cur[2][0] = m - k;
    for(auto v : g[u]) if(v != p) {
        dfs(v, u);
        vector<vector<ll>> new_cur(3, vector<ll>(x + 1, 0));
        for(int su = 0; su <= 2; su++) {
            for(int sv = 0; sv <= 2; sv++) {
                for(int c1 = 0; c1 <= x; c1++) {
                    for(int c2 = 0; c1 + c2 <= x; c2++) {
                        if(su == 1 && sv != 0) continue;
                        if(su != 0 && sv == 1) continue;
                        new_cur[su][c1 + c2] = (new_cur[su][c1 + c2] + (cur[su][c1] * dp[v][sv][c2]) % mod) % mod;
                    }
                }
            }
        }
        swap(cur, new_cur);
    }
    for(int s = 0; s <= 2; s++) {
        for(int c = 0; c <= x; c++) {
            dp[u][s][c] = cur[s][c];
        }
    }
};