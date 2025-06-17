#include <bits/stdc++.h>
using namespace std;

const int MAXK = 1500;   // maximum number of bits in one ability string
const int MAXN = 1500;   // maximum number of players

/*
 * A reminder of the theory we implement
 * -------------------------------------
 * • We need a non-empty subset of *even* size whose XOR is 0.
 * • Every (linear) dependency among the input vectors lives in the kernel.
 * • We build a row-reduced basis over GF(2) while simultaneously tracking
 *   which original rows combine to form each basis vector.
 * • Whenever a row becomes 0 **without** becoming a new pivot, we have found
 *   a dependency.  Its bitset “comb” tells which players participate.
 * • We keep:
 *     – one even dependency  → success
 *     – up to two odd dependencies → their XOR is even ⇒ success
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /* ---------- read input ---------- */
    int N, K;
    if (!(cin >> N >> K)) return 0;

    /* A[i]  = ability vector (bitset of length K) of player i */
    vector<bitset<MAXK>> A(N);
    for (int i = 0; i < N; ++i) {
        string s; cin >> s;                 // read as K-char string
        for (int j = 0; j < K; ++j)
            if (s[K - 1 - j] == '1')        // store least-significant bit at index 0
                A[i].set(j);
    }

    /* ---------- basis storage ----------
     * basis[col]   = basis vector that has a 1 at column 'col' (pivot col)
     * who[col]     = bitset (length N) showing which original rows XOR to this basis vector
     */
    vector<bitset<MAXK>> basis(K);          // initially all 0 → no pivots yet
    vector<bitset<MAXN>> who(K);

    /* containers for dependencies we discover */
    bitset<MAXN> evenDep, firstOdd;
    bool haveEven = false, haveOdd = false;

    /* ---------- process each player (row) one by one ---------- */
    for (int idx = 0; idx < N && !haveEven; ++idx) {

        bitset<MAXK> v = A[idx];            // current vector we try to insert
        bitset<MAXN> comb; comb.set(idx);   // comb = {idx}  (the set currently represented)
        bool addedPivot = false;            // did this row become a new basis vector?

        /* Gaussian elimination over GF(2), from high bit downwards */
        for (int col = K - 1; col >= 0; --col) {
            if (!v[col]) continue;          // bit 0 → nothing to eliminate on this column

            if (!basis[col].any()) {        // this column has no pivot yet → insert as pivot
                basis[col] = v;             // store the row as a basis vector
                who[col]   = comb;          // store which original rows form it
                addedPivot = true;          // remember that we inserted a pivot
                break;                      // basis insertion finished
            }

            /* otherwise: eliminate using existing pivot */
            v   ^= basis[col];
            comb ^= who[col];
        }

        /* ---------- if row reduced to zero *without* adding pivot → dependency found */
        if (!addedPivot && v.none()) {

            size_t cnt = comb.count();      // number of players in this dependency

            if (cnt == 0) continue;         // should not happen, but stay safe

            if ((cnt & 1) == 0) {           // EVEN dependency → we are done
                evenDep  = comb;
                haveEven = true;
            } else {                        // ODD dependency → maybe we can pair it
                if (!haveOdd) {             // store the first odd one
                    firstOdd = comb;
                    haveOdd  = true;
                } else {                    // already had one odd → XOR them
                    evenDep  = firstOdd ^ comb;
                    if (evenDep.any() && (evenDep.count() & 1) == 0)
                        haveEven = true;    // new dependency is even → success
                }
            }
        }
    }

    /* ---------- output ---------- */
    if (!haveEven) {                        // no valid subset exists
        cout << "*\n";
        return 0;
    }

    /* Split the even-sized dependency into two equal halves */
    string out(N, '0');
    vector<int> idxs;                       // list indices in the subset
    for (int i = 0; i < N; ++i)
        if (evenDep[i]) idxs.push_back(i);

    int half = static_cast<int>(idxs.size()) / 2;
    for (int i = 0; i < half; ++i)               out[idxs[i]] = '1';  // first team
    for (int i = half; i < static_cast<int>(idxs.size()); ++i)
                                                  out[idxs[i]] = '2'; // second team

    cout << out << '\n';
    return 0;
}
