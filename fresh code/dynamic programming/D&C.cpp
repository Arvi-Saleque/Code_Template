/*
  Problem: Partition `L` cells into `G` groups to minimize total cost.
  - Each cell has a value C[i]
  - Cost of a group from index l to r = (sum of C[l..r]) * (r - l + 1)
  - Goal: minimize total cost when dividing into exactly G groups

  Optimization:
  - Standard DP is O(G * L²)
  - With Divide and Conquer Optimization, reduced to O(G * L * logL) or better
*/

ll G, L; // G = number of groups, L = total number of cells
ll dp[8001][801]; // dp[i][g] = min cost to divide first i cells into g groups
ll cum[8001];     // cum[i] = prefix sum of C[1..i]
ll C[8001];       // value of each cell (1-indexed)

// Compute cost of placing cells from l to r in one group
inline ll cost(ll l, ll r) {
  return (cum[r] - cum[l - 1]) * (r - l + 1);
}

// Divide and Conquer Optimization:
// Computes dp[st..ed][g] using optimal partition point in [r1, r2]
void fn(ll g, ll st, ll ed, ll r1, ll r2) {
  if (st > ed) return;

  ll mid = (st + ed) / 2;
  ll pos = -1;
  dp[mid][g] = inf;

  // Try placing group end at `mid` and starting from `i`
  for (int i = r1; i <= r2; i++) {
    ll tcost = cost(i, mid) + dp[i - 1][g - 1];
    if (tcost < dp[mid][g]) {
      dp[mid][g] = tcost;
      pos = i; // best split point for current (mid, g)
    }
  }

  // Recursively compute left and right segments
  fn(g, st, mid - 1, r1, pos);     // left side: search in [r1, pos]
  fn(g, mid + 1, ed, pos, r2);     // right side: search in [pos, r2]
}

int main() {
  // Precompute prefix sums
  for (int i = 1; i <= L; i++)
    cum[i] = cum[i - 1] + C[i];

  // Base case: one group for first i elements
  for (int i = 1; i <= L; i++)
    dp[i][1] = cost(1, i);

  // Compute dp for groups 2 to G
  for (int i = 2; i <= G; i++)
    fn(i, 1, L, 1, L); // DP group `i` over range [1, L]
}
