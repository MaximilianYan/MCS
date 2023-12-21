#include <iostream>
#include <random>
#include <functional>
#include <utility>
#include <string>
#include <sstream>
#include <stdint.h>

using namespace std;

template<int64_t H, const uint32_t MOD>
class PolHash;

template<int64_t H, const uint32_t MOD>
bool operator==(const PolHash<H, MOD>& lo, const PolHash<H, MOD>& ro);

template<int64_t H, const uint32_t MOD>
class PolHash {
public:
    PolHash();
    PolHash(int nextPow);

    void operator+=(int64_t ro);
    void next(int64_t old, int64_t young);

    friend bool operator== <>(const PolHash& lo, const PolHash& ro);

private:
    // const int HNextPow;
    int HNextPow;

    int64_t sum;
};

using PolHash_u1 = PolHash<(1 << 11) - 1, (1 << 15) - 1>;
using PolHash_u2 = PolHash<(1 << 11) - 2, (1 << 15) - 1>;
using PolHash_u3 = PolHash<(1 << 11) - 5, (1 << 15) - 1>;
// using PolHash_u2 = PolHash<821, 999999937>;

class MultiHash {
public:
    MultiHash();
    MultiHash(int nextPow);

    void operator+=(int64_t ro);
    void next(int64_t old, int64_t young);

    friend bool operator==(const MultiHash& lo, const MultiHash& ro);

private:
    PolHash_u1 h1;
    PolHash_u2 h2;
    PolHash_u3 h3;
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

template<int64_t H, const uint32_t MOD>
PolHash<H, MOD>::PolHash() : HNextPow(0), sum(0) {}

template<int64_t H, const uint32_t MOD>
PolHash<H, MOD>::PolHash(int nextPow) : sum(0) {
    HNextPow = 1;
    for (int i = 0; i < nextPow; ++i) {
        HNextPow *= H;
        HNextPow %= MOD;
    }
}

template<int64_t H, const uint32_t MOD>
void PolHash<H, MOD>::operator+=(int64_t ro) {
    ro %= MOD;
    sum *= H;
    sum += ro;
    sum %= MOD;
}

template<int64_t H, const uint32_t MOD>
void PolHash<H, MOD>::next(int64_t old, int64_t young) {
    sum = sum * H - old * HNextPow + young;
    sum %= MOD;
    if (sum < 0) sum += MOD;
}

template<int64_t H, const uint32_t MOD>
bool operator==(const PolHash<H, MOD>& lo, const PolHash<H, MOD>& ro) {
    return lo.sum == ro.sum;
}

MultiHash::MultiHash() : h1(), h2(), h3() {}
MultiHash::MultiHash(int nextPow) : h1(nextPow), h2(nextPow), h3(nextPow) {}

void MultiHash::operator+=(int64_t ro) {
    h1 += ro;
    h2 += ro;
    h3 += ro;
}

void MultiHash::next(int64_t old, int64_t young) {
    h1.next(old, young);
    h2.next(old, young);
    h3.next(old, young);
}

bool operator==(const MultiHash& lo, const MultiHash& ro) {
    return
        lo.h1 == ro.h1 &&
        lo.h2 == ro.h2 &&
        lo.h3 == ro.h3;
}
