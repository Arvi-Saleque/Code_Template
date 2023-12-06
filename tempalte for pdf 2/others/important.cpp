1. if ans % mod is used never divide ans with only val must use inverse modulo 
for example the final ans is 'ans / 2'
so this is must be ans * inverse_modulo(2); 
2. if there is any subtract operation, mod must be add with the value 
ans = ans + div_group_sum(pos-1, (sum + (a[pos] % d + d) % d) % d, cnt - 1);
not 
ans = ans + div_group_sum(pos-1, (sum + (a[pos]  % d), cnt - 1);
3. Number of trailing zeroes in base B representation of N!
as same as finding the highest power of B in N!. (Largest power of k in n!)
so the ans is just largestPowerOfB(N, B)
4. let a number is N. find x such that x^3 <= N and N = x * y
now x contain all prime factor less than N^(1/3) 
and y is prime or y = p1 or y = p1 * p2
