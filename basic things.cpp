#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

void __print(int x)
{
    cerr << x;
}
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char* x) { cerr << '\"' << x << '\"'; }
void __print(const string& x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template <typename T, typename V>
void __print(const pair<T, V>& x)
{
    cerr << '{';
    __print(x.first);
    cerr << ',';
    __print(x.second);
    cerr << '}';
}
template <typename T>
void __print(const T& x)
{
    int f = 0;
    cerr << '{';
    for (auto& i : x)
        cerr << (f++ ? "," : ""), __print(i);
    cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v)
{
    __print(t);
    if (sizeof...(v))
        cerr << ", ";
    _print(v...);
}
#ifndef ONLINE_JUDGE
#define debug(x...)               \
    cerr << "[" << #x << "] = ["; \
    _print(x)
#else
#define debug(x...)
#endif

const int MOD = 1e9 + 7;
const int MX = 2e5 + 10;
array<int, MX> factorial;
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
inline int inverse(int a) {
    return power(a, MOD - 2);
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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}