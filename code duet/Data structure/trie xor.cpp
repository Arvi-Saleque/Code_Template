struct Trie {
  static const int B = 31;
  struct node {
    node* nxt[2];
    int sz;
    node() {
      nxt[0] = nxt[1] = NULL;
      sz = 0;
    }
  }*root;
  Trie() {
    root = new node();
  }
  void insert(int val) {
    node* cur = root;
    cur -> sz++;
    for (int i = B - 1; i >= 0; i--) {
      int b = val >> i & 1;
      if (cur -> nxt[b] == NULL) 
        cur -> nxt[b] = new node();
      cur = cur -> nxt[b];
      cur -> sz++;
    }
  }
  // number of values s.t. val ^ x < k
  int query(int x, int k) { 
    node* cur = root;
    int ans = 0;
    for (int i = B - 1; i >= 0; i--) {
      if (cur == NULL) break;
      int b1 = x >> i & 1, b2 = k >> i & 1;
      if (b2 == 1) {
        if (cur -> nxt[b1]) 
          ans += cur -> nxt[b1] -> sz;
        cur = cur -> nxt[!b1];
      } else cur = cur -> nxt[b1];
    }
    return ans;
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
            // get_min()
            if (cur->next[d]) {
                cur = cur->next[d];
            } else {
                // forced to take the opposite branch → XOR‑bit = 1
                ans |= (1 << i);
                cur = cur->next[!d];
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
    for (int i = 0; i < 2; i++) 
      if (cur -> nxt[i]) del(cur -> nxt[i]);
    else delete(cur);
  }
} t;