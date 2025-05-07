struct Trie
{
    const int B = 31;
    struct node {
        node *next[2];
        int sz;
        node() {
            next[0] = next[1] = nullptr; 
            sz = 0;
        }
    };
    typedef node* pnode;
    pnode root = new node();
 
    void insert(int val) {
        auto cur = root;
        cur->sz++;
        for(int i = B - 1; i >= 0; i--) {
            int d = (val >> i) & 1;
            if(cur->next[d] == nullptr) {
                cur->next[d] = new node();
            }
            cur = cur->next[d];
            cur->sz++;
        }
    }
 
    int calc(int val) {
        auto cur = root;
        for(int i = B - 1; i >= 0; i--) {
            int d = (val >> i) & 1;
            if(cur->next[d] == nullptr) return 0;
            cur = cur->next[d];
        }
        return cur->sz;
    }
 
    int get_max(int val) {
        auto cur = root;
        int ans = 0;
        for(int i = B - 1; i >= 0; i--) {
            int d = (val >> i) & 1;
            if(cur->next[!d]) {
                ans |= (1 << i);
                cur = cur->next[!d];
            }
            else {
                cur = cur->next[d];
            }
        }
        return ans;
    }
 
    void remove_val(int val) {
        node* cur = root;
        cur->sz--; 
        for (int i = B - 1; i >= 0; i--) {
            int b = (val >> i) & 1;
            node* next = cur->next[b];
            next->sz--;
            if (next->sz == 0) {
                cur->next[b] = NULL;
                del(next);
                return;
            }
            cur = next;
        }
    }
 
    void del(node* cur) {
        for(int i = 0; i < 2; i++) {
            if(cur->next[i]) {
                del(cur->next[i]);
            }
        }
        delete cur;
    }
 
    ~Trie() {
        del(root);
    }
};

class Trie {
public:
    class node    {
    public:
        node *child[27];
        int leaf, sz;
        node() {
            for(int i = 0; i < 27; i++) {
                child[i] = nullptr;
            }
            sz = 0;
            leaf = 0;
        }
    } *root;
    Trie () {
        root = new node();
    }
    void insert(string s) {
        node *cur = root;
        for(auto x : s) {
            int id = x - 'a';
            if(cur->child[id] == nullptr) {
                cur->child[id] = new node();
            }
            cur = cur->child[id];
            cur->sz++;
        }
        cur->leaf++;
    }
    void remove(string s) {
        stack<pair<node *, int>> stck;
        node *cur = root;
        for(auto x : s) {
            int id = x - 'a';
            if(cur->child[id] == nullptr) break;
            stck.push({cur, id});
            cur = cur->child[id];
        }
        while(!stck.empty()) {
            auto [x, y] = stck.top();
            stck.pop();
            x->child[y]->sz--;
            if(x->child[y]->sz == 0) {
                x->child[y] = nullptr;
                delete(x->child[y]);
            }

        }
    }
    int findLCP(string s) {
        int cnt = 0;
        node *cur = root;
        for(auto x : s) {
            int id = x - 'a';
            if(cur->child[id] == nullptr) break;
            cnt++;
            cur = cur->child[id];
        }
        return cnt;
    }
};
void solve() {
    Trie mytrie;
    int n;
    cin >> n;
    vector<string> v;
    for(int i = 1; i <= n; i++) {
        string t; cin >> t;
        mytrie.insert(t);
        v.push_back(t);
    }
    for(auto x : v) {
        mytrie.remove(x);
        cout << mytrie.findLCP(x) << "\n";
        mytrie.insert(x);
    }

}  