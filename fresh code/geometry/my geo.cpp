struct pt {
    double x, y;
    pt(){}
    pt(double _x, double _y){
        x = _x;
        y = _y;
    }
    void init(double _x, double _y) {
        x = _x; y = _y;
    }
    pt operator + (const pt &o) const {return pt(x + o.x, y + o.y);}
    pt operator - (const pt &o) const {return pt(x - o.x, y - o.y);}
    ld operator | (const pt &o) const {return x * o.x + y * o.y; }
    ld operator * (const pt &o) const {return x * o.y - y * o.x; }
    ld dis() { return hypotl(x, y); }
};
ld pt_to_seg_dis(pt p, pt a, pt b) {
    if(((p - a) | (b - a)) < 0) {
        return (p - a).dis();
    }
    else {
        if(((p - b) | (a - b)) < 0) {
            return (p - b).dis();
        }
        else {
            return fabs(((p - b) * (b - a)) / (b - a).dis());
        }
    }
}
ld dis_bet_seg(pt a, pt b, pt c, pt d) {
    ld dot1 = ((b - a) * (d - a)) * ((b - a) * (c - a));
    ld dot2 = ((d - c) * (a - c)) * ((d - c) * (b - c));
    if(dot1 <= 0 && dot2 <= 0) {
        cout << 0 << "\n";
        return;
    }
    ld ans = min(pt_to_seg_dis(c, a, b), pt_to_seg_dis(d, a, b));
    ans = min(ans, pt_to_seg_dis(a, c, d));
    ans = min(ans, pt_to_seg_dis(b, c, d));
    return ans;
}
