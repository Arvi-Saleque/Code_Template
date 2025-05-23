#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;

const double PI = acos(-1);

// Function to compute the position of each body recursively
void compute_positions(int idx, int n, const vector<double>& r, const vector<double>& t, double T,
                       double px, double py, double angle, vector<double>& dists) {
    double theta = 2 * PI * T / t[idx];
    double new_angle = angle + theta;

    double x = px + r[idx] * cos(new_angle);
    double y = py + r[idx] * sin(new_angle);

    dists[idx] = sqrt(x * x + y * y);

    if (idx + 1 < n) {
        compute_positions(idx + 1, n, r, t, T, x, y, new_angle, dists);
    }
}

int main() {
    int n;
    double T;
    while (cin >> n >> T) {
        vector<double> r(n), t(n);
        for (int i = 0; i < n; ++i) {
            cin >> r[i] >> t[i];
        }

        vector<double> dists(n);
        compute_positions(0, n, r, t, T, 0.0, 0.0, 0.0, dists);

        cout << fixed << setprecision(4);
        for (int i = 0; i < n; ++i) {
            if (i > 0) cout << " ";
            cout << dists[i];
        }
        cout << endl;
    }
    return 0;
}
