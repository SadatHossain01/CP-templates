#include <bits/stdc++.h>
using namespace std;

const int mx = 1e7 + 5;
bitset<mx> isPrime;
vector<int> Primes;
// space optimized one is faster
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
int eulerPhi(int n) {
    int res = n;
    int sqrtn = sqrt(n);
    for (int i = 0; i < Primes.size() && Primes[i] <= sqrtn; i++) {
        if (n % Primes[i] == 0) {
            while (n % Primes[i] == 0) n /= Primes[i];
            sqrtn = sqrt(n);
            res /= Primes[i];
            res *= (Primes[i] - 1);
        }
    }
    if (n != 1) {
        res /= n;
        res *= n - 1;
    }
    return res;
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

vector<char> segmentedSieve(long long L, long long R) {
    // generate all primes up to sqrt(R)
    long long lim = sqrt(R);
    vector<char> mark(lim + 1, false);
    vector<long long> primes;
    for (long long i = 2; i <= lim; ++i) {
        if (!mark[i]) {
            primes.emplace_back(i);
            for (long long j = i * i; j <= lim; j += i) mark[j] = true;
        }
    }

    vector<char> isPrime(R - L + 1, true);
    // 0 denotes L, 1 denotes L + 1, so on...
    for (long long i : primes)
        for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;
    if (L == 1) isPrime[0] = false;
    return isPrime;
}

// Memory Optimized Block Sieve, uses O(S + sqrt(n)) memory
// vector<int> prime_generated;
int count_primes(int n) {
    const int S = 10000;

    vector<int> primes;
    int nsqrt = sqrt(n);
    vector<char> is_prime(nsqrt + 2, true);
    for (int i = 2; i <= nsqrt; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= nsqrt; j += i) is_prime[j] = false;
        }
    }

    int result = 0;
    vector<char> block(S);
    for (int k = 0; k * S <= n; k++) {
        fill(block.begin(), block.end(), true);
        int start = k * S;
        for (int p : primes) {
            int start_idx = (start + p - 1) / p;
            int j = max(start_idx, p) * p - start;
            for (; j < S; j += p) block[j] = false;
        }
        if (k == 0) block[0] = block[1] = false;
        for (int i = 0; i < S && start + i <= n; i++) {
            if (block[i]) {
                // prime_generated.push_back(start + i);
                result++;
            }
        }
    }
    return result;
}
