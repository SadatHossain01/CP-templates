#include <bits/stdc++.h>
using namespace std;

// Longest Prefix Suffix
vector<int> getLPS(const string& s) {
    const int n = s.size();
    vector<int> lps(n, 0);
    for (int i = 1; i < n; i++) {
        if (s[i] == s[lps[i - 1]])
            lps[i] = lps[i - 1] + 1;
        else {
            int k = lps[i - 1];
            while (k > 0 && s[i] != s[k]) k = lps[k - 1];
            if (s[i] == s[k]) k++;
            lps[i] = k;
        }
    }
    return lps;
}