// problem link: https://cses.fi/problemset/task/1193

#include <bits/stdc++.h>
using namespace std;
 
typedef long long int ll;
const int MAX = 1000;
char arr[MAX+10][MAX+10];
int level[MAX+10][MAX+10];
int movex[] = {1,-1,0,0};
int movey[] = {0,0,1,-1};
int n,m;
map<pair<int,int>,pair<int,int>> mp;
bool valid(int x,int y)
{
 
   if(x>=1 && x <= n && y >= 1 && y <= m)
   {
      if(arr[x][y] == '#') return false;
      else return true;
   }
   return false;
}
 
void bfs(pair<int,int> src, pair<int,int> end)
{
   level[src.first][src.second] = 0;
   queue<pair<int,int>> Q;
   Q.push(src);
   while(!Q.empty())
   {
      pair<int,int> par = Q.front();
      Q.pop();
      for(int i=0;i<4;i++)
      {
         int x = par.first + movex[i];
         int y = par.second + movey[i];
         if(level[x][y]==-1 && valid(x,y))
         {
            Q.push({x,y});
            level[x][y] = 1 + level[par.first][par.second];
            mp[{x,y}] = par;
         }
      }
   }
}

char findLetter(pair<int,int> &p1, pair<int,int> &p2)
{
   if(p1.second == p2.second && p2.first-p1.first==1) return 'D';
   if(p1.second == p2.second && p1.first-p2.first==1) return 'U';
   if(p1.first == p2.first && p2.second-p1.second==1) return 'R';
   if(p1.first == p2.first && p1.second-p2.second==1) return 'L';
}

void findThePath(pair<int,int> &src, pair<int,int> &end, vector<char> &ans)
{
   pair<int,int> pos = mp[end];
   ans.push_back(findLetter(end,pos));
   //cout << pos.first << " " << pos.second << endl;
   while(pos != src)
   {
      pair<int,int> cur = mp[pos];
      ans.push_back(findLetter(pos,cur));
      pos = mp[pos];
      //cout << pos.first << " " << pos.second << endl;
   }
}

int main()
 
{
   scanf("%d %d",&n,&m);
   pair<int,int> src, end;
   for(int i=1;i<=n;i++)
   {
      for(int j=1;j<=m;j++)
      {
         scanf(" %c",&arr[i][j]);
         if(arr[i][j] == 'A')
         {
            src = {i,j};
         }
         if(arr[i][j] == 'B')
         {
            end = {i,j};
         }
      }
   }
   
   swap(src,end);

   memset(level,-1,sizeof level);
   bfs(src,end);

   if(level[end.first][end.second] == -1)
   {
      puts("NO");
   }
   else
   {
      //printf("%d\n", level[end.first][end.second]);
      vector<char> ans;
      findThePath(src,end,ans);
      printf("YES\n%d\n",ans.size());
      for(auto x : ans)
      {
         printf("%c",x);
      }
      puts("");
   }
   return 0;
}