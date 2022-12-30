#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
typedef long long ll;
// Solves SPOJ Problem DQUERY
struct Query {
    int l, r, index, ans;
};
const int BLOCK_SIZE = 200;
const int MX = 1e6 + 10;
int n, q, n_unique;
int current_left = 0, current_right = -1;
vector<int> numbers, frequency(MX);
vector<Query> queries;
void add(int index) {
    if (index < 0 || index >= numbers.size()) return;
    int element = numbers[index];
    frequency[element]++;
    if (frequency[element] == 1) n_unique++;
}
void remove(int index) {
    if (index < 0 || index >= numbers.size()) return;
    int element = numbers[index];
    frequency[element]--;
    if (frequency[element] == 0) n_unique--;
}
void processQueries(Query& q) {
    while (current_left > q.l) {
        current_left--;
        add(current_left);
    }
    while (current_right < q.r) {
        current_right++;
        add(current_right);
    }
    while (current_left < q.l) {
        remove(current_left);
        current_left++;
    }
    while (current_right > q.r) {
        remove(current_right);
        current_right--;
    }
    q.ans = n_unique;
}
void solve() {
    cin >> n;
    numbers.resize(n);
    for (int i = 0; i < n; i++) cin >> numbers[i];
    cin >> q;
    queries.resize(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--;
        queries[i].r--;
        queries[i].index = i;
    }
    sort(queries.begin(), queries.end(), [&](const Query& p, const Query& q) {
        if (p.l / BLOCK_SIZE != q.l / BLOCK_SIZE)
            return make_pair(p.l, p.r) < make_pair(q.l, q.r);
        return ((p.l / BLOCK_SIZE) & 1) ? (p.r < q.r) : (p.r > q.r);
    });
    for (int i = 0; i < q; i++) processQueries(queries[i]);
    sort(queries.begin(), queries.end(),
         [&](const Query& p, const Query& q) { return p.index < q.index; });
    for (int i = 0; i < q; i++) cout << queries[i].ans << endl;
}