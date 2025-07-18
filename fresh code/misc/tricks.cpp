1. Shortest path safety:
   - Always use visited array
   - Check reachability from negative cycles
   - Always initialize all arrays (int or bool)

2. Connected component on reverse graph:
   - Treat edges not in input as actual edges
   - Compute connected components normally
   - Use DSU for fast calculation

3. Char construction logic:
   - Try with 1 char, then 2
   - If merging is needed, try with one extra char

4. Small constraints:
   - Check if solution is possible with just 2-3 values
   - Merge remaining if needed

5. Subsequence (order does not matter)
   - Sort array
   - Fix j, find i < j
   - a[j] may contribute as min or max

6. 1 to n inc/dec sequence:
   - Check if both 1 and n are present

7. Even/Odd indexed logic:
   - Use evenSum and oddSum
   - Prefix sum can help reduce one state

8. Modular arithmetic trick:
   - Generalize expressions like ai + aj eqvto ai^2 + aj^2 mod p
   - Use algebra to reduce both sides

9. Algebraic transform:
   - (ai + aj)(ai^2 + aj^2) eqvto k mod p
   - Leads to: ai^4 - aj^4 eqvto k(ai - aj) mod p
   - Define f(x) = x^4 - kx
   - Then f(ai) eqvto f(aj) mod p

10. Sorting strings by concatenation:
    - Use comparator: return (a + b < b + a)

11. Floor division modulo:
    - floor(a / b) % M = ((a - a % b) / b) % M

12. Sum from l to r:
    - Use formula: (l + r)(r - l + 1) / 2

13. GCD trick:
    - gcd(a, b) = gcd(a, b - a)
    - Example: gcd(a1 + bj, a2 + bj) = gcd(a1 + bj, a2 - a1)

14. Representing doubles:
    - val / 10^k
    - To check divisibility by q, all primes of q must divide base
    - Reduce q by repeatedly dividing gcd(q, base), check if q == 1

15. Kth value problems:
    - Binary search on answer
    - Count how many values <= x, then compare to k

16. Longest non-increasing subsequence:
    - Negate array: v[i] = -v[i]
    - Find LIS

17. DP optimization:
    - For small k (<=120), use map dp[{x, k}]

18. Median of medians:
    - Reduce to kth smallest subarray
    - Make +1/-1 array: a[i] = (v[i] <= x ? 1 : -1)
    - Use prefix sums to count

19. Make array equal to MEX:
    - Never place ai before ai
    - Mark and safely place values

20. Two-group min/max:
    - Binary search on answer
    - Divide and check bipartite graph

21. XOR on trees:
    - Always track subtree[v] to avoid overcount

22. a^b^c % mod:
    - Use exponent reduction: phi(mod), phi(phi(mod))

23. XOR/OR parity trick:
    - XOR of 2 values = 1 means even
    - OR of 2 values = 1 means odd

24. Parallelogram midpoint idea:
    - Count midpoints of each (x1 + x2, y1 + y2)

25. Inversion parity in permutation:
    - If inversion count is odd, 1 swap changes parity
    - If X swaps and Y swaps lead to same permutation: X % 2 == Y % 2

26. Making x <= LCM:
    - Try all x
    - LCM = p^a * Q^b

27. Sum from k elements among [1e6]:
    - Min sum = 1 + 2 + 3 = 6
    - Max sum = 4 + 5 + 6 = 15

28. Reverse DP:
    - Used to avoid overcount
    - Sort divisors in reverse

29. Count arrays where min == t:
    - Count arrays where all >= t: solve(t)
    - Result = solve(t) - solve(t - 1)

30. Digital root:
    - ((n - 1) % 9) + 1

31. x = y by multiply/divide:
    - Use gcd: g = gcd(x, y)
    - Compute: get(x / g), get(y / g)

32. Bitwise AND == k subset count:
    - cnt[k] = freq, sup[k] = 2^cnt[k] - 1
    - exact = sup
    - for (i) for (mask): if (!(m & (1 << i))) exact[m] -= exact[m | (1 << i)]

