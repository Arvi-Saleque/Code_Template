// https://vjudge.net/problem/Gym-104857C
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int mod = 998244353;

struct palindromic_tree {
    struct node {
        int len, link;
        int occ, occ1;      // occ: total in s+s, occ1: only in first n0
        array<int, 10> next;
        node(int l = 0) : len(l), link(0), occ(0), occ1(0) {
            next.fill(-1);
        }
    };
    string s;
    vector<node> t;
    int last;
    int n0;                // original length (first-half cutoff)

    palindromic_tree() {}
    palindromic_tree(string _s, int _n0) {
        s = _s; n0 = _n0;
        t.clear();
        t.reserve((int)s.size() + 3);
        t.push_back(node(-1));
        t.push_back(node(0));
        t[0].link = 0;
        t[1].link = 0;
        last = 1;
    }
    int getlink(int u, int i) {
        while (true) {
            int idx = i - 1 - t[u].len;
            if (idx >= 0 && s[idx] == s[i]) return u;
            u = t[u].link;
        }
    }
    int add(int i) {
        int u = getlink(last, i);
        int ch = s[i] - '0';
        if (t[u].next[ch] != -1) {
            last = t[u].next[ch];
            t[last].occ++;
            if (i < n0) t[last].occ1++;   // count only in first n0 for non-wrap
            return 0;
        }
        int llen = t[u].len + 2;
        node nu(llen);
        t.push_back(nu);
        int v = (int)t.size() - 1;
        t[u].next[ch] = v;

        if (t[v].len == 1) {
            t[v].link = 1;
        } else {
            int w = t[u].link;
            w = getlink(w, i);
            t[v].link = t[w].next[ch];
        }
        last = v;
        t[last].occ = 1;
        if (i < n0) t[last].occ1 = 1;
        return 1;
    }
    void pushOcc() {
        for (int v = (int)t.size() - 1; v >= 2; --v) {
            int p = t[v].link;
            t[p].occ  += t[v].occ;
            t[p].occ1 += t[v].occ1;
        }
    }
};

void solve() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n0; 
    cin >> n0;
    string s; 
    cin >> s;

    string ds = s + s;                 // build on s+s once
    palindromic_tree tree(ds, n0);
    int n = (int)ds.size();
    for (int i = 0; i < n; ++i) tree.add(i);
    tree.pushOcc();

    ll ans = 0;
    for (int i = 2; i < (int)tree.t.size(); ++i) {
        int len = tree.t[i].len;
        if (len > n0) continue;        // cyclic substrings must have len ≤ n0
        long long f = (long long)tree.t[i].occ - (long long)tree.t[i].occ1; // f_circular
        f %= mod; if (f < 0) f += mod;
        long long add = (f * f) % mod;
        add = (add * len) % mod;
        ans += add;
        if (ans >= mod) ans -= mod;
    }
    cout << ans % mod << "\n";
}

int main() {
    solve();
    return 0;
}
