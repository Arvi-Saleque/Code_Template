/*
Given p and n, find the largest x such that p^x divides n!
*/

/* IF p is may or may not prime */
int findPowerOfP(int n, int p)
{
    int count = 0;
    int r=p;
    while (r <= n) {
        // calculating floor(n/r)
        // and adding to the count
        count += (n / r);
        // increasing the power of p
        // from 1 to 2 to 3 and so on
        r = r * p;
    }
    return count;
}
vector<pair<int, int> > primeFactorsofK(int k)
{
    vector<pair<int, int> > ans;
    for (int i = 2; k != 1; i++) { // check only for primes
        if (k % i == 0) {
            int count = 0;
            while (k % i == 0) {
                k = k / i;
                count++;
            }
            ans.push_back(make_pair(i, count));
        }
    }
    return ans;
}
int largestPowerOfK(int n, int k)
{
    vector<pair<int, int>> vec;
    vec = primeFactorsofK(k);
    int ans = INT_MAX;
    for (int i = 0; i < vec.size(); i++) {
        ans = min(ans, findPowerOfP(n, vec[i].first) / vec[i].second);
    }
    return ans;
}