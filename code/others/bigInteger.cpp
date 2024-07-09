string mul(string a, string b) {
    int n = a.size(), m = b.size();
    if(n < m) {
        swap(n, m);
        swap(a, b);
    }
    vector<vector<char>> store(m, vector<char>(n + m + 1, '0'));
    reverse(b.begin(), b.end());
    reverse(a.begin(), a.end());
    for(int i = 0; i < m; i++) {
        int caryy = 0, db = b[i] - '0';
        for(int j = 0; j < n; j++) {
            int da = a[j] - '0';
            int val = da * db + caryy;
            store[i][i + j] = (val % 10 + '0');
            caryy = (val / 10);
        }
        if(caryy > 0) {
            store[i][n + i] = (caryy + '0');
        }
    }
    string ans(n + m + 1, '0');
    int caryy = 0;
    for(int j = 0; j < n + m + 1; j++) {
        int sum = 0;
        for(int i = 0; i < m; i++) {
            sum += (store[i][j] - '0');
        }
        sum += caryy;
        ans[j] = (sum % 10 + '0');
        caryy = sum / 10;
    }
    while(ans.back() == '0') ans.pop_back();
    reverse(ans.begin(), ans.end());
    return ans;
}
string add(string a, string b) {
    int n = a.size(), m = b.size();
    if(n < m) {
        swap(n, m);
        swap(a, b);
    }
    string ans(n + m + 1, '0');
    reverse(b.begin(), b.end());
    reverse(a.begin(), a.end());
    int caryy = 0;
    for(int i = 0; i < m; i++) {
        int sum = (a[i] - '0') + (b[i] - '0') + caryy;
        ans[i] = (sum % 10 + '0');
        caryy = sum / 10;
    }
    for(int i = m; i < n; i++) {
        int sum = (a[i] - '0') + caryy;
        ans[i] = (sum % 10 + '0');
        caryy = sum / 10;
    }
    if(caryy > 0) {
        ans[n] = (caryy + '0');
    }
    while(ans.back() == '0') ans.pop_back();
    reverse(ans.begin(), ans.end());
    return ans;
}
