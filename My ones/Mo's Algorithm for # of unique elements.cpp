#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
typedef long long ll;

// SPOJ Problem DQUERY

struct Query {
    int l, r, index, ans;
};
const int BLOCK_SIZE = 200;
const int MAX_VALUE = 1e6 + 10;
int n, q, ans;
int current_left = 0, current_right = -1;
vector<int> numbers;
vector<int> frequency(MAX_VALUE);
vector<Query> questions;
void add(int index) {
    if (index < 0 || index >= (int)numbers.size()) return;
    int element = numbers[index];
    frequency[element]++;
    if (frequency[element] == 1) {
        ans++;
    }
}
void remove(int index) {
    if (index < 0 || index >= (int)numbers.size()) return;
    int element = numbers[index];
    frequency[element]--;
    if (frequency[element] == 0) ans--;
}
void Mo(Query& that) {
    while (current_left > that.l) {
        current_left--;
        add(current_left);
    }
    while (current_right < that.r) {
        current_right++;
        add(current_right);
    }
    while (current_left < that.l) {
        remove(current_left);
        current_left++;
    }
    while (current_right > that.r) {
        remove(current_right);
        current_right--;
    }
    that.ans = ans;
}
void solve() {
    scanf("%d", &n);
    numbers.resize(n);
    for (int i = 0; i < n; i++) scanf("%d", &numbers[i]);
    scanf("%d", &q);
    questions.resize(q);
    for (int i = 0; i < q; i++) {
        scanf("%d%d", &questions[i].l, &questions[i].r);
        questions[i].l--;
        questions[i].r--;
        questions[i].index = i;
    }
    sort(questions.begin(), questions.end(),
         [&](const Query& p, const Query& q) {
             if (p.l / BLOCK_SIZE != q.l / BLOCK_SIZE)
                 return make_pair(p.l, p.r) < make_pair(q.l, q.r);
             return (p.l / BLOCK_SIZE & 1) ? (p.r < q.r) : (p.r > q.r);
         });
    for (int i = 0; i < q; i++) {
        Mo(questions[i]);
    }
    sort(questions.begin(), questions.end(),
         [&](const Query& p, const Query& q) { return p.index < q.index; });
    for (int i = 0; i < q; i++) {
        printf("%d\n", questions[i].ans);
    }
}