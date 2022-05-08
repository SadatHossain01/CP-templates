#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
typedef long long ll;

int m, n;
//m is number of nodes, n number of edges

ll kruskal(const vector<pair<int, pair<int, int>>>& edges) {
  vector<int> tree_id(m);
  iota(tree_id.begin(), tree_id.end(), 0);
  ll min_cost = 0;
  for (const auto& e : edges) {
    if (tree_id[e.second.first] != tree_id[e.second.second]) {
      min_cost += e.first;

      int old_id = tree_id[e.second.first];
      int new_id = tree_id[e.second.second];
      for (int i = 0; i < m; i++) {
        if (tree_id[i] == old_id) tree_id[i] = new_id;
      }
    }
  }
  return min_cost;
}

void solve() {
  cin >> m >> n;

  ll total_length = 0;
  vector<pair<int, pair<int, int>>> edges(n);
  for (int i = 0; i < n; i++) {
    //x and y are nodes, and z is weight/length
    int x, y, z;
    cin >> x >> y >> z;
    edges[i] = {z, {x, y}};
    total_length += z;
  }
  sort(edges.begin(), edges.end());
  cout << total_length - kruskal(edges) << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  solve();
}