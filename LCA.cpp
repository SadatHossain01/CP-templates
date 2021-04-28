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

const int MX = 10000;
const int LOG = __lg(MX - 1) + 1;
int n;
vector<vector<int>>children(MX);
vector<vector<int>>adjacent(MX);
vector<vector<int>>up(MX, vector<int>(LOG)); //up[i][j] is the 2^j th ancestor of i
vector<int>depth(MX);

//this version is applicable if inputs are given in node-children form
void dfs(int v) {
    for (auto child : children[v]) {
        depth[child] = depth[v] + 1;
        up[child][0] = v;
        for (int j = 1; j < LOG; j++) {
            up[child][j] = up[up[child][j - 1]][j - 1];
        }
        dfs(child);
    }
}
//this version is applicable if inputs are given in edge form
void dfs(int v, int parent) {
    for (auto neighbour : adjacent[v]) {
        if (neighbour == parent) continue;
        depth[neighbour] = depth[v] + 1;
        up[neighbour][0] = v;
        for (int j = 1; j < LOG; j++) {
            up[neighbour][j] = up[up[neighbour][j - 1]][j - 1];
        }
        dfs(neighbour, v);
    }
}
int get_distance_between_nodes_of_a_tree(int a, int b) {
    static bool isDFSdone = false;
    if (!isDFSdone) {
        dfs(1, -1);
        isDFSdone = true;
    }
    if (depth[a] < depth[b]) swap(a, b);
    int distance = 0;
    int k = depth[a] - depth[b];
    for (int j = LOG - 1; j >= 0; j--) {
        if (k & (1 << j)) {
            distance += (1 << j);
            a = up[a][j];
        }
    }
    if (a == b) return distance;
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
            distance += 2 * (1 << j);
        }
    }
    return distance + 2;
}
int get_LCA(int a, int b) {
    static bool isDFSdone = false;
    if (!isDFSdone) {
        dfs(0);
        //or, dfs(0, -1);
        isDFSdone = true;
    }
    if (depth[a] < depth[b]) swap(a, b);
    int k = depth[a] - depth[b];
    for (int j = LOG - 1; j >= 0; j--) {
        if (k & (1 << j)) {
            a = up[a][j];
        }
    }
    if (a == b) return a;
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}