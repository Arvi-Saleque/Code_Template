// if i need to clauclate connected componenet on reverse graph 
// means the edge are connected which are not present in the input
// so just simple as normal connected component
// use DSU for faster calculation

// when someething realtead to construrct with character
// at first try if it possible with 1 char then  2 char
// if possible but need to merge then check some how you can merge
// here you can use 1 extra char to merge both side

// focus on small constraint and check if it possible with only 
// 2/3 value and try to merge others 

// as subsequecen order does not matter so i can sort then
// fix J and try to find all i < j and how much contribute a[j]
// as max and min

// if I need to make any inc/dec sequence and 1-n all are present 
// then i can check only if 1 and n both present

// if i need to work with even and odd indicices something like that
// we need evensum and odd sum
// we can reduce 1 state using prefix sum

// if we need to work with modular arithmatic 
// like ai + aj (=) aipw2 + ajpw2 mod p
// then try to generanize and make all i/j in one side
// do some algebra and try to find solution

(ai + aj)(aipw2 + ajpw2) equiv to k (mod p)
aipw4 - ajpw4 = (ai - aj)(ai + aj)(aipw2 + ajpw2)
(aipw4 - ajpw4) / (ai - aj) equiv to k (mod p)
aipw4 - ajpw4 equiv to k(ai - aj) (mod p)
aipw4 - k * ai equiv to ajpw4 - k * aj (mod p)
f(x) = xpw4 - kx (mod p)
f(ai) equiv to f(aj) (mod p)

// exchagne argument
vector<string> vpp(n);
sort(vpp.begin(), vpp.end(), [&](auto a, auto b) -> bool {
    return (a + b < b + a);
});

// floor(a / b) % M = ((a - (a % b)) / b) % M
// if apwn too check if it is someting equal as apwn % mpw2 % M  

// sum of from l to r
ll f(ll l, ll r) {
    ll val = (l + r) * (r - l + 1) / 2;
    return val;
}

gcd(a, b) = gcd(a, b - a)
so gcd(a1 + bj, a2 + bj) = gcd(a1 + bj, a2 - a1)

// we can reprensent any double number = val / 10^k
// so for 10^k % q = 0 must be when every prime of q is in 10
// for b base
// so for b^k % q = 0 must be when every prime of q is in b
// for gcd dont use gcd use gcd()
// also if you need to know cehck if 
// every prime of q also occur in b
// then just do
/*
while(gcd(q, b) != 1) {
    ll g = gcd(q, b);
    q /= g;
}
and check if q == 1
*/

// if i need to count somethinig kth value then first 
// check if somehow it is possible to bs on the ans
// such as how many values <= x and then check x == k

// to calcualte longest non-increasing subsequence
// just make v[i] = -v[i]
// and find longest increasing subsequence

// sometimes we can observe and reduct the value to very lower
// here k can be max 120 
// also there can be max 30*120 difference type of f(y-1,k) call occur
// so map dp dp[{x, k}]  wonts exceed too much 

// to calcualte median of median we can conver this problem
// to find kth smallest number among all subarray
// so we can do binary search 
// we just make +1/-1 array 
// if v[i] <= x a[i] = 1 else -1
// then using prefix sum we can count easily
// how many values there are <= x

// if i need to equal an array a with mex values 
// then i never put any ai before ai
// so mark the safe values and put them 

// if we need to wokr with two group and need to count
// min-max or max-min then check if binary search possible
// then based on serach devide them into two group 
// then check bipartite graph exist or not

// when works using Xor on tree alz care about subtree
// because subtree[v] can be overcount

if you need to caulaute a^b^c % mod
then must use b % phi(mod)
c % phi(phi(mod)) 
for any prime mod m = a^b % mod = a^(b%(mod-1)) % mod

// two consecutive value XOR = 1 maens even
//  "          " value OR  = odd

// parallogram.cpp
map<pair<int, int>, int> cnt;
for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {
        int midX = vpp[i].first + vpp[j].first;
        int midY = vpp[i].second + vpp[j].second;
        cnt[makepair(midX, midY)]++;
    }
}

// if number of inversion of a permutation is ODD 
// then with one swap it become even then again odd
// also from an identity permutation if using X swap we got a permtaion
// and also if using Y swap we got same permtaion
// then X % 2 == Y % 2 must HOLD

// if i need to make x <= LCM 
// we can fix x say x = k and check if we can make k = LCM
// then solve for all 1 to x
// also let LCM = p -> LCM = p^n -> LCM = P * Q -> LCM = p^a * Q^b

// if i have 1 2 3 4 5 6 and i can pick at least k(3) element
// then i can make all valus from  1 + 2 + 3 = 6 to 4 + 5 + 6 = 15

// reverse DP
// sometimes it needs to do reverse DP to avoid overcounting
// if we need to dp on divisors then i need to sort in reverse order the divisor

when we need to find hoy mane array of a something like 
min(a1, a2, a3.........ak) = t
it is hard so we can just find how many there are >= t
then just solve(t) - solve(t - 1)

// ((n-1)mod9)+1 equal to summing all digits till one digit is left?

// always use visited array for sortesth path problem 
// always check if any node can be reached from negative cycles
// always intilize arrays no matter its int or bool