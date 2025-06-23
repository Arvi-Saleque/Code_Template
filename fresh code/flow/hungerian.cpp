struct Hungerian {
    int n;
    vector<vector<ll>> cost, reduced_cost;
    vector<int> whichj, whichi, responsiblei, parentj;
    bitset<MAXN> vis_row, vis_col;
    vector<ll> fx, fy, slack;
    Hungerian(){}
    Hungerian(int n, vector<vector<ll>> cost) : n(n), cost(cost),
                             whichi(n, -1), whichj(n, -1), fx(n), fy(n, 0),
                             reduced_cost(n, vector<ll>(n)),
                             slack(n), responsiblei(n), parentj(n) {
        build();
    }
    void build() {
        for(int i = 0; i < n; i++) {
            ll mn = 2e18;
            for(int j = 0; j < n; j++) {
                mn = min(cost[i][j], mn);
            }
            fx[i] = mn;
        }
        assign();
    }
    ll getRedueced(int i, int j) {
        return cost[i][j] - fx[i] - fy[j];
    }
    void addX_subY() {
        // try to addX_subY with new zeros using slack concetp
        ll delta = 2e18;
        for(int i = 0; i < n; i++) {
            if(vis_row[i]) {
                for(int j = 0 ; j < n; j++) {
                    if(!vis_col[j]) {
                        delta = min(delta, getRedueced(i, j));
                    }
                }
            }
        }
        for(int i = 0; i < n; i++) {
            if(vis_row[i]) fx[i] += delta;
        }
        for(int i = 0; i < n; i++) {
            if(vis_col[i]) fy[i] -= delta;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                reduced_cost[i][j] = cost[i][j] - fx[i] - fy[j];
            }
        }
    }
    bool find_augment_path() {
        vis_row.reset();
        vis_col.reset();
        int source = -1;
        for(int i = 0; i < n; i++) {
            if(whichj[i] == -1) {
                source = i;
                break;
            }
        }
        if(source == -1) return 1;
        parentj.assign(n, -1);
        queue<int> Q;
        Q.push(source);
        vis_row[source] = 1;

        for (int j = 0; j < n; j++) {
            slack[j] = getRedueced(source, j);
            responsiblei[j] = source;
        }

        while(not Q.empty()) {
            int u = Q.front(); Q.pop();
            for(int j = 0; j < n; j++) {
                if(getRedueced(u, j) == 0 && !vis_col[j]) {
                    vis_col[j] = 1;
                    par_j[j] = u;

                    if(whichi[j] == -1) {
                        int cur_j = j;
                        while(cur_j != -1) {
                            int assigned_i = par_j[cur_j]; // which i assign for this job
                            int next_j = whichj[assigned_i];
                            whichj[assigned_i] = cur_j;
                            whichi[cur_j] = assigned_i;
                            cur_j = next_j;
                        }
                        return 1;
                    }
                    else {
                        int assigned_i = whichi[j];
                        if(!vis_row[assigned_i]) {
                            vis_row[assigned_i] = 1;
                            Q.push(assigned_i);
                            for (int k = 0; k < n; k++) {
                                ll newSlack = getRedueced(assigned_i, k);
                                if (!vis_col[k] && newSlack < slack[k]) {
                                    slack[k] = newSlack;
                                    responsiblei[k] = assigned_i;
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
    void assign() {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(getRedueced(i, j) == 0 && whichi[j] == -1) {
                    whichi[j] = i;
                    whichj[i] = j;
                    break;
                }
            }
            if(whichj[i] == -1) {
                while(!find_augment_path()) {
                    addX_subY();
                }
            }
        }
    }   
    // returns a vector pair of n (i, j) which is taken for cost matrix
    vector<array<int, 2>> max_matching() {
        vector<array<int, 2>> result;
        for (int i = 0; i < n; i++) {
            if (whichj[i] != -1)
                result.push_back({i, whichj[i]});
        }
        return result;
    }
};
