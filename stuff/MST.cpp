#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge {
    int from, to;
    ll weight;
    bool operator<(const Edge& other) const {
        if (weight != other.weight) return weight < other.weight;
        return make_pair(from, to) < make_pair(other.from, other.to);
    }
};

int n;
vector<int> parent, size_v;
vector<pair<int, int>> result;  // resulting MST

int find_set(int v) {  // O(1)
    if (v == parent[v])
        return v;
    else
        return parent[v] = find_set(parent[v]);
}
bool union_sets(int a, int b) {  // O(1)
    // returns false if same set
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (size_v[a] < size_v[b]) swap(a, b);
        parent[b] = a;
        size_v[a] += size_v[b];
        return true;
    } else
        return false;
}

ll kruskal(vector<Edge>& edges) {
    parent.resize(n + 2);
    size_v.assign(n + 2, 1);
    for (int i = 0; i <= n; i++) parent[i] = i;

    sort(edges.begin(), edges.end());

    ll total_weight = 0;
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].from;
        int v = edges[i].to;
        ll w = edges[i].weight;
        if (find_set(u) != find_set(v)) {
            total_weight += w;
            result.push_back(make_pair(u, v));
            union_sets(u, v);
        }
    }
    return total_weight;
}