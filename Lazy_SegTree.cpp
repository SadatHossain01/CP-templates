#include <bits/stdc++.h>
using namespace std;

const int MX = 2e5 + 5;
vector<int> numbers(MX);

typedef long long ll;

struct seg_tree {
    vector<ll> vec, lazy;
    const ll NEUTRAL_ELEMENT = 0LL;
    inline int lc(int x) { return (x << 1); }        // left child
    inline int rc(int x) { return ((x << 1) | 1); }  // right child
    seg_tree(int n) {
        vec.assign(4 * n, NEUTRAL_ELEMENT);
        lazy.assign(4 * n, NEUTRAL_ELEMENT);
    }
    inline ll combine(ll a, ll b) { return a + b; }
    inline void push(int at, int start, int end) {
        if (lazy[at] == NEUTRAL_ELEMENT) return;
        vec[at] = combine(vec[at], lazy[at] * (end - start + 1));
        if (start != end) {
            lazy[lc(at)] = combine(lazy[lc(at)], lazy[at]);
            lazy[rc(at)] = combine(lazy[rc(at)], lazy[at]);
        }
        lazy[at] = NEUTRAL_ELEMENT;
    }
    inline void pull(int at) { vec[at] = combine(vec[lc(at)], vec[rc(at)]); }
    // call build(1, 1, n)
    void build(int at, int start, int end) {
        lazy[at] = NEUTRAL_ELEMENT;
        if (start == end) {
            vec[at] = numbers[start];
            return;
        }
        int mid = (start + end) >> 1;
        build(lc(at), start, mid);
        build(rc(at), mid + 1, end);
        pull(at);
        return;
    }
    // for incrementing index [l, r] by val, call update(1, 1, n, l, r, val)
    void update(int at, int start, int end, int q_left, int q_right, ll val) {
        push(at, start, end);
        if (start > q_right || end < q_left) return;
        if (start >= q_left && end <= q_right) {
            lazy[at] = val;
            push(at, start, end);
            return;
        }
        int mid = (start + end) >> 1;
        update(lc(at), start, mid, q_left, q_right, val);
        update(rc(at), mid + 1, end, q_left, q_right, val);
        pull(at);
    }
    // for query [l, r] call query(1, 1, n, l, r)
    ll query(int at, int start, int end, int q_left, int q_right) {
        push(at, start, end);
        if (start > q_right || end < q_left) return NEUTRAL_ELEMENT;
        if (start >= q_left && end <= q_right) return vec[at];
        int mid = (start + end) >> 1;
        return combine(query(lc(at), start, mid, q_left, q_right),
                       query(rc(at), mid + 1, end, q_left, q_right));
    }
};