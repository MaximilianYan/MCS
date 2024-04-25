#include <iostream>
#include <random>
#include <functional>
#include <utility>
#include <string>
#include <sstream>
#include <stdint.h>

using namespace std;

int main() {
    string s;
    int k = 0;
    cin >> s >> k;

    vector<int64_t> prefixf(s.size(), 0);
    prefixf[0] = 0;
    for (int i = 1; i < s.size(); ++i) {
        int k = prefixf[i - 1];

        while (k > 0 && s[i] != s[k])
            k = prefixf[k - 1];

        if (s[i] == s[k])
            k += 1;
        prefixf[i] = k;
    }

    vector<int64_t> zetf(s.size(), 0);
    zetf[0] = 0;
    int64_t lo = 0, hi = 0;
    for (int i = 1; i < s.size(); ++i) {
        if (i < hi)
            zetf[i] = min(zetf[i - lo], hi - i);

        while (i + zetf[i] < s.size() && s[zetf[i]] == s[i + zetf[i]])
            zetf[i] += 1;

        if (hi < i + zetf[i]) {
            lo = i;
            hi = i + zetf[i];
        }
    }

    // for (int i = 0; i < s.size(); ++i) {
    //     cout << zetf[i];
    // }

    

    // cin.tie(0);
    // cout.tie(0);
    // // sync_with_stdio(0);

    return 0;
}