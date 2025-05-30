const int N = 1e4 + 9;
const int mod1 = 127657753, mod2 = 987654319;
const int p1 = 137, p2 = 277;

pair<int,int> pw[N], invpw[N];
int bigMod(int a,int b,int mod) {
    int ans = 1;
    while(b) {
        if(b & 1) {
            ans = 1LL * ans * a % mod;
        }
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return (ans % mod);
}
void preCalc() {
    pw[0] = {1, 1};
    for(int i = 1; i < N; i++) {
        pw[i].first = 1LL * pw[i-1].first * p1 % mod1;
    } 
    for(int i = 1; i < N; i++) {
        pw[i].second = 1LL * pw[i-1].second * p2 % mod2;
    } 
    int invpw1 = bigMod(p1, mod1 - 2, mod1);
    int invpw2 = bigMod(p2, mod2 - 2, mod2);
    invpw[0] = {1, 1};
    for(int i = 1; i < N; i++) {
        invpw[i].first = 1LL * invpw[i-1].first * invpw1 % mod1;
        invpw[i].second = 1LL * invpw[i-1].second * invpw2 % mod2;
    }
}

class hashNode
{
public:
    int n;
    string str;
    vector<pair<int,int>> prehs;
    hashNode(){}
    hashNode(string s) {
        str = s;
        n = s.size();
        prehs.resize(n);
        prehs[0].first = 1LL * s[0] * pw[0].first % mod1;
        prehs[0].second = 1LL * s[0] * pw[0].second % mod2;
        for(int i = 1; i < n; i++) {
            prehs[i].first = prehs[i - 1].first + (1LL * s[i] * pw[i].first % mod1);
            prehs[i].first %= mod1;
            prehs[i].second = prehs[i - 1].second + (1LL * s[i] * pw[i].second % mod2);
            prehs[i].second %= mod2;
        }
    }
    pair<int,int> getHash(int i,int j) {
        //assert(i <= j);
        pair<int,int> ans{0, 0};
        if(i == 0) {
            ans.first = 1LL * prehs[j].first * invpw[i].first % mod1;
            ans.second = 1LL * prehs[j].second * invpw[i].second % mod2;
        }
        else {
            ans.first = (prehs[j].first - prehs[i-1].first + mod1) % mod1;
            ans.first = 1LL * ans.first * invpw[i].first % mod1;
            ans.second = (prehs[j].second - prehs[i-1].second + mod2) % mod2;
            ans.second = 1LL * ans.second * invpw[i].second % mod2;
        }
        return ans;
    }
};

bool is_palindrome(int i,int j, hashNode &nd, hashNode &rnd) {
    return (nd.getHash(i, j) == rnd.getHash(nd.n - j - 1, nd.n - i - 1));
}

// Compare two substrings given by (l1, r1) and (l2, r2).
// We convert them to 0-indexed positions.
bool cmpSubstr(const Substring &a, const Substring &b) {
    int l1 = a.l - 1, r1 = a.r - 1;
    int l2 = b.l - 1, r2 = b.r - 1;
    int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
    int L = min(len1, len2);
    
    // Binary search for longest common prefix length.
    int lo = 0, hi = L;
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;
        if (getHash(l1, l1 + mid - 1) == getHash(l2, l2 + mid - 1))
            lo = mid;
        else
            hi = mid - 1;
    }
    int lcp = lo;
    if(lcp == L) {
        // one is a prefix of the other, or they are equal.
        if(len1 == len2)
            return (a.l != b.l ? a.l < b.l : a.r < b.r); // tie-break by positions.
        return len1 < len2;
    }
    // Compare the first differing character.
    return s[l1 + lcp] < s[l2 + lcp];
}