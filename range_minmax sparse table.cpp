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

int max_query(vector<vector<int>>& sparse, int l, int r) {
    int len = r - l + 1;
    return max(sparse[l][__lg(len)], sparse[r - (1 << (__lg(len))) + 1][__lg(len)]);
}
void range_maximum(vector<int>& vec) {
    int n = vec.size();
    vector<vector<int> > sparse(n, vector<int>(__lg(n) + 1, INT_MAX));
    for (int i = 0; i < n; i++) sparse[i][0] = vec[i];
    for (int j = 1; j <= __lg(n); j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            sparse[i][j] = max(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int min_query(vector<vector<int>>& sparse, int l, int r) {
    int len = r - l + 1;
    return min(sparse[l][__lg(len)], sparse[r - (1 << (__lg(len))) + 1][__lg(len)]);
}
void range_minimum(vector<int>& vec) {
    int n = vec.size();
    vector<vector<int> > sparse(n, vector<int>(__lg(n) + 1, INT_MAX));
    for (int i = 0; i < n; i++) sparse[i][0] = vec[i];
    for (int j = 1; j <= __lg(n); j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            sparse[i][j] = min(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

}