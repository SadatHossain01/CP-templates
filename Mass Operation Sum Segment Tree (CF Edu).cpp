#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

struct seg_tree {
    // Only applicable for operations
    // that are both associative and commutative

    int size;
    const long long NEUTRAL_ELEMENT = 0;
    vector<long long> operations;

    void initiate(int n) {
        size = 1;
        while (size < n) size <<= 1;
        operations.assign(2 * size, 0LL);
    }

    long long combine(long long a, long long b) { return a + b; }

    void add(int l, int r, int v, int index, int start, int end) {
        if (r <= start || end <= l) return;
        if (start >= l && end <= r) {
            operations[index] += v;
            return;
        }
        int mid = (start + end) / 2;
        add(l, r, v, index * 2 + 1, start, mid);
        add(l, r, v, index * 2 + 2, mid, end);
    }

    void add(int l, int r, int v) { add(l, r, v, 0, 0, size); }

    long long get(int i, int index, int start, int end) {
        if (end - start == 1) return operations[index];
        int mid = (start + end) / 2;
        long long ret;
        if (i < mid)
            ret = get(i, index * 2 + 1, start, mid);
        else
            ret = get(i, index * 2 + 2, mid, end);
        return ret + operations[index];
    }

    long long get(int i) { return get(i, 0, 0, size); }

    void set(int i, int value, int index, int start, int end) {
        if (end - start == 1) {
            operations[index] = value;
            return;
        }

        int mid = (start + end) / 2;
        if (i < mid)
            set(i, value, index * 2 + 1, start, mid);
        else
            set(i, value, index * 2 + 2, mid, end);

        operations[index] =
            combine(operations[index * 2 + 1], operations[index * 2 + 2]);
    }

    void set(int i, int value) { set(i, value, 0, 0, size); }

    long long sum(int l, int r, int index, int start, int end) {
        if (r <= start || end <= l) return NEUTRAL_ELEMENT;
        if (start >= l && end <= r) return operations[index];
        int mid = (start + end) / 2;
        auto s1 = sum(l, r, index * 2 + 1, start, mid);
        auto s2 = sum(l, r, index * 2 + 2, mid, end);
        return combine(s1, s2);
    }

    long long sum(int l, int r) { return sum(l, r, 0, 0, size); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    seg_tree st;
    st.initiate(n);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, v;
            cin >> l >> r >> v;
            st.add(l, r, v);
        } else {
            int i;
            cin >> i;
            cout << st.get(i) << endl;
        }
    }
}
