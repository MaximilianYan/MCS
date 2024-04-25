#include <iostream>
#include <random>
#include <functional>
#include <utility>
#include <string>
#include <sstream>
#include <stdint.h>

using namespace std;

int64_t add(int64_t sum, int64_t ro, int64_t H, uint32_t MOD) {
    ro %= MOD;
    sum *= H;
    sum %= MOD;
    sum += ro;
    sum %= MOD;
    return sum;
}

bool compare(vector<int64_t>& sHash, vector<int64_t>& hPow, int a, int b, int c, int d, int64_t H, uint32_t MOD) {
    int l = b - a + 1;
    if (d - c + 1 != l) return 0;

    int64_t delta1 = sHash[a - 1];
    int64_t delta2 = sHash[c - 1];
    delta1 *= hPow[l];
    delta1 %= MOD;
    delta2 *= hPow[l];
    delta2 %= MOD;

    delta1 = sHash[b] - delta1;
    delta1 %= MOD;
    delta1 += MOD;
    delta1 %= MOD;

    delta2 = sHash[d] - delta2;
    delta2 %= MOD;
    delta2 += MOD;
    delta2 %= MOD;

    return delta1 == delta2;
}

int main() {
    string s;
    cin >> s;
    int m;
    cin >> m;


    const int NNN = 3;
    const int64_t H[NNN] = {
        (1 << 11) - 1,
        (1 << 11) - 2,
        (1 << 11) - 5
    };
    const int64_t MOD[NNN] = {
        (1 << 17) - 1,
        (1 << 15) - 1,
        (1 << 15) - 1
    };

    vector<int64_t> sHash[NNN];
    vector<int64_t> hPow[NNN];

    for (int h = 0; h < NNN; ++h) {
        sHash[h] = vector<int64_t>(s.size() + 1, 0);
        hPow[h] = vector<int64_t>(s.size() + 1, 0);
        hPow[h][0] = 1;
    }

    for (int h = 0; h < NNN; ++h)
        for (int i = 0; i < s.size(); ++i) {
            sHash[h][i + 1] = sHash[h][i];
            sHash[h][i + 1] = add(sHash[h][i + 1], s[i], H[h], MOD[h]);
            hPow[h][i + 1] = hPow[h][i];
            hPow[h][i + 1] = add(hPow[h][i + 1], 0, H[h], MOD[h]);
        }

    while (m--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        bool ans = true;
        for (int h = 0; h < NNN; ++h)
            ans &= compare(sHash[h], hPow[h], a, b, c, d, H[h], MOD[h]);

        if (ans)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    // string t, s;
    // cin >> t >> s;

    // cin.tie(0);
    // cout.tie(0);
    // // sync_with_stdio(0);

    // stringstream ans = countIncs(t, s);

    // cout << (ans.str().length() ? ans.str() : "none") << endl;

    return 0;
}