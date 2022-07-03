#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
typedef long long ll;

const int MOD1 = 1e9 + 7;

struct Matrix {
    int r, c;
    vector<vector<int>> mat;
    Matrix(int r, int c) {
        this->r = r, this->c = c;
        mat.assign(r, vector<int>(c, 0));
    }
    Matrix(vector<vector<int>> &vec) {
        r = vec.size();
        c = vec[0].size();
        mat.assign(r, vector<int>(c, 0));
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) mat[i][j] = vec[i][j];
        }
    }
};

istream &operator>>(istream &in, Matrix &mt) {
    for (int i = 0; i < mt.r; i++)
        for (int j = 0; j < mt.c; j++) in >> mt.mat[i][j];
    return in;
}
ostream &operator<<(ostream &out, Matrix &mt) {
    for (int i = 0; i < mt.r; i++) {
        for (int j = 0; j < mt.c; j++) out << mt.mat[i][j] << " ";
        out << endl;
    }
    return out;
}

Matrix mul(Matrix &a, Matrix &b) {
    // assert(a.mat[0].size() == b.mat.size());
    Matrix product(a.mat.size(), b.mat[0].size());
    for (int j = 0; j < a.mat.size(); j++) {
        for (int i = 0; i < b.mat.size(); i++) {
            for (int k = 0; k < b.mat[0].size(); k++) {
                product.mat[j][k] = (product.mat[j][k] + 0LL +
                                     (a.mat[j][i] * 1LL * b.mat[i][k]) % MOD1) %
                                    MOD1;
            }
        }
    }
    return product;
}

Matrix power(Matrix a, ll b) {
    // assert(a.mat.size() == a.mat[0].size());
    Matrix ans(a.mat.size(), a.mat.size());
    for (int i = 0; i < ans.mat.size(); i++) ans.mat[i][i] = 1;
    while (b) {
        if (b & 1) ans = mul(ans, a);
        a = mul(a, a);
        b >>= 1;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

    ll n;
    cin >> n;
    Matrix a(2, 2);
    a.mat = {{0, 1}, {1, 1}};
    Matrix ans = power(a, n);
    // cout << ans << endl;
    cout << ans.mat[1][0] << endl;
    return 0;
}