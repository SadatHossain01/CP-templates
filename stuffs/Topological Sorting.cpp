#include <iostream>
#include <stack>
#include <vector>
using namespace std;

#define endl "\n"

int n, d;
vector<vector<int>> adj;
vector<char> color;
stack<int> st;

bool dfs(int node) {
    color[node] = 'G';
    bool flag = true;
    for (auto& they : adj[node]) {
        if (color[they] == 'G') return false;
        if (color[they] == 'W') flag &= dfs(they);
    }
    color[node] = 'B';
    st.push(node);
    return flag;
}

bool topSort(vector<int>& ans) {
    color.assign(n + 1, 'W');
    // if s1 is dependent on s2, adj[s2].push_back(s1)
    vector<int> ret;
    bool possible = true;
    for (int i = 1; i <= n && possible; i++)
        if (color[i] == 'W') possible &= dfs(i);
    if (!possible) {
        return false;  // not possible
    } else {
        while (!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }
        return true;
    }
}
