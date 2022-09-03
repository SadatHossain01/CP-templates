#include <bits/stdc++.h>
using namespace std;

const int INF = 2e8;
int n, m;
vector<vector<int>> adj_mat, distmm, distfw, parent;

vector<vector<int>> extend_shortest_path(vector<vector<int>>& d,
                                         vector<vector<int>>& w) {
    vector<vector<int>> new_d(n + 2, vector<int>(n + 2));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            new_d[i][j] = INF;
            for (int k = 1; k <= n; k++) {
                new_d[i][j] = min(new_d[i][j], d[i][k] + w[k][j]);
            }
        }
    }

    return new_d;
}

void mat_mul_shortest_path_faster() {
    distmm = adj_mat;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) distmm[i][i] = 0;
    }

    int b = n - 1;
    int m = 1;
    while (m < b) {
        distmm = extend_shortest_path(distmm, distmm);
        m *= 2;
    }
}

void floyd_warshall() {
    distfw = adj_mat;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) distfw[i][i] = 0;
    }

    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= n; k++) {
                if (distfw[i][k] > distfw[i][j] + distfw[j][k]) {
                    distfw[i][k] = distfw[i][j] + distfw[j][k];
                    if (i != k) parent[i][k] = parent[j][k];
                }
            }
        }
    }
}