#include <bits/stdc++.h>
using namespace std;
#define pi 2*acos(0.0)
typedef long long int ll;
const int MAX = 200000;
vector<int> graph[MAX+10]; 
vector<int> level;

int bfs(int src)
{
   level.clear();
   level.resize(MAX+5, -1);
   queue<int> Q;
   Q.push(src);
   level[src] = 0;
   while(!Q.empty())
   {
      int par = Q.front();
      Q.pop();
      for(auto x : graph[par])
      {
         if(level[x] == -1)
         {
            level[x] = 1 + level[par];
            Q.push(x); 
         }
      }
   }
}

int main() 
{
    return 0;
} 