#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
#define int long long
const int MOD = 1e9 + 7;

/*
g_n = a_1 g_(n-1) + a_2 g_(n-2) + a_3 g_(n-3) + ... + a_k g_(n-k)
[a1 a2 a3 ... ak
1 0 0 ... 0
0 1 0 ... 0
0 0 1 ... 0
0 0 0 ... 0] ^ (n - k) dimension: (k + 1) x k
x
[b_1
b_2
b_3
...
b_k] dimension: k x 1 (b1, b2, ..., bk are the first k elements of the sequence)
=
[g_n
g_n-1
g_n-2
...
g_n-k+1]
*/

struct Matrix {
    int nums[2][2];
    void print() {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                cout << nums[i][j] << " ";
            }
            cout << endl;
        }
    }
};

Matrix mul(Matrix &a, Matrix &b) {
    Matrix temp{{{0, 0}, {0, 0}}};
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 2; i++) {
            for (int k = 0; k < 2; k++) {
                temp.nums[j][k] =
                    (temp.nums[j][k] + (a.nums[j][i] * b.nums[i][k]) % MOD) %
                    MOD;
            }
        }
    }
    return temp;
}

Matrix power(Matrix a, int b) {
    Matrix temp{{{1, 0}, {0, 1}}};
    while (b) {
        if (b % 2) temp = mul(temp, a);
        a = mul(a, a);
        b /= 2;
    }
    return temp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    Matrix a;
    a.nums[0][0] = 0;
    a.nums[0][1] = 1;
    a.nums[1][0] = 1;
    a.nums[1][1] = 1;
    Matrix ans = power(a, n);

    cout << ans.nums[1][0] << endl;
    return 0;
}