#include <bits/stdc++.h>
using namespace std;

// g++ -fsanitize=address -static-libasan -g -DLOCAL -O3 -std=c++14 b.cpp
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif

#define endl "\n"
typedef long long ll;

const int MX = 250015;
vector<int> numbers(MX + 2, 0);

// solves LightOJ Rip Van Winkle's Code
struct LazyStruct {
    ll sum, cntA, cntB, del, paramC;
    bool pendingC;
};

typedef long long ll;
struct seg_tree {
    vector<LazyStruct> tree;
    const ll NEUTRAL_ELEMENT = 0LL;
    inline int lc(int x) { return (x << 1); }        // left child
    inline int rc(int x) { return ((x << 1) | 1); }  // right child
    seg_tree(int n) { tree.assign(4 * n, {0, 0, 0, 0, 0, false}); }
    inline ll combine(ll a, ll b) { return a + b; }
    inline void pushA(int at, int start, int end) {
        if (at >= tree.size()) return;
        ll len = 0;
        int mid = (start + end) >> 1;

        if (lc(at) < tree.size()) {
            int lx = lc(at);
            len = mid - start + 1;
            tree[lx].sum +=
                tree[at].del * len + tree[at].cntA * (len * (len + 1)) / 2;
            tree[lx].del += tree[at].del;
            tree[lx].cntA += tree[at].cntA;
        }

        if (rc(at) < tree.size()) {
            int rx = rc(at);
            len = end - mid;
            tree[rx].sum += tree[at].del * len +
                            tree[at].cntA * (mid + 1 - start) * len +
                            tree[at].cntA * (len * (len + 1)) / 2;
            // notice the tree[at].cntA * (mid - start + 1) part
            // reason for the 2nd part, 1 2 3 4 5 6
            // 1 2 3             4 5 6
            // so for the right child, there is a del = 3,
            // (3 + 1) + (3 + 2) +(3 + 3)
            tree[rx].del += tree[at].del + tree[at].cntA * (mid + 1 - start);
            tree[rx].cntA += tree[at].cntA;
        }

        tree[at].cntA = 0;
        tree[at].del = 0;  // have pushed down all del and cntA stuffs
    }
    inline void pushB(int at, int start, int end) {
        if (at >= tree.size()) return;
        ll len = 0;
        int mid = (start + end) >> 1;
        // debug('B', at, start, end, sum[at], cntB[at], del[at]);
        if (lc(at) < tree.size()) {
            int lx = lc(at);
            len = mid - start + 1;
            tree[lx].sum += (tree[at].del + tree[at].cntB * (end - mid)) * len +
                            tree[at].cntB * (len * (len + 1)) / 2;
            tree[lx].del += tree[at].del + tree[at].cntB * (end - mid);
            tree[lx].cntB += tree[at].cntB;
        }

        if (rc(at) < tree.size()) {
            int rx = rc(at);
            len = end - mid;
            tree[rx].sum +=
                tree[at].del * len + tree[at].cntB * (len * (len + 1)) / 2;
            tree[rx].del += tree[at].del;
            tree[rx].cntB += tree[at].cntB;
        }

        tree[at].cntB = 0;
    }
    inline void pushC(int at, int start, int end) {
        if (at >= tree.size()) return;
        if (!tree[at].pendingC) return;
        ll len = 0;
        int mid = (start + end) >> 1;
        // debug('C', at, start, end, sum[at], paramC[at], (int)pendingC[at]);
        if (lc(at) < tree.size()) {
            int lx = lc(at);
            len = mid - start + 1;
            tree[lx].sum = len * tree[at].paramC;
            tree[lx].paramC = tree[at].paramC;
            tree[lx].pendingC = true;
            tree[lx].cntA = tree[lx].cntB = tree[lx].del = 0;
        }

        if (rc(at) < tree.size()) {
            int rx = rc(at);
            len = end - mid;
            tree[rx].sum = len * tree[at].paramC;
            tree[rx].paramC = tree[at].paramC;
            tree[rx].pendingC = true;
            tree[rx].cntA = tree[rx].cntB = tree[rx].del = 0;
        }

        tree[at].pendingC = false;
        tree[at].paramC = 0;
    }
    inline void push_all(int at, int start, int end) {
        pushC(at, start, end);
        pushA(at, start, end);
        pushB(at, start, end);
    }
    inline void pull(int at) {  // used in building and updating the tree,
                                // pulling the leaf values to the root
        tree[at].sum = combine(tree[lc(at)].sum, tree[rc(at)].sum);
    }
    // call build(1, 1, n)
    void build(int at, int start, int end) {
        if (start == end) {
            tree[at].sum = numbers[start];
            return;
        }
        int mid = (start + end) >> 1;
        build(lc(at), start, mid);
        build(rc(at), mid + 1, end);
        pull(at);
        return;
    }
    void update(int at, int start, int end, char ty, int st, int nd,
                int x = 0) {
        if (start > nd || end < st) return;
        push_all(at, start, end);
        ll len = end - start + 1;
        if (start >= st && end <= nd) {
            if (ty == 'A') {
                tree[at].cntA++;
                tree[at].del += start - st;
                tree[at].sum += len * (start - st) + len * (len + 1) / 2;
            } else if (ty == 'B') {
                tree[at].cntB++;
                tree[at].del += nd - end;
                tree[at].sum += len * (nd - end) + len * (len + 1) / 2;
            } else if (ty == 'C') {
                tree[at].pendingC = true;
                tree[at].paramC = x;
                tree[at].sum = len * x;
                tree[at].cntA = tree[at].cntB = tree[at].del = 0;
            }
            push_all(at, start, end);
            return;
        }
        int mid = (start + end) >> 1;
        update(lc(at), start, mid, ty, st, nd, x);
        update(rc(at), mid + 1, end, ty, st, nd, x);
        pull(at);
    }
    // for query [l, r] call query(1, 1, n, l, r)
    ll query(int at, int start, int end, int q_left, int q_right) {
        push_all(at, start, end);
        if (start > q_right || end < q_left) return NEUTRAL_ELEMENT;
        if (start >= q_left && end <= q_right) return tree[at].sum;
        int mid = (start + end) >> 1;
        return combine(query(lc(at), start, mid, q_left, q_right),
                       query(rc(at), mid + 1, end, q_left, q_right));
    }
    void show() {
        debug(sum);
        debug(cntA);
        debug(cntB);
        debug(del);
        debug(paramC);
        debug((int)pendingC);
    }
};

void solve() {
    int m;
    cin >> m;
    seg_tree seg(MX - 2);
    int n = min(250005, MX - 1);
    seg.build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        char a;
        cin >> a;
        int st, nd;
        cin >> st >> nd;
        if (a == 'A') {
            seg.update(1, 1, n, 'A', st, nd);
        } else if (a == 'B') {
            seg.update(1, 1, n, 'B', st, nd);
        } else if (a == 'C') {
            int x;
            cin >> x;
            seg.update(1, 1, n, 'C', st, nd, x);
        } else if (a == 'S') {
            cout << seg.query(1, 1, n, st, nd) << endl;
        }
        // seg.show();
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifdef LOCAL
    auto inn = freopen("in.txt", "r", stdin);
    auto outt = freopen("out.txt", "w", stdout);
#endif

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++) {
        cout << "Case " << tc << ":" << endl;
        solve();
    }
}