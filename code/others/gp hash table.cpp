#include<bits/stdc++.h>

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

struct chash {
    int operator()(pair<int,int> x) const { return x.first* 31 + x.second; }
};

gp_hash_table<pair<int, int>, int, chash> mp;
// use as map