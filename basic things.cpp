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
int compute_hash_for_a_string(const string& s) {
    const int p = 31; // choose p = 53 if both uppercase and lowercase letters are allowed
    int hash_value = 0;
    const int n = s.size();
    for (int i = 0; i < n; i++) {
        add_self(hash_value, mul(s[i] - 'a' + 1, power(p, i + 1)));
    }
    return hash_value;
}
vector<int> compute_prefix_hash(const string& s) {
    const int n = s.size();
    const int p = 31; // choose p = 53 if both uppercase and lowercase letters are allowed
    int also = p;
    vector<int>hash_values(n, 0);
    for (int i = 0; i < n; i++) {
        hash_values[i] = mul(also, s[i] - 'a' + 1);
        if (i) add_self(hash_values[i], hash_values[i - 1]);
        mul_self(also, p);
    }
    return hash_values;
}
inline int substring_hash(vector<int>& hash_values, int l, int r, const int p = 31) {
    if (l > r) return 0;
    if (l == 0) return hash_values[r];
    return mul(sub(hash_values[r], hash_values[l - 1]), inverse(power(p, l)));
}
inline int nCr(int n, int r) {
    if (r > n) return 0;
    if (n == r || r == 0) return 1;
    return divide(factorial[n], mul(factorial[r], factorial[n - r]));
}
void precompute()
{
    factorial[0] = 1;
    for (int i = 1; i < MX; i++) {
        factorial[i] = mul(factorial[i - 1], i);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
// #ifndef ONLINE_JUDGE
//     freopen("in.txt", "r", stdin);
//     freopen("out.txt", "w", stdout);
// #endif
    precompute();
}