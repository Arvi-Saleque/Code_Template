
struct DSU {
    struct Op {
        char type;      // 'M' = merge, 'V' = add value, 'X' = dummy
        int  a, b;      // merge: childRoot=a, parentRoot=b
        long long savedSum; // sum of component a before merge   OR   sum(root) snapshot for 'V'
        long long delta;    // only for 'V'
    };

    vector<int> par, sz;          // parent and size per vertex
    vector<long long> compSum,    // current sum for every component root
                      val;        // individual vertex value
    vector<Op> stk;               // undo stack
    int comps;                    // current number of components

    DSU() {}
    DSU(int n, const vector<long long>& init){ initDSU(n,init); }

    void initDSU(int n, const vector<long long>& init){
        par.resize(n);  iota(par.begin(), par.end(), 0);
        sz.assign(n, 1);
        val.resize(n);  compSum.resize(n);
        for(int i=0;i<n;++i){
            val[i] = init.empty()? 0LL : init[i];
            compSum[i] = val[i];
        }
        stk.clear();
        comps = n;
    }

    int find(int x) const { return (x==par[x]) ? x : find(par[x]); }

    /* ---- merge two components (with rollback support) ---- */
    void merge(int u,int v){
        u = find(u); v = find(v);
        if(u==v){                      // edge inside the same component
            stk.push_back({'X',0,0,0,0});
            return;
        }
        if(sz[u] > sz[v]) swap(u,v);   // union by size, u becomes child
        stk.push_back({'M',u,v,compSum[u],0});
        par[u]  = v;
        sz[v]  += sz[u];
        compSum[v] += compSum[u];
        --comps;
    }

    /* ---- vertex value increase (persistent) ---- */
    void addValue(int v,long long d){
        int r = find(v);
        stk.push_back({'V',v,r,compSum[r],d});
        val[v]      += d;
        compSum[r]  += d;
    }

    /* ---- rollback last operation ---- */
    void undo(){
        auto op = stk.back(); stk.pop_back();
        if(op.type=='X') return;             // dummy
        if(op.type=='M'){
            int child = op.a, parent = op.b;
            par[child] = child;
            sz[parent] -= sz[child];
            compSum[parent] -= op.savedSum;
            ++comps;
        }else{                               // 'V'
            int vtx = op.a, root = op.b;
            val[vtx]      -= op.delta;
            compSum[root]  = op.savedSum;
        }
    }

    long long sumOfComp(int v){ return compSum[ find(v) ]; }
};
struct Event{                   // stored inside the segment tree
    bool isEdge;                // true = edge, false = value add
    int u,v;                    // edge: (u,v) ; value: (v,delta)
    long long delta;
};
struct SegTree{
    int n;                                  // number of leaves (Q)
    vector<vector<Event>> box;              // events per segment node
    SegTree(int _n=0){ init(_n); }
    void init(int _n){ n=_n; box.assign(4*(n+2),{}); }
    void add(int idx,int l,int r,int ql,int qr,const Event& e){
        if(ql>qr) return;
        if(l==ql && r==qr){ box[idx].push_back(e); return; }
        int m=(l+r)>>1;
        add(idx<<1,l,m,ql,min(qr,m),e);
        add(idx<<1|1,m+1,r,max(ql,m+1),qr,e);
    }
    void addRange(int l,int r,const Event& e){ if(l<=r) add(1,0,n-1,l,r,e); }
};
struct RawQ{ int tp,u,v; long long x; };   // raw query data

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,Q;                      // #vertices, #queries
    if(!(cin>>N>>Q)) return 0;

    vector<long long> init(N);
    for(auto &x:init) cin>>x;

    /* -------- read all queries first (offline) ---------------- */
    vector<RawQ> q(Q);
    for(int i=0;i<Q;++i){
        cin>>q[i].tp;
        if(q[i].tp==0||q[i].tp==1){
            cin>>q[i].u>>q[i].v;
        }else if(q[i].tp==2){
            cin>>q[i].v>>q[i].x;
        }else if(q[i].tp==3){
            cin>>q[i].v;
        } /* NEW-4 : type 4 has no extra input */
    }

    /* -------- build interval structure ------------------------ */
    SegTree seg(Q);
    unordered_map<long long,int> openEdge;          // edge -> start time
    auto key=[&](int a,int b){ if(a>b) swap(a,b); return (1LL*a<<20)|b; };

    for(int t=0;t<Q;++t){
        int tp=q[t].tp;
        if(tp==0){                         // edge insert
            openEdge[key(q[t].u,q[t].v)]=t;
        }else if(tp==1){                   // edge delete
            long long k=key(q[t].u,q[t].v);
            int l=openEdge[k], r=t-1;
            seg.addRange(l,r,{true,q[t].u,q[t].v,0});
            openEdge.erase(k);
        }else if(tp==2){                   // vertex value add
            seg.addRange(t,Q-1,{false,q[t].v,0,q[t].x});
        }
    }
    /* edges never removed -> alive until Q-1 */
    for(auto [k,l]:openEdge){
        int u=k>>20, v=k&((1<<20)-1);
        seg.addRange(l,Q-1,{true,u,v,0});
    }

    /* -------- DFS over the segment tree with rollback DSU ----- */
    DSU dsu(N,init);
    vector<long long> out;   out.reserve(Q);        // printed answers

    function<void(int,int,int)> dfs=[&](int idx,int l,int r){
        /* apply events stored in this segment */
        for(const auto &ev:seg.box[idx]){
            if(ev.isEdge) dsu.merge(ev.u,ev.v);
            else          dsu.addValue(ev.u,ev.delta);
        }

        if(l==r){           // leaf = one specific time moment
            int tp=q[l].tp;
            if(tp==3) out.push_back(dsu.sumOfComp(q[l].v));
            else if(tp==4) out.push_back(dsu.comps);           // NEW-4
        }else{
            int m=(l+r)>>1;
            dfs(idx<<1,l,m);
            dfs(idx<<1|1,m+1,r);
        }

        /* roll back this segment’s modifications */
        for(size_t i=0;i<seg.box[idx].size();++i) dsu.undo();
    };
    if(Q) dfs(1,0,Q-1);

    /* -------- print answers in the exact order they were asked */
    for(long long v:out) cout<<v<<"\n";
    return 0;
}
