// SuffixArray struct built using the doubling method and Kasai's algorithm.
// Includes computation of suffix array, LCP array, and substring distribution.
struct SuffixArray {
    string s;
    int n;
    vector<int> sa;   // sa[i]: starting index of the i-th smallest suffix
    vector<int> lcp;  // lcp[i]: LCP between sa[i] and sa[i+1]

    // Constructor: initializes and builds suffix array and LCP
    SuffixArray(const string &str) : s(str), n(str.size()) {
        buildSA();
        buildLCP();
    }

    // Builds the suffix array using the doubling method in O(n log n)
    void buildSA() {
        sa.resize(n);
        vector<int> rank(n), tmp(n);
        iota(sa.begin(), sa.end(), 0); // sa = [0, 1, ..., n-1]
        for (int i = 0; i < n; i++) rank[i] = s[i];

        for (int k = 1; k < n; k *= 2) {
            auto cmp = [&](int i, int j) {
                if (rank[i] != rank[j]) return rank[i] < rank[j];
                int ri = (i + k < n) ? rank[i + k] : -1;
                int rj = (j + k < n) ? rank[j + k] : -1;
                return ri < rj;
            };

            sort(sa.begin(), sa.end(), cmp);

            tmp[sa[0]] = 0;
            for (int i = 1; i < n; i++)
                tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
            rank = tmp;
        }
    }

    // Builds the LCP (Longest Common Prefix) array in O(n)
    void buildLCP() {
        lcp.resize(n);
        vector<int> inv(n);
        for (int i = 0; i < n; i++) inv[sa[i]] = i;

        int k = 0;
        lcp[n - 1] = 0;
        for (int i = 0; i < n; i++) {
            if (inv[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = sa[inv[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[inv[i]] = k;
            if (k) k--;
        }
    }

    // Computes the number of distinct substrings of each length in the string
    // Returns a vector `dist` where dist[l] = number of distinct substrings of length l
    vector<int> computeDistribution() {
        vector<int> diff(n + 2, 0);
        for (int j = 0; j < n; j++) {
            int pos = sa[j];
            int prevLCP = (j == 0 ? 0 : lcp[j - 1]);
            int low = prevLCP + 1;
            int high = n - pos;
            if (low <= high) {
                diff[low]++;
                if (high + 1 <= n) diff[high + 1]--;
            }
        }
        vector<int> dist(n + 1, 0);
        for (int l = 1; l <= n; l++)
            dist[l] = dist[l - 1] + diff[l];
        return dist;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    string s;
    cin >> n >> m >> s;

    // === Preprocessing: Compute 2D F and prefix sum array PS ===

    // F[i][l] = number of distinct substrings of length l in suffix s[i-1...n-1]
    vector<vector<int>> F(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
        SuffixArray sa(s.substr(i - 1));
        vector<int> dist = sa.computeDistribution();
        for (int l = 1; l <= n; l++)
            F[i][l] = (l <= sa.n ? dist[l] : 0);
    }

    // PS[i][l] = sum of F[1..i][1..l] (2D prefix sum)
    vector<vector<long long>> PS(n + 1, vector<long long>(n + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int l = 1; l <= n; l++)
            PS[i][l] = PS[i - 1][l] + PS[i][l - 1] - PS[i - 1][l - 1] + F[i][l];

    // === Answer M queries: each asks for sum of F in submatrix [L..R][P..Q] ===
    while (m--) {
        int L, R, P, Q;
        cin >> L >> R >> P >> Q;
        Q = min(Q, n);
        long long ans = PS[R][Q] - PS[L - 1][Q] - PS[R][P - 1] + PS[L - 1][P - 1];
        cout << ans << '\n';
    }

    // === Optional: Pattern matching using suffix array ===
    int k;
    cin >> k; // number of pattern queries
    SuffixArray SA(s); // Full suffix array for pattern matching and kth-substring

    // Function to compare a suffix with a pattern lexicographically
    auto cmp = [&](int i, const string &p) -> bool {
        for (int j = 0; j < p.size(); j++) {
            if (i + j >= s.size()) return true;
            if (s[i + j] != p[j]) return s[i + j] < p[j];
        }
        return false;
    };

    while (k--) {
        string pattern;
        cin >> pattern;
        auto low = lower_bound(SA.sa.begin(), SA.sa.end(), pattern, cmp);
        string pattern2 = pattern + '{'; // '{' > 'z'
        auto high = lower_bound(SA.sa.begin(), SA.sa.end(), pattern2, cmp);
        cout << (high - low) << '\n'; // pattern occurrence count
    }

    // === Optional: Find the k-th lexicographically smallest distinct substring ===
    int kth;
    cin >> kth;

    for (int i = 0; i < SA.n; i++) {
        int total = (SA.n - SA.sa[i]) - SA.lcp[i];
        if (kth > total) {
            kth -= total;
        } else {
            int len = SA.lcp[i] + kth;
            cout << s.substr(SA.sa[i], len) << '\n';
            break;
        }
    }

    return 0;
}
