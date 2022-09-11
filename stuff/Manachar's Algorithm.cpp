#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

int main() {
    string s;
    cin >> s;
    const int n = s.size();
    vector<int> d1(n, 0);
    // radius of maximum odd length palindrome centered at i
    // here d1[i] = the palindrome has d1[i] - 1 right characters from i
    // e.g. for aba, d1[1] = 2;
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    vector<int> d2(n, 0);
    // radius of maximum even length palindrome centered at i
    // here d2[i] = the palindrome has d2[i] - 1 right characters from i
    // e.g. for abba, d2[2] = 2;
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
    for (int i = 0; i < n; i++) cout << d1[i] << ' ';
    cout << endl;
    for (int i = 0; i < n; i++) cout << d2[i] << ' ';
    cout << endl;
    // number of palindromes
    long long ans = 0;
    for (int i = 0; i < n; i++) ans += d1[i] + d2[i];
    cout << ans << endl;
    return 0;
}