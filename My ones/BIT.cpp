#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 1-based indexing
// point-update and range-query
const int MX = 1e5 + 5;
vector<ll> BIT(MX), a(MX);
int n;
void add(int idx, int delta) {  // increase idx'th element by delta
    for (; idx <= n; idx += idx & -idx) BIT[idx] += delta;
}
ll query(int idx) {  // returns sum in range [1, x]
    ll sum = 0;
    for (; idx > 0; idx -= idx & -idx) sum += BIT[idx];
    return sum;
}
ll query(int l, int r) { return query(r) - query(l - 1); }

// 2D
const int mx = 1e3 + 5;
int r, c;
vector<vector<ll>> bit(r, vector<ll>(c));
ll sum(int x, int y) {
    ll ret = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1) ret += bit[i][j];
    return ret;
}

void add(int x, int y, int delta) {
    for (int i = x; i < bit.size(); i = i | (i + 1))
        for (int j = y; j < bit[i].size(); j = j | (j + 1)) bit[i][j] += delta;
}