#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

const int MX = 1e6 + 5;
const int MOD = 1e9 + 7;
int POWER[MX], INV[MX];
int power(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = (ans * 1LL * a) % MOD;
        a = (a * 1LL * a) % MOD;
        b >>= 1;
    }
    return ans;
}
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
void precompute() {
    const int p = 31;  // choose p = 53 if both uppercase and lowercase letters
                       // are allowed
    POWER[0] = 1;
    INV[0] = 1;
    int inv_of_p = modInverse(p, MOD);
    for (int i = 1; i < MX; i++) {
        POWER[i] = (POWER[i - 1] * 1LL * p) % MOD;
        INV[i] = INV[i - 1];
        INV[i] = (INV[i] * 1LL * inv_of_p) % MOD;
    }
}
int compute_hash_for_a_string(const string& s) {
    // call precompute() first
    const int p = 31;  // choose p = 53 if both uppercase and lowercase letters
                       // are allowed
    int hash_value = 0;
    const int n = s.size();
    for (int i = 0; i < n; i++) {
        int val = ((s[i] - 'a' + 1) * 1LL * POWER[i]) % MOD;
        hash_value = (hash_value + 0LL + val) % MOD;
    }
    return hash_value;
}
vector<int> compute_prefix_hash(const string& s) {
    const int n = s.size();
    const int p = 31;  // choose p = 53 if both uppercase and lowercase letters
                       // are allowed
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
vector<int> compute_suffix_hash(const string& s) {
    const int n = s.size();
    const int p = 31;  // choose p = 53 if both uppercase and lowercase letters
                       // are allowed
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
int prefix_hash(vector<int>& pref, int l, int r, const int p = 31) {
    // call precompute() first
    if (l == 0) return pref[r];
    int inv = INV[l];
    int val = (pref[r] + 0LL - pref[l - 1] + MOD) % MOD;
    return (inv * 1LL * val) % MOD;
}
int suffix_hash(vector<int>& suf, int l, int r, const int p = 31) {
    // call precompute() first
    const int n = suf.size();
    if (r == n - 1) return suf[l];
    int inv = INV[n - 1 - r];
    int val = (suf[l] + 0LL - suf[r + 1] + MOD) % MOD;
    return (inv * 1LL * val) % MOD;
}
string longestPalindromicSubstring(const string& s) {
    const int n = s.size();
    vector<int> prefix_hash_values = compute_prefix_hash(s);
    vector<int> suffix_hash_values = compute_suffix_hash(s);
    int start = 0, end = 0;
    int low, high, middle;
    for (int i = 0; i < n; i++) {
        if (min(2 * min(n - 1 - i, i) + 1, 2 * min(n - 1 - i, i - 1) + 2) <=
            end - start + 1)
            continue;  // i + 1 + (n - 1 -i) is the best possible result from
                       // this position
        // odd lengthed ones
        low = 0;
        high = min(i, n - 1 - i);
        while (low <= high) {
            middle = (low + high) / 2;
            if (prefix_hash(prefix_hash_values, i - middle, i + middle) ==
                suffix_hash(suffix_hash_values, i - middle, i + middle)) {
                if (2 * middle + 1 > end - start + 1) {
                    end = i + middle;
                    start = i - middle;
                }
                low = middle + 1;
            } else
                high = middle - 1;
        }
        // even lengthed ones  3, 2, 1 < "string" > 0, 1, 2
        low = 0;
        high = min(n - 1 - i, i - 1);
        while (low <= high) {
            middle = (low + high) / 2;
            if (prefix_hash(prefix_hash_values, i - middle - 1, i + middle) ==
                suffix_hash(suffix_hash_values, i - middle - 1, i + middle)) {
                if (2 * middle + 2 > end - start + 1) {
                    end = i + middle;
                    start = i - middle - 1;
                }
                low = middle + 1;
            } else
                high = middle - 1;
        }
        // even lengthed ones 2, 1, 0 < "string" > 1, 2, 3
        low = 0;
        high = min(n - 2 - i, i);
        while (low <= high) {
            middle = (low + high) / 2;
            if (prefix_hash(prefix_hash_values, i - middle, i + middle + 1) ==
                suffix_hash(suffix_hash_values, i - middle, i + middle + 1)) {
                if (2 * middle + 2 > end - start + 1) {
                    end = i + middle + 1;
                    start = i - middle;
                }
                low = middle + 1;
            } else
                high = middle - 1;
        }
    }
    return s.substr(start, end - start + 1);
}