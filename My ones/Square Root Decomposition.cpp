#include <bits/stdc++.h>
using namespace std;
int n, q;
vector<int> a(n);
int main() {
    // input data
    //  preprocessing
    const int len =
        (int)sqrt(n + .0) + 1;  // size of the block and the number of blocks
    vector<int> b(len);
    for (int i = 0; i < n; ++i) b[i / len] += a[i];

    // answering the queries
    while (q--) {
        int l, r;
        // read input data for the next query
        cin >> l >> r;
        int sum = 0;
        int c_l = l / len, c_r = r / len;
        if (c_l == c_r)
            for (int i = l; i <= r; ++i) sum += a[i];
        else {
            for (int i = l, end = (c_l + 1) * len - 1; i <= end; ++i)
                sum += a[i];
            for (int i = c_l + 1; i <= c_r - 1; ++i) sum += b[i];
            for (int i = c_r * len; i <= r; ++i) sum += a[i];
        }
    }
}
