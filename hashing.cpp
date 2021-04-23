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
int compute_hash_for_a_string(const string& s) {
    const int p = 31; // choose p = 53 if both uppercase and lowercase letters are allowed
    int hash_value = 0;
    const int n = s.size();
    for (int i = 0; i < n; i++) {
        add_self(hash_value, mul(s[i] - 'a' + 1, power(p, i)));
    }
    return hash_value;
}
vector<int> compute_prefix_hash(const string& s) {
    const int n = s.size();
    const int p = 31; // choose p = 53 if both uppercase and lowercase letters are allowed
    int also = 1;
    vector<int>hash_values(n, 0);
    for (int i = 0; i < n; i++) {
        hash_values[i] = mul(also, s[i] - 'a' + 1);
        if (i) add_self(hash_values[i], hash_values[i - 1]);
        mul_self(also, p);
    }
    return hash_values;
}
vector<int> compute_suffix_hash(const string& s) {
    const int n = s.size();
    const int p = 31; // choose p = 53 if both uppercase and lowercase letters are allowed
    int also = 1;
    vector<int>hash_values(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        hash_values[i] = mul(also, s[i] - 'a' + 1);
        if (i < n - 1) add_self(hash_values[i], hash_values[i + 1]);
        mul_self(also, p);
    }
    return hash_values;
}
int prefix_hash(vector<int>& pref, int l, int r, const int p = 31) {
    if (l == 0) return pref[r];
    int inv = inverse(power(p, l));
    return mul(inv, sub(prefix_hash(pref, 0, r), prefix_hash(pref, 0, l - 1)));
}
int suffix_hash(vector<int>& suf, int l, int r, const int p = 31) {
    const int n = suf.size();
    if (r == n - 1) return suf[l];
    int inv = inverse(power(p, n - 1 - r));
    return mul(inv, sub(suffix_hash(suf, l, n - 1), suffix_hash(suf, r + 1, n - 1)));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
}