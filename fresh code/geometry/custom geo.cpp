#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e7 + 9, mod = 1e9 + 7; 
const ld inf = 1e100;
const ld eps = 1e-9;
const ld PI = acos((ld)-1.0);
int sign(ld x) { return (x > eps) - (x < -eps); }
struct PT {
    ll x, y;
    PT() { x = 0, y = 0; }
    PT(ll x, ll y) : x(x), y(y) {}
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    PT operator * (const ll a) const { return PT(x * a, y * a); }
    friend PT operator * (const ll &a, const PT &b) { return PT(a * b.x, a * b.y); }
    PT operator / (const ll a) const { return PT(x / a, y / a); }
    bool operator == (PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
    bool operator != (PT a) const { return !(*this == a); }
    bool operator < (PT a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator > (PT a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
};
istream &operator >> (istream &in, PT &p) { return in >> p.x >> p.y; }
ostream &operator << (ostream &out, PT &p) { return out << "(" << p.x << "," << p.y << ")"; }
inline ll dot(PT a, PT b) { return a.x * b.x + a.y * b.y; }
inline ll dist2(PT a, PT b) { return dot(a - b, a - b); }
inline double dist(PT a, PT b) { return sqrt(dot(a - b, a - b)); }
inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
inline double cross2(PT a, PT b, PT c) { return cross(b - a, c - a); }
inline int orientation(PT a, PT b, PT c) { return sign(cross(b - a, c - a)); }

// intersection point between segment ab and segment cd assuming unique intersection exists
bool seg_seg_intersection(PT a, PT b, PT c, PT d, PT &ans) {
    ld oa = cross2(c, d, a), ob = cross2(c, d, b);
    ld oc = cross2(a, b, c), od = cross2(a, b, d);
    if (oa * ob < 0 && oc * od < 0){
        ans = (a * ob - b * oa) / (ob - oa);
        return 1;
    }
    else return 0;
}
// returns true if  point p is on line segment ab
bool is_point_on_seg(PT a, PT b, PT p) {
    if (fabs(cross(p - b, a - b)) < eps) {
        if (p.x < min(a.x, b.x) - eps || p.x > max(a.x, b.x) + eps) return false;
        if (p.y < min(a.y, b.y) - eps || p.y > max(a.y, b.y) + eps) return false;
        return true;
    }
    return false;
}
// intersection point between segment ab and segment cd assuming unique intersection exists
set<PT> seg_seg_intersection_inside(PT a,  PT b,  PT c,  PT d) {
    PT ans;
    if (seg_seg_intersection(a, b, c, d, ans)) return {ans};
    set<PT> se;
    if (is_point_on_seg(c, d, a)) se.insert(a);
    if (is_point_on_seg(c, d, b)) se.insert(b);
    if (is_point_on_seg(a, b, c)) se.insert(c);
    if (is_point_on_seg(a, b, d)) se.insert(d);
    return se;
}

ld area(vector<PT> &p) {
    ld ans = 0; int n = p.size();
    for (int i = 0; i < n; i++) ans += cross(p[i], p[(i + 1) % n]);
    return fabs(ans) * 0.5;
}

ll area2(const vector<PT>& p) {
    ll ans = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        ans += cross(p[i], p[(i + 1) % n]);
    }
    return abs(ans); // not devided by 2 for integers
}

bool is_point_on_polygon(vector<PT> &p, const PT& z) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        if (is_point_on_seg(p[i], p[(i + 1) % n], z)) return 1;
    }
    return 0;
}

// returns 1e9 if the point is on the polygon 
int winding_number(vector<PT> &p, const PT& z) { // O(n)
    if (is_point_on_polygon(p, z)) return 1e9;
    int n = p.size(), ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        bool below = p[i].y < z.y;
        if (below != (p[j].y < z.y)) {
            auto orient = orientation(z, p[j], p[i]);
            if (orient == 0) return 0;
            if (below == (orient > 0)) ans += below ? 1 : -1;
        }
    }
    return ans;
}

// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
int is_point_in_polygon(vector<PT> &p, const PT& z) { // O(n)
    int k = winding_number(p, z);
    return k == 1e9 ? 0 : k == 0 ? 1 : -1;
}

// Count boundary lattice points using GCD on each edge
ll boundary_lattice_points(const vector<PT>& p) {
    ll b = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        PT a = p[i], c = p[(i + 1) % n];
        b += __gcd(abs(a.x - c.x), abs(a.y - c.y));
    }
    return b;
}

// Computes (interior, boundary) lattice points using Pick's Theorem
pair<ll, ll> polygon_lattice_points(const vector<PT>& p) {
    // Pick's Theorem:
    // Area = I + B/2 - 1 
    // I = the number of interior lattice points
    // B = the number of boundary lattice points
    ll A2 = area2(p);               // Twice the area
    ll B = boundary_lattice_points(p);
    ll I = (A2 - B + 2) / 2;
    return {I, B};
}

// distance, p1, p2
pair<ll, pair<PT, PT>> closest_pair_recursive(vector<PT>& pts, vector<PT>& tmp, int l, int r) {
    if (r - l <= 3) {
        pair<ll, pair<PT, PT>> res = {LLONG_MAX, {PT(), PT()}};
        for (int i = l; i < r; ++i) {
            for (int j = i + 1; j < r; ++j) {
                ll d = dist2(pts[i], pts[j]);
                if (d < res.first) {
                    res = {d, {pts[i], pts[j]}};
                }
            }
        }
        sort(pts.begin() + l, pts.begin() + r, [](const PT& a, const PT& b) {
            return a.y < b.y;
        });
        return res;
    }

    int m = (l + r) / 2;
    ll midx = pts[m].x;

    auto left = closest_pair_recursive(pts, tmp, l, m);
    auto right = closest_pair_recursive(pts, tmp, m, r);
    auto res = min(left, right);

    merge(pts.begin() + l, pts.begin() + m,
          pts.begin() + m, pts.begin() + r,
          tmp.begin() + l, [](const PT& a, const PT& b) {
              return a.y < b.y;
          });

    copy(tmp.begin() + l, tmp.begin() + r, pts.begin() + l);

    vector<PT> strip;
    for (int i = l; i < r; ++i) {
        if ((pts[i].x - midx) * (pts[i].x - midx) >= res.first) continue;
        for (int j = strip.size() - 1; j >= 0; --j) {
            ll dy = pts[i].y - strip[j].y;
            if (dy * dy >= res.first) break;
            ll d = dist2(pts[i], strip[j]);
            if (d < res.first) {
                res = {d, {pts[i], strip[j]}};
            }
        }
        strip.push_back(pts[i]);
    }

    return res;
}

// distance, point1, point2
pair<ll, pair<PT, PT>> minimum_euclidean_distance(vector<PT>& pts) {
    int n = pts.size();
    sort(pts.begin(), pts.end(), [](const PT& a, const PT& b) {
        return a.x < b.x;
    });
    vector<PT> tmp(n);
    return closest_pair_recursive(pts, tmp, 0, n);
}


vector<PT> ConvexHull(vector<PT>&p, int n) {
    int sz = 0;
    vector<PT> hull(n + n);
    sort(p.begin(), p.end());
  for(int i = 0; i < n; ++i) {
        while (sz > 1 and cross2(hull[sz - 2], hull[sz - 1], p[i]) < 0) --sz;
        hull[sz++] = p[i];
    }
    for(int i = n - 2, j = sz + 1; i >= 0; --i) {
        while (sz >= j and cross2(hull[sz - 2], hull[sz - 1], p[i]) < 0) --sz;
        hull[sz++] = p[i];
    }
    hull.resize(sz - 1);
    return hull;
}   
