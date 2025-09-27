struct BIT2D {
long long M[N][N][2], A[N][N][2];
BIT2D() {
  memset(M, 0, sizeof M);
  memset(A, 0, sizeof A);
}
void upd2(long long t[N][N][2], int x, 
  int y, long long mul, long long add) {
  for(int i = x; i < N; i += i & -i) {
    for(int j = y; j < N; j += j & -j) {
      t[i][j][0] += mul;
      t[i][j][1] += add;
    }
  }
}
void upd1(int x, int y1, int y2, 
  long long mul, long long add) {
  upd2(M, x, y1, mul, -mul * (y1 - 1));
  upd2(M, x, y2, -mul, mul * y2);
  upd2(A, x, y1, add, -add * (y1 - 1));
  upd2(A, x, y2, -add, add * y2);
}
void upd(int x1, int y1, int x2, 
  int y2, long long val) {
  upd1(x1, y1, y2, val, -val * (x1 - 1));
  upd1(x2, y1, y2, -val, val * x2);
}
long long query2(long long t[N][N][2], 
  int x, int y) {
  long long mul = 0, add = 0;
  for(int i = y; i > 0; i -= i & -i) {
    mul += t[x][i][0];
    add += t[x][i][1];
  }
  return mul * y + add;
}
long long query1(int x, int y) {
  long long mul = 0, add = 0;
  for(int i = x; i > 0; i -= i & -i) {
    mul += query2(M, i, y);
    add += query2(A, i, y);
  }
  return mul * x + add;
}
long long query(int x1, int y1, 
  int x2, int y2) {
  return query1(x2, y2) - query1(x1 - 1, y2)
   - query1(x2, y1 - 1) + query1(x1 - 1, y1 - 1);
}
} t;
void solve() {
int n, q; 
cin >> n >> q;
char gr[n+1][n+1];
for(int i = 1; i <= n; i++) {
  for(int j = 1; j <= n; j++) {
      cin >> gr[i][j];
    int k;
    if(gr[i][j] == '.') k = 0;
    else k = 1;
    t.upd(i, j, i, j, k);
  }
}
while(q--) {
  int ty, x1, y1, x2, y2;
  cin >> ty;
  if(ty == 1) {
      cin >> x1 >> y1;
      if(gr[x1][y1] == '.') {
          t.upd(x1, y1, x1, y1, 1);
          gr[x1][y1] = '*';
      }
      else {
          t.upd(x1, y1, x1, y1, -1);
          gr[x1][y1] =  '.';
      }
  }
  else {
      cin >> x1 >> y1 >> x2 >> y2;
      cout << t.query(x1, y1, x2, y2) << '\n';   
  }
}
}

return cnt > x and prod of values > x from L....R
  struct _2dbit {
    struct BITadd {
        vector<int> v;
        int n;
        BITadd(){}
        BITadd(int n) : n(n) {
            v.resize(n + 1);
        }
        void upd(int i, int val) {
            for(; i <= n; i += (i & -i)) {
                v[i] += val;
            }
        }
        ll query(int i) {
            ll ans = 0;
            for(; i > 0; i -= (i & -i)) {
                ans += v[i];
            }
            return ans;
        }
    };
    struct BITmul {
        vector<int> v;
        int n;
        BITmul(){}
        BITmul(int n) : n(n) {
            v.resize(n + 1, 1);
        }
        void upd(int i, int val) {
            for(; i <= n; i += (i & -i)) {
                v[i] = (1LL * v[i] * val) % mod;
            }
        }
        ll query(int i) {
            ll ans = 1;
            for(; i > 0; i -= (i & -i)) {
                ans = (1LL * ans * v[i]) % mod;
            }
            return ans;
        }
    };
    vector<vector<int>> cords;
    vector<BITadd> cnt;
    vector<BITmul> prod;
    int n;
    _2dbit(int n) : n(n) {
        cords.resize(n + 1);
        cnt.resize(n + 1);
        prod.resize(n + 1);
    }
    void add(int i, int val) {
        for(; i <= n; i += (i & -i)) {
            cords[i].push_back(val);
        }
    }
    void build() {
        for(int i = 1; i <= n; i++) {
            auto &v = cords[i];
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
            cnt[i] = BITadd(v.size());
            prod[i] = BITmul(v.size());
        }
    }
    int getidx(int p, int x) {
        auto &v = cords[p];
        return (lower_bound(v.begin(), v.end(), x) - v.begin() + 1);
    }
    void upd(int i, int val, int delta) {
        for(; i <= n; i += (i & -i)) {
            int id = getidx(i, val);
            cnt[i].upd(id, delta);
            if(delta == 1) prod[i].upd(id, val % mod);
            else prod[i].upd(id, invmod(val));
        }
    }
    array<ll, 2> query(int i, int x) {
        array<ll, 2> ans = {0, 1};
        for(; i > 0; i -= (i & -i)) {
            int id = getidx(i, x);
            int sz = cords[i].size();
            if(id <= sz) {
                ll tot = prod[i].query(sz);
                ll less = prod[i].query(id - 1);
                ll val = (tot * invmod(less)) % mod;
                int ctot = cnt[i].query(sz);
                int cless = cnt[i].query(id - 1);
                int cval = ctot - cless;
                ans[0] += cval;
                ans[1] = (ans[1] * val) % mod;
            }
        }
        return ans;
    }
    array<ll, 2> rangeQ(int l, int r, int x) {
        auto tot = query(r, x);
        auto less = query(l - 1, x);
        array<ll, 2> res = {0, 1};
        res[0] = (tot[0] - less[0]);
        res[1] = (tot[1] * invmod(less[1])) % mod;
        return res;
    }
};
