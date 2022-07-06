#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6 + 5;
vector<int> size(MX);
vector<int> parent(MX);

int find_set(int v) {  // O(1)
    if (v == parent[v])
        return v;
    else
        return parent[v] = find_set(parent[v]);
}
void make_set(int v) {
    parent[v] = v;
    size[v] = 1;
}
bool union_sets(int a, int b) {  // O(1)
    // returns false if same set
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    } else
        return false;
}
