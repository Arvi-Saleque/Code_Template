// https://codeforces.com/contest/706/problem/D

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e7 + 9, mod = 998244353; 
 
struct Trie {
    const int B = 30;
    struct node { // 1 based
        node *child[2];
        int leaf;
        node() {
            child[0] = child[1] = 0;
            leaf = 0;
        }
    } *root;
    
    Trie () {
        root = new node();
    }

    void insert(int x) {
        auto cur = root;
        for(int i = B - 1; i >= 0; i--) {
            int id = (x >> i) & 1;
            if(!cur->child[id]) cur->child[id] = new node();
            cur = cur->child[id];
        }
        cur->leaf++;
    }

    int occurence(int x) {
        auto cur = root;
        for(int i = B - 1; i >= 0; i--) {
            int id = (x >> i) & 1;
            if(!cur->child[id]) return 0;
            cur = cur->child[id];
        }
        return cur->leaf;
    }

    void del(int x) {
        stack<pair<node *, int>> stck;
        auto cur = root;
        for(int i = B - 1; i >= 0; i--) {
            int id = (x >> i) & 1;
            stck.push({cur, id});
            cur = cur->child[id];
        }   
        while(not stck.empty()) {
            auto [par, id] = stck.top();
            stck.pop();
            auto child = par->child[id];
            if(!child->child[0] && !child->child[1]) {
                delete child;
                par->child[id] = nullptr;
            }
            else {
                break;
            }
        }
    }

    void remove(int x) {
        if(occurence(x) == 1) {
            del(x);
            return;
        }
        auto cur = root;
        for(int i = B - 1; i >= 0; i--) {
            int id = (x >> i) & 1;
            cur = cur->child[id];
        }
        cur->leaf--;
    }

    int get_max(int x) {
        auto cur = root;
        int ans = 0;
        for(int i = B - 1; i >= 0; i--) {
            int id = (x >> i) & 1;
            if(cur->child[!id]) {
                //cout << i << " " << id << " " << sz << "\n";
                ans += (1 << i);
                cur = cur->child[!id];
            }
            else if(cur->child[id]){
                cur = cur->child[id];
            }
            else break;
        }
        return ans;
    }

} trie;

void solve() {
    int q; cin >> q;
    trie.insert(0);

    while(q--) {
        char ch; cin >> ch;
        if(ch == '+') {
            int x; cin >> x;
            trie.insert(x);
        }
        else if(ch == '-') {
            int x; cin >> x;
            trie.remove(x);
        }
        else {
            int x; cin >> x;
            cout << trie.get_max(x) << "\n";
        }
    }
}  
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tc = 1, cs = 1;
    //cin >> tc;
    while(tc--) {
        //cout << "Case " << cs++ << ": " << "\n";
        solve();
    }
} 
