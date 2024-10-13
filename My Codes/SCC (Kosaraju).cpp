#include <iostream>
#include <stack>
#include <vector>
using namespace std;

#define endl "\n"

vector<vector<int>> adj, adj_rev;
vector<bool> visited;
stack<int> st;

void dfs1(int node) {
    visited[node] = true;
    for (auto& other : adj[node]) {
        if (!visited[other]) dfs1(other);
    }
    st.push(node);
}

void dfs2(int node) {
    visited[node] = true;
    cout << node << " ";
    for (auto& other : adj_rev[node]) {
        if (!visited[other]) dfs2(other);
    }
}

int main() {
    int n, s;
    cin >> n >> s;
    visited.assign(n + 1, false);
    adj.resize(n + 1);
    adj_rev.resize(n + 1);
    for (int i = 0; i < s; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj_rev[b].push_back(a);
    }
    for (int i = 1; i <= n; i++)
        if (!visited[i]) dfs1(i);
    visited.assign(n + 1, false);
    while (!st.empty()) {
        int now = st.top();
        st.pop();
        if (visited[now]) continue;
        dfs2(now);
        cout << endl;
    }
}

/*
8
13
1 2
2 3
3 1
4 5
5 4
2 4
2 6
3 6
6 7
7 6
4 7
7 8
5 8

Output:
1 2 3
4 5
6 7
*/