#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

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