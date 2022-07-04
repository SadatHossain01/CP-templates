#include <bits/stdc++.h>
using namespace std;

struct Trie {
    const int MX = 1e5 + 5;
    int root, n_node;
    vector<vector<int>> node;
    vector<bool> isWord;
    Trie() {
        root = 0, n_node = 0;
        // assuming only small letters
        node.assign(MX, vector<int>(26, 0));
        isWord.assign(MX, false);
        //-1 means no edge for ('a' + i)th character
        fill(node[root].begin(), node[root].end(), -1);
    }
    void insert(const string& s) {
        const int len = s.size();
        int now = root;
        for (int i = 0; i < len; i++) {
            if (node[now][s[i] - 'a'] == -1) {
                node[now][s[i] - 'a'] = ++n_node;
                fill(node[n_node].begin(), node[n_node].end(), -1);
            }
            now = node[now][s[i] - 'a'];
        }
        isWord[now] = true;
    }
};