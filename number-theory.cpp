#include <bits/stdc++.h>
using namespace std;

const int mx = 1e7 + 5;
bitset<mx>isPrime;
vector<int>Primes;
void sieve(int n) {
    isPrime.set();
    isPrime[0] = isPrime[1] = false;
    for (int i = 4; i <= n; i += 2) isPrime[i] = false;
    for (int i = 3; i * i <= n; i += 2) {
        if (!isPrime[i]) continue;
        for (int j = i * i; j <= n; j += i) isPrime[j] = false;
    }
    Primes.push_back(2);
    for (int i = 3; i <= n; i += 2) {
        if (isPrime[i]) Primes.push_back(i);
    }
}
int NumberOfDivisors(int n) {
    int ans = 1;
    for (int i = 0; i < Primes.size() && Primes[i] * Primes[i] <= n; i++) {
        int times = 0, prime = Primes[i];
        while (n % prime == 0) {
            times++;
            n /= prime;
        }
        ans *= times + 1;
    }
    if (n > 1) {
        ans *= 2;
    }
    return ans;
}
int main()
{
    return 0;
}