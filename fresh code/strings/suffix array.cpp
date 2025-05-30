#include <bits/stdc++.h>
using namespace std;
// SuffixArray class built with the doubling method and Kasai's algorithm.
class SuffixArray {
public:
    vector<int> sfxarray; // stores starting indices of suffixes in sorted order
    vector<int> lcpArray; // lcpArray[i] = LCP of sfxarray[i] and sfxarray[i+1], for i in [0, n-2]; last is 0.
    string s;
    int n;
    
    SuffixArray() {}
    SuffixArray(const string &s) {
        this->s = s;
        n = s.size();
        buildSA();
        buildLCP();
    }
    // Build suffix array using doubling method (O(n log n)).
    void buildSA() {
        sfxarray.resize(n);
        vector<int> rank(n), tmp(n);
        // initial ranking by character
        for (int i = 0; i < n; i++) {
            sfxarray[i] = i;
            rank[i] = s[i];
        }
        
        for (int k = 1; k < n; k *= 2) {
            auto cmp = [&](int i, int j) -> bool {
                if (rank[i] != rank[j])
                    return rank[i] < rank[j];
                int ri = (i + k < n) ? rank[i+k] : -1;
                int rj = (j + k < n) ? rank[j+k] : -1;
                return ri < rj;
            };
            sort(sfxarray.begin(), sfxarray.end(), cmp);
            tmp[sfxarray[0]] = 0;
            for (int i = 1; i < n; i++) {
                tmp[sfxarray[i]] = tmp[sfxarray[i-1]] + (cmp(sfxarray[i-1], sfxarray[i]) ? 1 : 0);
            }
            rank = tmp;
        }
    }
    // Build LCP array using Kasai's algorithm (O(n)).
    void buildLCP() {
        lcpArray.resize(n);
        vector<int> inv(n);
        for (int i = 0; i < n; i++) {
            inv[sfxarray[i]] = i;
        }
        int k = 0;
        lcpArray[n-1] = 0; // last LCP is conventionally 0
        for (int i = 0; i < n; i++) {
            if (inv[i] == n-1) {
                k = 0;
                continue;
            }
            int j = sfxarray[inv[i] + 1];
            while (i + k < n && j + k < n && s[i+k] == s[j+k])
                k++;
            lcpArray[inv[i]] = k;
            if (k)
                k--;
        }
    }
};
 
// For a given string T (which is one of the suffixes Xi), compute an array "dist"
// such that for each length l from 1 to n, dist[l] equals the number of distinct substrings of T of length l
vector<int> computeDistribution(const string &T) {
    int L = T.size();
    // Build suffix array for T.
    SuffixArray sa(T);
    // We'll use 0-indexing on sa.sfxarray and sa.lcpArray.
    // For each sorted suffix (say, at index j in the suffix array), the new distinct substrings it contributes are:
    // lengths in the interval [prevLCP + 1, (L - pos)]
    // where pos = sa.sfxarray[j] and prevLCP = (j==0?0 : sa.lcpArray[j-1]).
    vector<int> diff(L+2, 0); // difference array, 1-indexed positions.
    for (int j = 0; j < L; j++) {
        int pos = sa.sfxarray[j];
        int prevLCP = (j == 0 ? 0 : sa.lcpArray[j-1]);
        int low = prevLCP + 1;
        int high = L - pos; // maximum possible substring length from this suffix.
        if (low <= high) {
            diff[low] += 1;
            if (high + 1 <= L)
                diff[high+1] -= 1;
        }
    }
    vector<int> dist(L+1, 0);
    // Build prefix sum to get actual counts.
    for (int l = 1; l <= L; l++) {
        dist[l] = dist[l-1] + diff[l];
    }
    // For lengths beyond L, set to 0. (We return an array of size (original_n+1) later.)
    return dist; // dist[l] for l = 1 ... L.
}
 
// Main solution.
// We precompute a 2D array F where F[i][l] = f(X_i, l): the number of distinct substrings of Xi (i = 1..n)
// of length exactly l. For l greater than |Xi|, F[i][l] = 0.
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    /// ## number of distinct substrings of length i
    /*auto get = computeDistribution(s);
    for(int i = 1; i <= s.size(); i++) {
        cout << get[i] << " ";
    }*/
    // We'll use 1-indexing for suffixes: i = 1 ... n, where X_i = s[i-1...n-1].
    // Create a 2D array F[1..n][1..n] (we use vector of vectors, dimensions (n+1) x (n+1)).
    vector<vector<int>> F(n+1, vector<int>(n+1, 0));
    // For each suffix X_i, compute the distribution of distinct substrings by length.
    for (int i = 1; i <= n; i++){
        string T = s.substr(i-1);
        int L = T.size(); // = n - i + 1.
        vector<int> dist = computeDistribution(T); // dist[1..L] valid.
        // Fill row i for lengths 1 to n.
        for (int l = 1; l <= n; l++){
            if(l <= L)
                F[i][l] = dist[l];
            else
                F[i][l] = 0;
        }
    }
    // Build a 2D prefix sum array PS over F.
    // Let PS[i][l] = sum_{u=1}^{i} sum_{v=1}^{l} F[u][v].
    vector<vector<long long>> PS(n+1, vector<long long>(n+1, 0));
    for (int i = 1; i <= n; i++){
        for (int l = 1; l <= n; l++){
            PS[i][l] = PS[i-1][l] + PS[i][l-1] - PS[i-1][l-1] + F[i][l];
        }
    }
    // We can use our 2D prefix sum PS to get rectangle sums.
    // For each query, answer = PS[R][Q] - PS[L-1][Q] - PS[R][P-1] + PS[L-1][P-1].
    // (Recall that F[i][l] is 0 for l > n-i+1.)
    for (int qi = 0; qi < m; qi++){
        int L, R, P, Q;
        cin >> L >> R >> P >> Q;
        // Bound Q by n (our F has columns 1..n). Also note that if a row i has max length = n-i+1,
        // then for l > n-i+1, F[i][l] is already 0.
        Q = min(Q, n);
        long long ans = PS[R][Q] - PS[L-1][Q] - PS[R][P-1] + PS[L-1][P-1];
        cout << ans << "\n";
    }
    
    return 0;
}

auto cmp = [&](int i, const string &p) -> bool {
    int m = p.size();
    int n = s.size();
    for (int j = 0; j < m; j++){
        if(i+j >= n) return true; // suffix ended; it is "smaller"
        if(s[i+j] != p[j])
            return s[i+j] < p[j];
    }
    return false; // equal to pattern (so not less)
};

for (int q = 0; q < k; q++){
    string pattern;
    cin >> pattern;
    // lower bound: first index where suffix >= pattern
    auto lowIt = lower_bound(SA.sfxarray.begin(), SA.sfxarray.end(), pattern, cmp);
    // For upper bound, search for pattern with an extra character that is greater than 'z'
    string pattern2 = pattern;
    pattern2.push_back('{'); // '{' is lexicographically after 'z'
    auto highIt = lower_bound(SA.sfxarray.begin(), SA.sfxarray.end(), pattern2, cmp);
    cout << (highIt - lowIt) << "\n";
}

// kth smallest substring among all distinct substring 
// Number of distinct substrings contributed by the suffix at SA.sfxarray[i]
int totalSubstr = (n - SA.sfxarray[i]) - SA.lcpArray[i];
if(k > totalSubstr) {
    k -= totalSubstr;
} else {
    // The kth substring in this suffix has length = LCP + k.
    int length = SA.lcpArray[i] + k;
    cout << s.substr(SA.sfxarray[i], length) << "\n";
    return 0;
}