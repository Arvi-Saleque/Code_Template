#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long int ll;
const int MAX = 200010;
const long long inf = 1000000000000000;
vector<pair<long long,int>> graph[MAX+10];
long long dis[MAX+10], parent[MAX+10];
bool cmp(pair<int,int> a, pair<int,int> b)
{
   return (a.first<b.first);
}
void dijkstra(int src)
{
   for(int i=1;i<=MAX;i++) dis[i] = inf;
   priority_queue< pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> PQ;
   PQ.push({0,src});
   dis[src] = 0;
   while(!PQ.empty())
   {
      long long par = PQ.top().second, parDis = PQ.top().first;
      PQ.pop();
      for(auto x : graph[par])
      {
         long long child = x.second, childDis = x.first;
         if(dis[child] > parDis + childDis)
         {
            dis[child] = parDis + childDis;
            PQ.push({dis[child],child});
            parent[child] = par;
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
   dijkstra(1);
   if(dis[n]==inf) puts("-1");
   else 
   {
      pathprint(n);
      cout << endl;
   }
   return 0;
}