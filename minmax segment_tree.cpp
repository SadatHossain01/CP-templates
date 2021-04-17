#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

const long long NEUTRAL_ELEMENT = LONG_LONG_MAX;

struct seg_tree {
    int size;
    vector <long long> sums;
    void initiate(int n) {
        size = 1;
        while (size < n) size <<= 1;
        sums.assign(2 * size, 0LL);
    }
    long long combine(long long a, long long b) { return min(a, b); }
    void build(vector <int>& numbers, int index, int start, int end) {
        if (end - start == 1) {
            if (start < numbers.size()) {
                sums[index] = numbers[start];
            }
            return;
        }
        int mid = (start + end) / 2;
        build(numbers, index * 2 + 1, start, mid);
        build(numbers, index * 2 + 2, mid, end);
        sums[index] = combine(sums[index * 2 + 1], sums[index * 2 + 2]);
    }
    void build(vector<int>& numbers) {
        build(numbers, 0, 0, size);
    }
    void set(int i, int value, int index, int start, int end) {
        if (end - start == 1) {
            sums[index] = value;
            return;
        }
        int mid = (start + end) / 2;
        if (i < mid) {
            set(i, value, index * 2 + 1, start, mid);
        }
        else {
            set(i, value, index * 2 + 2, mid, end);
        }
        sums[index] = combine(sums[index * 2 + 1], sums[index * 2 + 2]);
    }
    void set(int i, int value) {
        set(i, value, 0, 0, size);
    }
    long long sum(int l, int r, int index, int start, int end) {
        if (r <= start || end <= l) return NEUTRAL_ELEMENT;
        if (start >= l && end <= r) return sums[index];
        int mid = (start + end) / 2;
        auto s1 = sum(l, r, index * 2 + 1, start, mid);
        auto s2 = sum(l, r, index * 2 + 2, mid, end);
        return combine(s1, s2);
    }
    long long sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector <int> numbers(n);
    seg_tree st;
    st.initiate(n);
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }
    st.build(numbers);
    while (m--) {
        int op;
        cin >> op;
        if (op == 2) {
            int l, r;
            cin >> l >> r;
            cout << st.sum(l, r) << endl;
        }
        else {
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        }
    }
}

