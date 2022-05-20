#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

int n, m, timer = 1, SCC;
vector<vector<int>> adj;
vector<bool> visited, onStack;
vector<int> inTime, lowLink;
stack<int> st;

void tarjan(int node) {
    visited[node] = true;
    inTime[node] = lowLink[node] = timer++;
    // low link is the smallest node id reachable from that node including the
    // node itself
    onStack[node] = true;
    st.push(node);
    for (int neighbour : adj[node]) {
        if (visited[neighbour]) {
            if (onStack[neighbour]) {
                lowLink[node] = min(lowLink[node], inTime[neighbour]);
            }
        } else {
            tarjan(neighbour);
            if (onStack[neighbour]) {
                lowLink[node] = min(lowLink[node], lowLink[neighbour]);
            }
        }
    }
    if (inTime[node] == lowLink[node]) {
        // the following loop gives you the chance to process the nodes that
        // belong to this SCC
        cout << "SCC #" << ++SCC << endl;
        int u;
        while (true) {
            u = st.top();
            st.pop();
            onStack[u] = false;
            cout << u << " ";
            if (u == node) break;
        }
        cout << endl;
    }
}

void solve() {
    cin >> n >> m;
    adj.resize(n + 1);
    visited.assign(n + 1, false);
    onStack.assign(n + 1, false);
    inTime.resize(n + 1);
    lowLink.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    for (int i = 1; i <= n; i++)
        if (visited[i] == false) tarjan(i);
}