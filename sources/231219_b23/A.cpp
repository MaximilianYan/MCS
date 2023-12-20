#include <iostream>
#include <random>
#include <functional>
#include <utility>
#include <string>
#include <stdint.h>

using namespace std;

uint32_t MOD = (1 << 13) - 1;
int64_t H = (1 << 11) - 1;

int main() {
    string t, s;
    cin >> t >> s;

    if (s.size() > t.size()) {
        cout << "none" << endl;
    }

    // int sSize = s.size();

    int64_t HpowS = 1;

    int64_t sHash = 0;
    int64_t tHash = 0;

    for (int i = 0; i < s.size(); ++i) {
        sHash = (sHash * H + s[i]) % MOD;
        tHash = (tHash * H + t[i]) % MOD;
        HpowS = (HpowS * H) % MOD;
    }

    bool found = false;

    for (int end = s.size() - 1; end < t.size(); ++end) {
        if (sHash == tHash) {
            bool good = true;
            for (int i = 0; i < s.size(); ++i)
                if (s[s.size() - 1 - i] != t[end - i]) good = false;
            if (good) cout << end - s.size() + 2 << endl, found = true;
        }

        if (end < t.size() - 1) {
            tHash = (tHash * H - t[end - s.size() + 1] * HpowS + t[end + 1]) % MOD;
            if (tHash < 0) tHash += MOD;
        }
    }

    if (!found) cout << "none" << endl;

    return 0;
}
