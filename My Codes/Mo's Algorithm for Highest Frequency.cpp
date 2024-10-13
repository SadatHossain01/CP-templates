#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
typedef long long ll;
struct Query {
    int l, r, index, ans;
};
const int BLOCK_SIZE = 350;
const int MX = 1e5 + 10;
int n, q, max_freq = 1;
int current_left = 0, current_right = -1;
vector<int> numbers, frequency(MX), freq_frequency;
vector<Query> queries;
void add(int index) {
    if (index < 0 || index >= numbers.size()) return;
    int element = numbers[index];
    int previous_frequency = frequency[element];
    frequency[element]++;
    int current_frequency = frequency[element];
    if (previous_frequency > 0) freq_frequency[previous_frequency]--;
    freq_frequency[current_frequency]++;
    if (freq_frequency[current_frequency] == 1 && current_frequency > max_freq)
        max_freq = current_frequency;
}
void remove(int index) {
    if (index < 0 || index >= numbers.size()) return;
    int element = numbers[index];
    int previous_frequency = frequency[element];
    frequency[element]--;
    int current_frequency = frequency[element];
    if (current_frequency > 0) freq_frequency[current_frequency]++;
    freq_frequency[previous_frequency]--;
    if (max_freq == previous_frequency &&
        freq_frequency[previous_frequency] == 0)
        max_freq = current_frequency;
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
    q.ans = max_freq;
}
void solve() {
    cin >> n >> q;
    numbers.resize(n);
    freq_frequency.assign(n + 2, 0);
    for (int i = 0; i < n; i++) cin >> numbers[i];
    queries.resize(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
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
    for (int i = 0; i < q; i++) {
        cout << queries[i].ans << endl;
    }
}