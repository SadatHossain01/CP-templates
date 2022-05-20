#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

void split(string& s) {
    int idx = 0;
    while (idx < s.size() && s[idx] == ' ') idx++;
    for (int j = 0; j < idx; j++) {
        s.erase(s.begin());
    }
    idx = s.size() - 1;
    while (idx >= 0 && s[idx] == ' ') idx--;
    for (int i = s.size() - 1; i > idx; i--) s.erase(s.begin() + i);
}

int main(int argc, char* argv[]) {
    char delimiter;
    if (argc != 4) {
        // printf("You have to provide 2 file names and a delimiter name!");
        delimiter = '\n';
    }
    if (strcmp(argv[3], "space") == 0)
        delimiter = ' ';
    else
        delimiter = '\n';
    FILE* fp1 = fopen(argv[1], "r");
    FILE* fp2 = fopen(argv[2], "r");
    string s1, s2;
    bool isMessageShown = false;
    do {
        while (true) {
            if (feof(fp1)) break;
            char c1 = fgetc(fp1);
            if (c1 == delimiter) break;
            s1 += c1;
        }
        while (true) {
            if (feof(fp2)) break;
            char c2 = fgetc(fp2);
            if (c2 == delimiter) break;
            s2 += c2;
        }
        split(s1);
        split(s2);
        // if (!s1.empty() && !s2.empty()) cout << s1 << " " << s2 << endl;
        if (s1 != s2) {
            if (!isMessageShown) {
                cout << "Mismatch Noticed " << argv[1] << " " << argv[2]
                     << endl;
                isMessageShown = true;
            }
            cout << s1 << " " << s2 << endl;
        }
        s1 = "";
        s2 = "";
    } while (!feof(fp1) || !feof(fp2));
    if (!isMessageShown) {
        cout << "No Mismatch Found" << endl;
    }
    fclose(fp1);
    fclose(fp2);
}