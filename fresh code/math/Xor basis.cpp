#include <bits/stdc++.h>
using namespace std;

/* -----------------------------------------------------------
   Gaussian elimination over GF(2)
   - a: K × (N+1) matrix, last column is RHS (all 0’s here)
   - where[j] = pivot-row that solves variable j, or −1 if free
   returns rank (= #pivot columns); matrix a is left in row-echelon form
   ----------------------------------------------------------- */
int gauss_xor(vector<vector<int>>& a, vector<int>& where) {
    int n = a.size();          // rows   (K)
    int m = a[0].size() - 1;   // cols   (N)
    where.assign(m, -1);

    int row = 0;
    for (int col = 0; col < m && row < n; ++col) {
        int sel = -1;
        for (int i = row; i < n; ++i)
            if (a[i][col]) { sel = i; break; }
        if (sel == -1) continue;           // no pivot in this column

        swap(a[row], a[sel]);
        where[col] = row;

        for (int i = 0; i < n; ++i)
            if (i != row && a[i][col])
                for (int j = col; j <= m; ++j)
                    a[i][j] ^= a[row][j];  // eliminate
        ++row;
    }
    return row;                            // rank
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    if (!(cin >> N >> K)) return 0;
    vector<string> A(N);
    for (int i = 0; i < N; ++i) cin >> A[i];

    /* -----------------------------------------------------------
       Build K × (N+1) matrix: row = bit, column = player
       ----------------------------------------------------------- */
    vector<vector<int>> mat(K, vector<int>(N + 1, 0));
    for (int p = 0; p < N; ++p)
        for (int b = 0; b < K; ++b)
            mat[b][p] = (A[p][b] == '1');

    /* -----------------------------------------------------------
       Gaussian elimination, keep pivot information
       ----------------------------------------------------------- */
    vector<int> where;
    int rank = gauss_xor(mat, where);
    int free_cnt = N - rank;
    if (free_cnt == 0) { cout << "*\n"; return 0; }

    /* -----------------------------------------------------------
       Build null-space basis (one vector per free variable)
       ----------------------------------------------------------- */
    vector<vector<int>> basis;
    for (int col = 0; col < N; ++col) if (where[col] == -1) {
        vector<int> v(N, 0);
        v[col] = 1;                        // set this free var to 1
        /* back-substitute pivot variables */
        for (int c = N - 1; c >= 0; --c) if (where[c] != -1) {
            int r = where[c], sum = 0;
            for (int d = c + 1; d < N; ++d)
                if (mat[r][d] && v[d]) sum ^= 1;
            v[c] = sum;                   // because RHS is 0
        }
        basis.push_back(std::move(v));
    }

    auto weight = [&](const vector<int>& v) {
        return accumulate(v.begin(), v.end(), 0);
    };

    /* -----------------------------------------------------------
       Pick an even-weight, non-zero combination
       ----------------------------------------------------------- */
    vector<int> pick(N, 0);

    /* 1) a single even-weight vector */
    for (auto& v : basis) {
        int w = weight(v);
        if (w >= 2 && (w & 1) == 0) { pick = v; break; }
    }

    /* 2) XOR of two odd-weight basis vectors */
    if (weight(pick) == 0 && basis.size() >= 2) {
        for (size_t i = 0; i < basis.size() && weight(pick) == 0; ++i)
            if (weight(basis[i]) & 1)
                for (size_t j = i + 1; j < basis.size(); ++j)
                    if (weight(basis[j]) & 1) {
                        vector<int> tmp(N);
                        for (int c = 0; c < N; ++c)
                            tmp[c] = basis[i][c] ^ basis[j][c];
                        int w = weight(tmp);
                        if (w >= 2 && (w & 1) == 0) { pick = tmp; break; }
                    }
    }

    /* 3) single odd vector + an all-zero player */
    if (weight(pick) == 0 && !basis.empty()) {
        int zero_player = -1;
        for (int i = 0; i < N; ++i)
            if (A[i].find('1') == string::npos) { zero_player = i; break; }
        if (zero_player != -1 && basis[0][zero_player] == 0) {
            pick = basis[0];
            pick[zero_player] = 1;         // toggles parity → even
        }
    }

    int w = weight(pick);
    if (w == 0 || (w & 1)) { cout << "*\n"; return 0; }

    /* -----------------------------------------------------------
       Split selected players into two equal teams
       ----------------------------------------------------------- */
    vector<int> idx;
    for (int i = 0; i < N; ++i) if (pick[i]) idx.push_back(i);
    int half = w / 2;
    string out(N, '0');
    for (int i = 0; i < half; ++i)             out[idx[i]] = '1';
    for (int i = half; i < w; ++i)             out[idx[i]] = '2';
    cout << out << '\n';
    return 0;
}