33. Segment tree + mod with lazy:
    - Normal lazy doesn’t work
    - Do point update where max >= mod

34. Count overlapping intervals:
    - bitL.upd(l, 1), bitR.upd(r, 1)
    - Remove: bitL.upd(l, -1), bitR.upd(r, -1)
    - Result = bitL.query(r) - bitR.query(l - 1)

35. Same path check for k nodes:
    - Find LCA tree diameter endpoints u, v
    - For each x, check: dist(u, v) == dist(u, x) + dist(v, x)

36. Shortest cycle in graph:
    - Remove edge (u, v)
    - Compute shortest distance from u to v
    
37. Interval DP trick:
    - for interval [l, r]
    - for (int k = l; k < r; k++)
        ans = min(ans, dpf(l, k) + dpf(k + 1, r));

38. Counting distinct subsequences:
    - Go from a to next a, b, ..., z (track transitions)
    - Key idea: can not just use take/not-take like standard subseq
    - Alternate approach:
    - dp[i] = number of distinct subsequences using first i characters
    - Use last[ch] to store the last occurrence index of each character

39. Block size optimization:
    - Block size is not always sqrt(n)
    - If complexity is O(n/b + b), minimize by solving n/b = b → b = sqrt(n)

40. MO's Algorithm:
    - Can solve without remove operation
    - For L in same block, let R keep increasing
    - For each range, start L from the end of the block

41. Sqrt Decomposition by query time:
    - Keep overall solution and sqrt(n) updates in a vector
    - For each query, iterate over the updates (<= sqrt(n) cost)
    - When size exceeds sqrt(n), apply updates to global structure in O(n)

42. Distinct values from sum:
    - If sum of N positive numbers is S, there are at most sqrt(S) distinct values

43. Randomization:
    - Use when deterministic structure is hard or fails
    - Try random order/seed to avoid worst-case paths or collisions

44. Baby Step Giant Step:
    - Used for discrete log: a^x = b mod p
    - Time: O(sqrt(p)), Space: O(sqrt(p))
    - Precompute a^j (baby steps), match with b * a^(-irootp) (giant steps)

45. Hockey Stick Identity:
    - sum_{j=r to n} C(j, r) = C(n + 1, r + 1)

46. Weighted Hockey Stick Identity:
    - sum_{j=r to n} j * C(j, r) = r * C(n + 1, r + 1)

47. Binomial Identity (splitting j * C(j, k - 1)):
    - j * C(j, k - 1) = (k - 1) * C(j, k - 1) + k * C(j, k)
    - Useful to break weighted binomial sums into simpler parts

48. Ratio Between Binomials:
    - C(n, k + 1) = (n - k) / (k + 1) * C(n, k)
    - Handy for simplifying recursive or dynamic binomial expressions

49. DSU on 2D grid (reverse build, e.g., paint black → white):
    - pain all query start from reverse removing
    - Each time a cell is made white:
        * If no white neighbor → comp++
        * Else, check 4 neighbors and connect different components → comp--
        * Finally, connect current cell to one neighbor

    - Pseudocode:
      auto calc = [&](int x, int y) {
          vector<pii> cnt;
          for (int d = 0; d < 4; d++) {
              int nx = x + dx[d], ny = y + dy[d];
              if (valid(nx, ny) && vis[nx][ny] == 0)
                  cnt.push_back({nx, ny});
          }
          if (cnt.empty()) comp++;
          else {
              auto root = cnt[0];
              for (int i = 1; i < cnt.size(); i++) {
                  if (dsu.find(root) != dsu.find(cnt[i])) {
                      comp--;
                      dsu.join(root, cnt[i]);
                  }
              }
              dsu.join({x, y}, root);
          }
      };

50. Choose values where OR of all ai <= k:
    - tmp = k, turn off ith bit in k of tmp
    - Turn on all lower bits (0 to i-1) 
    - Then check for each mask if((tmp | ai) == tmp) add ans

51. Minimum swaps to sort a permutation:
    - Build graph: edges from i to p[i]
    - Answer = n - number_of_components


