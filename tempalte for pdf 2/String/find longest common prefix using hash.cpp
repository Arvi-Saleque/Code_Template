// return LCP(lowest common prefix) of str[i.........j] and str[x.........y]
int findLCP(hashNode &node, int i, int j, int x, int y) {
    int len = min(j - i + 1, y - x + 1);
    int l = 1, r = len, mid, ans;
    while(l <= r) {
        mid = l + r >> 1;
        if(node.getHash(i, i + mid - 1) == node.getHash(x, x + mid - 1)) {
            ans = mid;
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return ans;
}
void solve() {
    string str;
    cin >> str;
    hashNode node(str);
    cout << findLCP(node, 0, 1, 2, 6);
}    