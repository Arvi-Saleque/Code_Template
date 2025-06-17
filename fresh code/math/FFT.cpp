#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1);

/*
map<int, int> freq;
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
        freq[apples[i] + bananas[j]]++;
    }
}
for (int w = 2; w <= 2*k; ++w) {
    cout << freq[w] << " ";
}
*/

// ===============================
// Custom Complex Number Structure
// ===============================
// Used for FFT with basic operations defined
struct cd {
    double x, y;
    cd(double x = 0, double y = 0): x(x), y(y) {}

    // Complex addition
    cd operator+(cd o) const { return cd(x + o.x, y + o.y); }

    // Complex subtraction
    cd operator-(cd o) const { return cd(x - o.x, y - o.y); }

    // Complex multiplication
    cd operator*(cd o) const { return cd(x*o.x - y*o.y, x*o.y + y*o.x); }

    // Scalar multiplication
    cd operator*(double d) const { return cd(x * d, y * d); }

    // Conjugate
    cd conj() const { return cd(x, -y); }
};

// =====================
// Fast Fourier Transform
// =====================
// Performs in-place FFT (invert=false) or inverse FFT (invert=true)
void fft(vector<cd> &a, bool invert) {
    int n = a.size();

    // Bit-reversal permutation
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }

    // Main FFT loop: process blocks of increasing size
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1); // angle for root of unity
        cd wlen(cos(ang), sin(ang)); // complex root of unity
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; ++j) {
                cd u = a[i + j];
                cd v = a[i + j + len/2] * w;
                a[i + j] = u + v;
                a[i + j + len/2] = u - v;
                w = w * wlen;
            }
        }
    }

    // Normalize if inverse FFT
    if (invert) {
        for (cd &x : a)
            x = x * (1.0 / n);
    }
}

// ============================================
// Multiply two integer arrays using FFT
// ============================================
// Takes two frequency arrays and returns convolution result
vector<long long> multiply(const vector<int> &a, const vector<int> &b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    // Resize to next power of 2 for convolution
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    // Perform FFT on both input arrays
    fft(fa, false);
    fft(fb, false);

    // Point-wise multiplication of FFT results
    for (int i = 0; i < n; ++i)
        fa[i] = fa[i] * fb[i];

    // Inverse FFT to get the result
    fft(fa, true);

    // Round the real parts to nearest integers
    vector<long long> result(n);
    for (int i = 0; i < n; ++i)
        result[i] = round(fa[i].x);
    return result;
}

// ===========================================
// Main function: Solves "Apples and Bananas"
// ===========================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n, m;
    cin >> k >> n >> m;

    // Frequency array for apples and bananas (weights 1 to k)
    vector<int> apples(k + 1, 0), bananas(k + 1, 0);

    // Read apple weights and count frequency
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        apples[x]++;
    }

    // Read banana weights and count frequency
    for (int i = 0, x; i < m; ++i) {
        cin >> x;
        bananas[x]++;
    }

    // Multiply the frequency arrays using FFT to count pairs
    vector<long long> res = multiply(apples, bananas);

    // Output results for weights from 2 to 2k
    for (int w = 2; w <= 2 * k; ++w)
        cout << res[w] << ' ';
    cout << '\n';
}
