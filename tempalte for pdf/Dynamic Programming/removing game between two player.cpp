#include <bits/stdc++.h>
using namespace std; 
typedef long long int ll;
const int N = 3005;
// function prototype
ll second_person_optimal_score(int, int);

int a[N];
ll dp1[N][N];
bool vis1[N][N];
ll dp2[N][N];
bool vis2[N][N];
// if the first person plays the game optimally on segment a[l...r]
// what will be the final score of the game (X - Y)
ll first_person_optimal_score(int l, int r) {
  if (l > r) return 0;
  if (vis1[l][r]) return dp1[l][r];

  // first person takes a[l]
  ll score_left = a[l] + second_person_optimal_score(l + 1, r);

  // first person takes a[r]
  ll score_right = a[r] + second_person_optimal_score(l, r - 1);

  vis1[l][r] = true;
  // first person wants to maximize the final game score
  return dp1[l][r] = max(score_left, score_right);
}

// if the second person plays the game optimally on segment a[l...r]
// what will be the final score of the game (X - Y)
ll second_person_optimal_score(int l, int r) {
  if (l > r) return 0;
  if (vis2[l][r]) return dp2[l][r];
  // second person takes a[l]
  ll score_left = -a[l] + first_person_optimal_score(l + 1, r);

  // second person takes a[r]
  ll score_right = -a[r] + first_person_optimal_score(l, r - 1);

  vis2[l][r] = true;
  // second person wants to minimize the final game score
  return dp2[l][r] = min(score_left, score_right);
}
void solve() {
    int n;
    cin >> n;
    for(int i=1;i<=n;i++) {
        cin >> a[i];
    }
    cout << first_person_optimal_score(1, n) << "\n";
} 