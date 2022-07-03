#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

const int MX = 1e6 + 5;
const int p1 = 137, p2 = 281;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
// Some back-up primes: 1072857881, 1066517951, 1040160883
// use double hashing for caution
// if both hash values match, then same string
// else different
vector<int> POWER1(MX), POWER2(MX);
vector<int> INV1(MX), INV2(MX);
int gcd(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}
int modInverse(int a, int m) {
    int x, y;
    int g = gcd(a, m, x, y);
    while (x < 0) x += m;
    return x;
}
void precompute(const int p, const int MOD, vector<int>& POWER,
                vector<int>& INV) {
    POWER[0] = 1;
    INV[0] = 1;
    int inv_of_p = modInverse(p, MOD);
    for (int i = 1; i < MX; i++) {
        POWER[i] = (POWER[i - 1] * 1LL * p) % MOD;
        INV[i] = (INV[i - 1] * 1LL * inv_of_p) % MOD;
    }
}
int compute_hash_for_a_string(const string& s, const int p, const int MOD,
                              const vector<int>& POWER) {
    // call precompute() first
    int hash_value = 0;
    const int n = s.size();
    for (int i = 0; i < n; i++) {
        int val = ((s[i] - 'a' + 1) * 1LL * POWER[i]) % MOD;
        hash_value = (hash_value + 0LL + val) % MOD;
    }
    return hash_value;
}
vector<int> compute_prefix_hash(const string& s, const int p, const int MOD) {
    const int n = s.size();
    int p_power = 1;
    vector<int> hash_values(n, 0);
    for (int i = 0; i < n; i++) {
        hash_values[i] = (p_power * 1LL * (s[i] - 'a' + 1)) % MOD;
        if (i > 0)
            hash_values[i] = (hash_values[i] + 0LL + hash_values[i - 1]) % MOD;
        p_power = (p_power * 1LL * p) % MOD;
    }
    return hash_values;
}
vector<int> compute_suffix_hash(const string& s, const int p, const int MOD) {
    const int n = s.size();
    int p_power = 1;
    vector<int> hash_values(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        hash_values[i] = (p_power * 1LL * (s[i] - 'a' + 1)) % MOD;
        if (i < n - 1)
            hash_values[i] = (hash_values[i] + 0LL + hash_values[i + 1]) % MOD;
        p_power = (p_power * 1LL * p) % MOD;
    }
    return hash_values;
}
int prefix_hash(vector<int>& pref, vector<int>& INV, int l, int r, const int p,
                const int MOD) {
    // call precompute() first
    assert(l <= r);
    if (l == 0) return pref[r];
    int inv = INV[l];
    int val = (pref[r] + 0LL - pref[l - 1] + MOD) % MOD;
    return (inv * 1LL * val) % MOD;
}
pair<int, int> getBothPrefixHashes(vector<int>& pref1, vector<int>& pref2,
                                   int l, int r) {
    pair<int, int> ans;
    ans.first = prefix_hash(pref1, INV1, l, r, p1, MOD1);
    ans.second = prefix_hash(pref2, INV2, l, r, p2, MOD2);
    return ans;
}
int suffix_hash(vector<int>& suf, vector<int>& INV, int l, int r, const int p,
                const int MOD) {
    // call precompute() first
    const int n = suf.size();
    assert(l <= r);
    if (r == n - 1) return suf[l];
    int inv = INV[n - 1 - r];
    int val = (suf[l] + 0LL - suf[r + 1] + MOD) % MOD;
    return (inv * 1LL * val) % MOD;
}
pair<int, int> getBothSuffixHashes(vector<int>& suf1, vector<int>& suf2, int l,
                                   int r) {
    pair<int, int> ans;
    ans.first = prefix_hash(suf1, INV1, l, r, p1, MOD1);
    ans.second = prefix_hash(suf2, INV2, l, r, p2, MOD2);
    return ans;
}