#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

const int MX = 2e5 + 10;
array<int, MX> factorial;
const int MOD = 1e9 + 7;
inline int add(int a, int b) {
    a += b;
    while (a >= MOD) a -= MOD;
    while (a < 0) a += MOD;
    return a;
}
inline void add_self(int& a, int b) {
    a = add(a, b);
}
inline int sub(int a, int b) {
    return add(a, -b);
}
inline void sub_self(int& a, int b) {
    a = sub(a, b);
}
inline int mul(int a, int b) {
    return (a * 1LL * b) % MOD;
}
inline void mul_self(int& a, int b) {
    a = mul(a, b);
}
int power(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) mul_self(ans, a);
        mul_self(a, a);
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
inline int inverse(int a) {
    int x, y;
    int whatever = gcd(a, MOD, x, y);
    return x;
}
inline int divide(int a, int b) {
    return mul(a, inverse(b));
}
inline void divide_self(int& a, int b) {
    a = divide(a, b);
}
void precompute()
{
    factorial[0] = 1;
    for (int i = 1; i < MX; i++) {
        factorial[i] = mul(factorial[i - 1], i);
    }
}
inline int nCr(int n, int r) {
    static bool isPrecomputationDone = false;
    if (!isPrecomputationDone) {
        precompute();
        isPrecomputationDone = true;
    }
    if (r > n) return 0;
    if (n == r || r == 0) return 1;
    return divide(factorial[n], mul(factorial[r], factorial[n - r]));
}
inline int nPr(int n, int r) {
    static bool isPrecomputationDone = false;
    if (!isPrecomputationDone) {
        precompute();
        isPrecomputationDone = true;
    }
    if (r > n) return 0;
    if (r == 0) return 1;
    if (n == r) return factorial[n];
    return divide(factorial[n], factorial[n - r]);
}
int shortestSubarraySum(vector<int>& a) {
    int sum = 0;
    int ans = INT_MIN;
    const int n = a.size();
    for (int i = 0; i < n; i++) {
        sum += a[i];
        ans = max(ans, sum);
        sum = max(sum, 0);
    }
    return ans;
}
void string_decrement(string& s) {
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] != '0') {
            s[i]--;
            break;
        }
        else s[i] = '9';
    }
}

__int128 read() {
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
bool cmp(__int128 x, __int128 y) { return x > y; }