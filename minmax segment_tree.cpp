#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

struct seg_tree {
    int size;
    const int NEUTRAL_ELEMENT = INT_MIN;
    vector <int> maximum;
    void initiate(int n) {
        size = 1;
        while (size < n) size <<= 1;
        maximum.assign(2 * size, 0);
    }
    int combine(int a, int b) { return max(a, b); }
    void build(vector <int>& numbers, int index, int start, int end) {
        if (end - start == 1) {
            if (start < numbers.size()) {
                maximum[index] = numbers[start];
            }
            return;
        }
        int mid = (start + end) / 2;
        build(numbers, index * 2 + 1, start, mid);
        build(numbers, index * 2 + 2, mid, end);
        maximum[index] = combine(maximum[index * 2 + 1], maximum[index * 2 + 2]);
    }
    void build(vector<int>& numbers) {
        build(numbers, 0, 0, size);
    }
    void set(int i, int value, int index, int start, int end) {
        if (end - start == 1) {
            maximum[index] = value;
            return;
        }
        int mid = (start + end) / 2;
        if (i < mid) {
            set(i, value, index * 2 + 1, start, mid);
        }
        else {
            set(i, value, index * 2 + 2, mid, end);
        }
        maximum[index] = combine(maximum[index * 2 + 1], maximum[index * 2 + 2]);
    }
    void set(int i, int value) {
        set(i, value, 0, 0, size);
    }
    int find_maximum(int l, int r, int index, int start, int end) {
        if (r <= start || end <= l) return NEUTRAL_ELEMENT;
        if (start >= l && end <= r) return maximum[index];
        int mid = (start + end) / 2;
        auto s1 = find_maximum(l, r, index * 2 + 1, start, mid);
        auto s2 = find_maximum(l, r, index * 2 + 2, mid, end);
        return combine(s1, s2);
    }
    int find_maximum(int l, int r) {
        return find_maximum(l, r, 0, 0, size);
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
            cout << st.find_maximum(l, r) << endl;
        }
        else {
            int i, v;
            cin >> i >> v;
            st.set(i, v);
        }
    }
}

