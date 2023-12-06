pair<bool, string> check(int len, Hash_node &nodeA, Hash_node &nodeB) {
    set<pair<int,int>> st;
    pair<bool, string> ans{false, ""};
    for(int i = 0; i + len - 1 < nodeA.s.size(); i++) {
        st.insert(nodeA.getHash(i, i + len - 1));
    }
    for(int i = 0; i + len - 1 < nodeB.s.size(); i++) {
        auto val = nodeB.getHash(i, i + len - 1);
        if(st.find(val) != st.end()) {
            ans.first = true;
            ans.second = nodeB.s.substr(i, len);
            break;
        }
    }
    return ans;
}
void solve() {
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    Hash_node node_a(a), node_b(b);
    int l = 1, r = n, mid;
    string ans_str = "";
    while(l <= r) {
        mid = (l + r) >> 1;
        auto [x, y] = check(mid, node_a, node_b);
        if(x) {
            ans_str = y;
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    cout << ans_str << "\n";
}   