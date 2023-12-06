#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;

const int N = 1e6 + 9;
const int mod1 = 127657753, mod2 = 987654319;
const int p1 = 137, p2 = 277;

// return how many times pat string occur in str string 

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
        assert(i <= j);
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

void solve() {
    string str, pat;
    cin >> str >> pat;
    Hash_node node(str);
    pair<int,int> patHashVal({0, 0});
    for(int i = 0; i < pat.size(); i++) {
        patHashVal.first += 1LL * pat[i] * pw[i].first % mod1;
        patHashVal.first %= mod1;
        patHashVal.second += 1LL * pat[i] * pw[i].second % mod2;
        patHashVal.second %= mod2;
    }
    int ans = 0, n = str.size(), m = pat.size();
    for(int i = 0; i + m - 1 < n; i++) {
        if(patHashVal == node.getHash(i, i + m -1)) ans++;
    }
    cout << ans << "\n";
}   
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    preCalc();
    int t = 1, cs = 1;
    //cin >> t;
    while(t--) {
        //cout << "Case " << cs++ << ": ";
        solve();
    }
    return 0;
}