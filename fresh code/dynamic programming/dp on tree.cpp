vector<int> down(n + 1);
vector<int> best1(n + 1, -1), best2(n + 1, -1);
function<int(int, int)> dfs1 = [&](int u, int p) -> int {
    for(auto v : g[u]) if(v != p) {
        int cand = 1 + dfs1(v, u);                          
        if (cand > best1[u]) { best2[u] = best1[u]; best1[u] = cand; }
        else if (cand > best2[u]) best2[u] = cand;
        down[u] = max(down[u], cand); 
    }
    return down[u];
};
dfs1(1, 0);

vector<int> up(n + 1);
function<void(int, int)> dfs2 = [&](int u, int p) -> void {
    for(auto v : g[u]) if(v != p) {
        int val = (down[v] + 1 == best1[u]) ? best2[u] : best1[u];
        up[v] = 1 + max(up[u], val);
        dfs2(v, u);
    } 
    
};
dfs2(1, 0);

// knapsack
vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, neg));
function<void(int, int)> dfs = [&](int u, int p) -> void {
    dp[u][1] = cost[u];

    for(auto v : g[u]) if ( v != p) {
        dfs(v, u);

        vector<ll> ndp(k + 1, neg);
        for(int x = 1; x <= k; x++) {
            if(dp[u][x] == neg) continue;
            for(int y = 0; x + y <= k; y++) {
                if(dp[v][y] == neg) continue;
                ndp[x + y] = max(ndp[x + y], dp[u][x] + dp[v][y]);
            }
        }

        for(int i = 1; i <= k; i++) {
            dp[u][i] = max(ndp[i], dp[u][i]);
        }
    }
}

// divide the tree into two component 
// say red and white 
// let d1 = diameter of red tree
// d2 = diameter of white tree
// ans = min(ans, max(d1, d2)

#include <bits/stdc++.h>
using namespace std;

/* helpers to keep the k best values ------------------------------------ */
inline void keep_top3(int &a,int &b,int &c,int x){
    if(x>a){ c=b; b=a; a=x; }
    else if(x>b){ c=b; b=x; }
    else if(x>c) c=x;
}
inline void keep_top2(int &a,int &b,int x){
    if(x>a){ b=a; a=x; }
    else if(x>b) b=x;
}

/* --------------------------------------------------------------------- */
void solve() {
    int n; cin >> n;
    vector<vector<int>> g(n+1);
    for (int i=1;i<n;i++){
        int u,v; cin>>u>>v;
        g[u].push_back(v); g[v].push_back(u);
    }

    /* bottom-up -------------------------------------------------------- */
    vector<int> down(n+1,0), diamIn(n+1,0);
    vector<int> bestd1(n+1,-1), bestd2(n+1,-1), bestd3(n+1,-1);
    vector<int> bestDia1(n+1,-1), bestDia2(n+1,-1);

    function<void(int,int)> dfs1=[&](int u,int p){
        for(int v:g[u]) if(v!=p){
            dfs1(v,u);
            keep_top3(bestd1[u],bestd2[u],bestd3[u], down[v]);
            keep_top2(bestDia1[u],bestDia2[u], diamIn[v]);
            diamIn[u]=max(diamIn[u], diamIn[v]);
        }
        if(bestd1[u]!=-1){
            down[u]=bestd1[u]+1;
            if(bestd2[u]!=-1) diamIn[u]=max(diamIn[u],bestd1[u]+bestd2[u]+2);
            else              diamIn[u]=max(diamIn[u],down[u]);
        }
    };
    dfs1(1,0);

    /* top-down --------------------------------------------------------- */
    vector<int> up(n+1,-1), diamOut(n+1,-1);
    function<void(int,int)> dfs2=[&](int u,int p){
        for(int v:g[u]) if(v!=p){

            /* 1. longest path that starts in v and goes up -------------- */
            int sibDepth = (down[v]==bestd1[u] ? bestd2[u] : bestd1[u]);
            int viaAncestor = 1 + (up[u]==-1 ? 0 : up[u]);
            int viaSibling  = sibDepth==-1 ? -1 : 2 + sibDepth;
            up[v] = max(viaAncestor, viaSibling);

            /* 2. branches meeting in u but not entering v ----------------*/
            vector<int> branches;
            branches.push_back(up[u]==-1 ? 0 : up[u]);          // ancestor side

            bool skipped=false;
            for(int d:{bestd1[u],bestd2[u],bestd3[u]}){
                if(d==-1) continue;
                if(!skipped && d==down[v]){ skipped=true; continue; }
                branches.push_back(d+1);                        // u → sibling
            }
            sort(branches.begin(),branches.end(),greater<int>());
            int pathThroughU = 0;
            if(branches.size()>=2) pathThroughU = branches[0]+branches[1];
            else if(branches.size()==1) pathThroughU = branches[0];

            /* 3. best diameter among siblings other than v ---------------*/
            int bestSibDia = (diamIn[v]==bestDia1[u]?bestDia2[u]:bestDia1[u]);

            diamOut[v] = max({diamOut[u], bestSibDia, pathThroughU});

            dfs2(v,u);
        }
    };
    dfs2(1,0);

    /* answer over all (parent,child) edges ----------------------------- */
    int ans = INT_MAX;
    for(int v=2; v<=n; ++v)
        ans = min(ans, max(diamIn[v], diamOut[v]));
    cout << ans << '\n';
}

/* --------------------------------------------------------------------- */
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;     // change if multiple cases
    //cin >> T;
    while(T--) solve();
    return 0;
}
