const int N = 1e6 + 9;
const int mod1 = 127657753, mod2 = 987654319;
const int p1 = 137, p2 = 277;
// take all hash stuffs from hash + seg tree
bool check(int i,int j, hashNode &nd, hashNode &rnd) {
    return (nd.getHash(i, j) == rnd.getHash(nd.n - j - 1, nd.n - i - 1));
}
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    hashNode nd(s);
    string t = s;
    reverse(t.begin(), t.end());
    hashNode rnd(t);
    int odd[n], ev[n];
    for(int st = 0; st < n; st++) {
        int l = 0, r = min(st, n - st - 1), ans = 0;
        while(l <= r) {
            int mid = l + r >> 1;
            if(check(st - mid, st + mid, nd, rnd)) {
                ans = mid;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        odd[st] = ans;
    }
    for(int st = 0; st < n; st++) {
        int l = 0, r = min(st, n - st), ans = 0;
        while(l <= r) {
            int mid = l + r >> 1;
            if(check(st - mid, st + mid - 1, nd, rnd)) {
                ans = mid;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        ev[st] = ans;
    }

    int maxLen = 0, ansL, ansR;
    for(int i = 0; i < n; i++) {
        int len = 2 * odd[i] + 1;
        if(len > maxLen) {
            maxLen = len;
            ansL = i - odd[i], ansR = i + odd[i];
        }
    }
    for(int i = 0; i < n; i++) {
        int len = 2 * ev[i];
        if(len > maxLen) {
            maxLen = len;
            ansL = i - ev[i], ansR = i + ev[i] - 1;
        }
    }
    cout << s.substr(ansL, ansR - ansL + 1) << "\n";
}