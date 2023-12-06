#include <bits/stdc++.h>
using namespace std;
#define FAST  ios_base::sync_with_stdio(0); cin.tie(0);
typedef long long int ll;
const int MAX = 200000;
int main()
{
    FAST;
    int n;
    cin >> n;
    string str;
    //getline(cin, str); // Does not work properly because of \n.....
    getline(cin >> ws, str); // Does work properly because (cin >> ws) ignore all kind of whitespaces.
    // It reads the full paragraph untill he find 'EOF'.
    cout << "HELLO " << str << " IS " << n << "\n";
    return 0;
