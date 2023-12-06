/*
! k x : change the salary of employee k to x
? a b : count the number of employees whose salary is between a ... b
*/

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T> using o_set = tree<T, null_type, less<T>, 
rb_tree_tag,  tree_order_statistics_node_update>;

void solve() {
    int n, q;
    cin >> n >> q;
    map<int, int> mp;
    o_set<pair<int, int>> st;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        mp[i] = x;
        st.insert({x, i});
    }
    int id = n + 1;
    while(q--) {
        char ty; cin >> ty;
        if(ty == '?') {
            int a, b; cin >> a >> b;
            cout << st.order_of_key({b + 1, 0}) - st.order_of_key({a, 0}) << "\n";
        }
        else {
            int k, x; cin >> k >> x;
            auto it = st.lower_bound(make_pair(mp[k], 0));
            st.erase(it);
            st.insert({x, id++});
            mp[k] = x;
        }
    }
}  