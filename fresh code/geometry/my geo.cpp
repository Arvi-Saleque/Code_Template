inline int cmp(double a, double b) {
    if (a < b - eps) return -1;
    if (a > b + eps) return 1;
    return 0;
}
struct PT {
    double x, y;
    PT(){}
    PT(double _x, double _y) {
        x = _x;
        y = _y;
    }
    PT operator - (const PT &o) const { return PT(x - o.x, y - o.y); }
    PT operator + (const PT &o) const { return PT(x + o.x, y + o.y); }
    bool operator == (const PT &o) const { return (cmp(x, o.x) == 0 && cmp(y, o.y) == 0); }
    bool operator < (const PT &o) const { return (cmp(x, o.x) == -1 || (cmp(x, o.x) == 0 && cmp(y, o.y) == -1)); }
};
istream &operator >> (istream &in, PT &p) { return in >> p.x >> p.y; }
ostream &operator << (ostream &out, const PT &p) { return out << "(" << p.x << "," << p.y << ")"; }
inline ld dot(PT a, PT b) { return a.x * b.x + a.y * b.y; }
inline ld cross(PT a, PT b) { return a.x * b.y - b.x * a.y; }
inline ld cross2(PT a, PT b, PT c) { return cross(b - a, c - a); }
int orientation(PT a, PT b, PT c) {
    double o = cross2(a, b, c);
    if(o > eps) return 1; // c on the left side of AB // anticlockwise
    else if(o < -eps) return -1; // c on the right side of AB // clockwise
    return 0;
}

vector<PT> convex_hull(vector<PT> v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int n = v.size();
    if(n <= 2) return v;
    vector<PT> u, l;
    u.push_back(v[0]);
    u.push_back(v[1]);
    for(int i = 2; i < n; i++) {
        int j = u.size();
        while(j > 1 && orientation(u[j - 2], u[j - 1], v[i]) != 1) {
            u.pop_back();
            j--;
        }
        u.push_back(v[i]);
    }
    l.push_back(v[n - 1]);
    l.push_back(v[n - 2]);
    for(int i = n - 3; i >= 0; i--) {
        int j = l.size();
        while(j > 1 && orientation(l[j - 2], l[j - 1], v[i]) != 1) {
            l.pop_back();
            j--;
        }
        l.push_back(v[i]);
    }

    u.pop_back();
    l.pop_back();
    u.insert(u.end(), l.begin(), l.end());
    return u;
}
