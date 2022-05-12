#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

void range_maximum(vector<int>& vec) {
    int n = vec.size();
    vector<vector<int> > sparse(n, vector<int>(__lg(n) + 1, INT_MIN));
    for (int i = 0; i < n; i++) sparse[i][0] = vec[i];
    for (int j = 1; j <= __lg(n); j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            sparse[i][j] = max(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int max_query(vector<vector<int>>& sparse, int l, int r) {
    int len = r - l + 1;
    return max(sparse[l][__lg(len)], sparse[r - (1 << (__lg(len))) + 1][__lg(len)]);
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
int min_query(vector<vector<int>>& sparse, int l, int r) {
    int len = r - l + 1;
    return min(sparse[l][__lg(len)], sparse[r - (1 << (__lg(len))) + 1][__lg(len)]);
}