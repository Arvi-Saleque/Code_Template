vector<pair<ll,int>> graph[N+10];
vector<ll> dis;
int parent[N+10];
void dijkstra(int u,int n)
{
    dis.clear();
    dis.resize(n+1, inf);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> PQ;
    PQ.push({0,u});
    dis[u] = 0;
    while(!PQ.empty())
    {
        auto [par_dis, par_node] = PQ.top(); PQ.pop();
        if(dis[par_node] < par_dis) continue;
        for(auto &[child_dis, child_node] : graph[par_node])
        {
            if(dis[child_node] > dis[par_node] + child_dis)
            {
                dis[child_node] = dis[par_node] + child_dis;
                PQ.push({dis[child_node], child_node});
            }
        }
    }
}
void pathprint(int n)
{
   if(n==0) return;
   pathprint(parent[n]);
   cout << n << " ";
}
int main()
{
   int n,m;
   scanf("%d %d",&n,&m);
   while(m--)
   {
      int a,b,c;
      scanf("%d %d %d",&a,&b,&c);
      graph[a].push_back({c,b});
      graph[b].push_back({c,a});
   }
   for(int i=1;i<=n;i++)
   {
      sort(graph[i].begin(),graph[i].end(),cmp);
   }
   dijkstra(1, n);
   if(dis[n]==inf) puts("-1");
   else 
   {
      pathprint(n);
      cout << endl;
   }
   return 0;
}