#include <iostream>
#include <random>
#include <functional>
#include <utility>
#include <string>
#include <sstream>
#include <stdint.h>

using namespace std;

class PolHash {
public:
    PolHash(int64_t H, uint32_t MOD);
    PolHash(int64_t H, uint32_t MOD, int nextPow);

    void operator+=(int64_t ro);
    void next(int64_t old, int64_t young);

    friend bool operator==(const PolHash& lo, const PolHash& ro);

private:
    const int64_t H;
    const uint32_t MOD;

    int HNextPow;

    int64_t sum;
};

class MultiHash {
public:
    MultiHash(int nextPow = 0);

    void operator+=(int64_t ro);
    void next(int64_t old, int64_t young);

    friend bool operator==(const MultiHash& lo, const MultiHash& ro);

private:
    vector<PolHash> hs;
};

stringstream countIncs(string t, string s) {
    stringstream ans;

    if (s.size() > t.size()) {
        return ans;
    }

    MultiHash sHash;
    MultiHash tHash(s.size());

    int64_t HpowS = 1;

    for (int i = 0; i < s.size(); ++i) {
        sHash += s[i];
        tHash += t[i];
    }

    for (int end = s.size() - 1; end < t.size(); ++end) {
        if (sHash == tHash) {
            bool good = true;
            // for (int i = 0; i < s.size(); ++i)
            //     if (s[s.size() - 1 - i] != t[end - i]) good = false;
            if (good) ans << end - s.size() + 2 << " ";
        }

        if (end == t.size() - 1) continue;

        tHash.next(t[end - s.size() + 1], t[end + 1]);
    }

    return ans;
}

int main() {
    string t, s;
    cin >> t >> s;

    cin.tie(0);
    cout.tie(0);
    // sync_with_stdio(0);

    stringstream ans = countIncs(t, s);

    cout << (ans.str().length() ? ans.str() : "none") << endl;

    return 0;
}

PolHash::PolHash(int64_t H, uint32_t MOD) : H(H), MOD(MOD), HNextPow(0), sum(0) {}

PolHash::PolHash(int64_t H, uint32_t MOD, int nextPow) : H(H), MOD(MOD), sum(0) {
    HNextPow = 1;
    for (int i = 0; i < nextPow; ++i) {
        HNextPow *= H;
        HNextPow %= MOD;
    }
}

void PolHash::operator+=(int64_t ro) {
    ro %= MOD;
    sum *= H;
    sum += ro;
    sum %= MOD;
}

void PolHash::next(int64_t old, int64_t young) {
    sum = sum * H - old * HNextPow + young;
    sum %= MOD;
    if (sum < 0) sum += MOD;
}

bool operator==(const PolHash& lo, const PolHash& ro) {
    return lo.sum == ro.sum;
}

MultiHash::MultiHash(int nextPow) {
    hs.emplace_back((1 << 11) - 1, (1 << 17) - 1, nextPow);
    // hs.emplace_back((1 << 11) - 2, (1 << 15) - 1, nextPow);
    // hs.emplace_back((1 << 11) - 5, (1 << 15) - 1, nextPow);
    // hs.emplace_back((1 << 11) - 5, (1 << 17) - 3, nextPow);
    // hs.emplace_back((1 << 11) - 5, (1 << 17) - 3, nextPow);
    // hs.emplace_back((1 << 11) - 5, (1 << 17) - 3, nextPow);
}

void MultiHash::operator+=(int64_t ro) {
    for (auto& h : hs)
        h += ro;
}

void MultiHash::next(int64_t old, int64_t young) {
    for (auto& h : hs)
        h.next(old, young);
}

bool operator==(const MultiHash& lo, const MultiHash& ro) {
    bool ans = true;
    for (int i = 0; i < lo.hs.size(); ++i)
        ans &= (lo.hs[i] == ro.hs[i]);
    return ans;
}
