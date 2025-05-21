/*
if you need dfs on trie
at first make the trie an uniqe tree
inserting an unique id on each node
then just treat as node of a tree
*/
class Trie {
public:
    class node {
    public:
        node *child[27]; int leaf = 0, sz = 0, id = 0;
        node() { for(int i = 0; i < 27; i++) child[i] = nullptr; }
    } *root;

    vector<int> dis; int unqid = 1;

    Trie() { root = new node(); }

    void insert(string s) {
        auto cur = root;
        for(auto x : s) {
            int i = x - 'a' + 1;
            if(!cur->child[i]) cur->child[i] = new node();
            cur = cur->child[i]; cur->sz++; cur->id = unqid++;
        }
        cur->leaf++;
    }

    int dfs(node *cur) {
        dis[cur->id] = cur->leaf;
        for(int i = 1; i <= 26; i++)
            if(cur->child[i]) {
                dfs(cur->child[i]);
                dis[cur->id] = max(dis[cur->id], dis[cur->child[i]->id]);
            }
        return dis[cur->id];
    }

    pair<string, int> calc(string s) {
        node *cur = root;
        for(auto x : s) {
            int id = x - 'a' + 1;
            if(!cur->child[id]) return {"", -1};
            cur = cur->child[id];
        }
        pair<string, int> ans = {s, cur->leaf};
        while(1) {
            int node = -1, mx = ans.second;
            for(int i = 1; i <= 26; i++)
                if(cur->child[i] && dis[cur->child[i]->id] > mx)
                    mx = dis[cur->child[i]->id], node = i;
            if(node == -1) break;
            cur = cur->child[node];
            ans.first.push_back((char)(node + 'a' - 1));
            ans.second = cur->leaf;
        }
        return ans;
    }

    int get_max(int x) {
        auto cur = root; int ans = 0;
        for(int i = B - 1; i >= 0; i--) {
            int id = (x >> i) & 1;
            if(cur->child[!id]) ans += (1 << i), cur = cur->child[!id];
            else if(cur->child[id]) cur = cur->child[id];
            else break;
        }
        return ans;
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
        stack<pair<node *, int>> stck; auto cur = root;
        for(int i = B - 1; i >= 0; i--) {
            int id = (x >> i) & 1;
            stck.push({cur, id}); cur = cur->child[id];
        }
        while(!stck.empty()) {
            auto [par, id] = stck.top(); stck.pop();
            auto child = par->child[id];
            if(!child->child[0] && !child->child[1]) delete child, par->child[id] = nullptr;
            else break;
        }
    }

    void remove(int x) {
        if(occurence(x) == 1) { del(x); return; }
        auto cur = root;
        for(int i = B - 1; i >= 0; i--) {
            int id = (x >> i) & 1;
            cur = cur->child[id];
        }
        cur->leaf--;
    }

    void clear(node *cur) {
        if(!cur) return;
        for(int i = 0; i < 2; i++)
            if(cur->child[i]) clear(cur->child[i]);
        delete cur;
    }

    ~Trie() { clear(root); }
};

void solve() {
    Trie mytrie;
    for(int i = 1; i <= n; i++) {
        string t; cin >> t;
        mytrie.insert(t);
    }
    mytrie.dis.assign(mytrie.unqid + 1, 0);
    mytrie.dfs(mytrie.root);
}

// how many subarray Xor < k -> pre[x] ^ pre[y] < k
ll countLess(int y, int k) { // for greater total - countless
    auto cur = root; ll ans = 0;
    for(int i = B - 1; i >= 0 && cur; i--) {
        int yb = (y >> i) & 1, kb = (k >> i) & 1;
        if(kb == 1) {
            if(cur->child[yb]) ans += cur->child[yb]->cnt;
            cur = cur->child[!yb];
        } else cur = cur->child[yb];
    }
    return ans;
}
void solve() {
    Trie trie; ll pref = 0;
    trie.insert(0);
    for(auto x : v) {
        pref ^= x;
        ans += trie.countLess(pref, k);
        trie.insert(pref);
    }
    cout << ans << "\n";
}
