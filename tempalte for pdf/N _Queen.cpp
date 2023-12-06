#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MAX = 12;
int grid[MAX][MAX];
int n; 
bool valid(int R,int C)
{
    for(int i=1;i<=n;i++)
    {
        if(grid[i][C]==1) return false;
    }
    int i = R, j = C;
    while(i<=n && j<=n)
    {
        if(grid[i][j] == 1) return false;
        i++; j++;
    }
    i=R, j=C;
    while(i>=1 && j>=1)
    {
        if(grid[i][j] == 1) return false;
        i--; j--;
    }
    i=R, j=C;
    while(i>=1 && j<=n)
    {
        if(grid[i][j] == 1) return false;
        i--; j++;
    }
    i=R, j=C;
    while(i<=n && j>=1)
    {
        if(grid[i][j] == 1) return false;
        i++; j--;
    }
    return true;
}
void N_queen(int R,int cnt,int &val)
{
    if(cnt == 0)
    {
        cout << val++ << endl;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                printf(" %d", grid[i][j]);
            }
            puts("");
        }
    }
    for(int C = 1; C <= n; C++)
    {
        if(valid(R,C))
        {
            grid[R][C] = 1;
            N_queen(R+1, cnt-1, val);
            grid[R][C] = 0;
        }
    }
}
int main()
{
    scanf("%d",&n);
    int val = 0;
    N_queen(1,n,val);
    cout << val << "\n";
    return 0;
}