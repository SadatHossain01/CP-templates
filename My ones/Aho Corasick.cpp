#include <bits/stdc++.h>
using namespace std;

const int K = 26;
struct Vertex {
    vector<int> next, go;
    // leaf will store which index's string it is leaf of
    int leaf = -1, p = -1, link = -1;
    char pch;
    Vertex(int p = -1, char ch = '$') : p(p), pch(ch) {
        next.assign(K, 0);
        go.assign(K, 0);
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};
vector<Vertex> trie(1);
void add_string(string const& s, int index) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (trie[v].next[c] == -1) {
            trie[v].next[c] = trie.size();
            trie.emplace_back(v, ch);
        }
        v = trie[v].next[c];
    }
    trie[v].leaf = index;
}
int go(int v, char ch);
int get_link(int v) {
    if (trie[v].link == -1) {
        if (v == 0 || trie[v].p == 0)
            trie[v].link = 0;
        else
            trie[v].link = go(get_link(trie[v].p), trie[v].pch);
    }
    return trie[v].link;
}
int go(int v, char ch) {
    int c = ch - 'a';
    if (trie[v].go[c] == -1) {
        if (trie[v].next[c] != -1)
            trie[v].go[c] = trie[v].next[c];
        else
            trie[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
    }
    return trie[v].go[c];
}

vector<bool> patternCheck(const string& text, const vector<string>& patterns) {
    // assuming one string once
    // if one string multiple times, do some mapping
    // so that one string is considered once in the trie
    int cur = 0;
    queue<int> q;
    for (int i = 0; i < text.size(); i++) {
        cur = go(cur, text[i]);  // go to the next node from current
        q.push(cur);
    }
    vector<bool> visited(trie.size() + 2, false);
    vector<bool> ok(patterns.size() + 2, false);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        visited[now] = true;
        if (trie[now].leaf != -1) ok[trie[now].leaf] = true;
        if (trie[now].link != -1 && !visited[trie[now].link])
            q.push(trie[now].link);
    }
    // so strings for which ok is true are present in 'text' as substring
    return ok;
}