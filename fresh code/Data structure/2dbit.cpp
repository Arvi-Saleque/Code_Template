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