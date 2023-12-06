const int N = 5005;
string str;
ll dp[N][N];
bool isPalindrome[N][N]; 
void solve() {
    cin >> str;
    int n = str.size();
    for(int i = 1; i <= n; i++) {
        dp[i][i] = 1;
        isPalindrome[i][i] = 1;
        if(i != 1) {
            if(str[i - 2] == str[i - 1]) {
                dp[i - 1][i] = 3;
                isPalindrome[i - 1][i] = 1;
            }
            else dp[i - 1][i] = 2;
        }
    }

    for(int len = 3; len <= n; len++) {
        for(int i = len; i <= n; i++) {
            int l = i - len + 1, r = i;
            isPalindrome[l][r] = (str[l - 1] == str[r - 1]) && isPalindrome[l + 1][r - 1];
        }
    }

    for(int len = 3; len <= n; len++) {
        for(int i = len; i <= n; i++) {
            int l = i - len + 1, r = i;
            dp[l][r] = (dp[l + 1][r] + dp[l][r - 1] - dp[l + 1][r - 1]) + isPalindrome[l][r];
        }
    }

    int q; cin >> q;
    while(q--) {
        int l, r;
        cin >> l >> r;
        cout << dp[l][r] << "\n";
    }
} 