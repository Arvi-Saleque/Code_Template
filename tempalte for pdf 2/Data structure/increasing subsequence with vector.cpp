#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int MAX = 1000;
int main()
{   
    int n;
    scanf("%d",&n);
    vector<int> vec;
    for(int i=1;i<=n;i++)
    {
        int a;
        scanf("%d",&a);
        int pos = lower_bound(vec.begin(), vec.end(),a) - vec.begin();
        if(pos == vec.size()) vec.push_back(a);
        else vec[pos] = a;
    }
    cout << vec.size() << "\n";
    return 0;
}