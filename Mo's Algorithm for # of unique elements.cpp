#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

void __print(int x)
{
    cerr << x;
}
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char* x) { cerr << '\"' << x << '\"'; }
void __print(const string& x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template <typename T, typename V>
void __print(const pair<T, V>& x)
{
    cerr << '{';
    __print(x.first);
    cerr << ',';
    __print(x.second);
    cerr << '}';
}
template <typename T>
void __print(const T& x)
{
    int f = 0;
    cerr << '{';
    for (auto& i : x)
        cerr << (f++ ? "," : ""), __print(i);
    cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v)
{
    __print(t);
    if (sizeof...(v))
        cerr << ", ";
    _print(v...);
}
#ifndef ONLINE_JUDGE
#define debug(x...)               \
    cerr << "[" << #x << "] = ["; \
    _print(x)
#else
#define debug(x...)
#endif

const int mx = 2000100;
const int sz = 3e4 + 20;
const int BLOCK = 600;
int ans;
int LEFT = 0, RIGHT = -1;
array<int, mx>freq;
array<int, sz> vec;
struct query {
    int l, r, idx, ans;
};
bool comp1(const query& q1, const query& q2) {
    if (q1.l / BLOCK != q2.l / BLOCK) return q1.l < q2.l;
    return q1.r < q2.r;
}
bool comp2(const query& q1, const query& q2) {
    return q1.idx < q2.idx;
}
void add(int idx) {
    if (idx < 0 || idx >= vec.size()) return;
    freq[vec[idx]]++;
    if (freq[vec[idx]] == 1) ans++;
}
void remove(int idx) {
    if (idx < 0 || idx >= vec.size()) return;
    freq[vec[idx]]--;
    if (freq[vec[idx]] == 0) ans--;
}
void process(query& q) {
    while (LEFT > q.l) {
        LEFT--;
        add(LEFT);
    }
    while (RIGHT < q.r) {
        RIGHT++;
        add(RIGHT);
    }
    while (LEFT < q.l) {
        remove(LEFT);
        LEFT++;
    }
    while (RIGHT > q.r) {
        remove(RIGHT);
        RIGHT--;
    }
    q.ans = ans;
}
void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> vec[i];
    int q;
    cin >> q;
    vector<query>Q(q);
    for (int i = 0; i < q; i++) {
        cin >> Q[i].l >> Q[i].r;
        Q[i].idx = i;
        Q[i].l--;
        Q[i].r--;
    }
    sort(Q.begin(), Q.end(), comp1);
    for (int i = 0; i < q; i++) {
        process(Q[i]);
    }
    sort(Q.begin(), Q.end(), comp2);
    for (int i = 0; i < q; i++) {
        cout << Q[i].ans << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
}