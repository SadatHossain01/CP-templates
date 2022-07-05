#include <bits/stdc++.h>
using namespace std;

// Longest Prefix Suffix (KMP)
vector<int> getLPS(const string& pattern) {
    // lps[i] is the length of the longest proper prefix that is also a suffix
    const int n = pattern.size();
    vector<int> lps(n, 0);
    for (int i = 1; i < n; i++) {
        if (pattern[i] == pattern[lps[i - 1]])
            lps[i] = lps[i - 1] + 1;
        else {
            int k = lps[i - 1];
            while (k > 0 && pattern[i] != pattern[k]) k = lps[k - 1];
            if (pattern[i] == pattern[k]) k++;
            lps[i] = k;
        }
    }
    return lps;
}
int KMPSearch(const string& text, const string& pattern,
              const vector<int>& lps) {
    // returns number of matches
    const int m = pattern.size();
    const int n = text.size();
    // lps array for pattern
    int i = 0, j = 0, match = 0;
    while (i < n) {
        if (pattern[j] == text[i]) i++, j++;
        if (j == m) {
            // match found at index i - j
            match++;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return match;
}

vector<int> z_function(const string& s) {
    // z[i] is the length of the longest substring from i-th position
    // that is also a prefix of s
    const int n = s.size();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

// Aho-Corasick Algorithm
// KMP or Z-function works for single pattern
// where as Aho-Corasick works for multiple patterns in linear time