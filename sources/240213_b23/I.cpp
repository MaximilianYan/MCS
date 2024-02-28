#include <iostream>
#include <random>
#include <functional>
#include <utility>
#include <string>
#include <sstream>
#include <stdint.h>

using namespace std;

class MRand {
public:
    void init(int seed) { s = seed; }

    void next() { s = s * a + c; }

    int random(int k) {
        long long z = (1LL << 32) / k * k;
        do next(); while (s >= z);
        return (s * 1LL * k) / z;
    }

    unsigned random() {
        next();
        return s;
    }

    MRand(uint32_t a = 1664525, uint32_t c = 1013904223, uint32_t seed = 0) : a(a), c(c), s(0) { init(seed); }
private:
    uint32_t a, c;
    // const undigned m = 2^*32;
    uint32_t s;
};

int ask(int x) {
    cout << "? " << x << endl;
    int in = -1;
    cin >> in;
    return in;
}

int main() {
    int n = 0;
    cin >> n;

    // [l, l+length]
    int l = 1;      //      l = 2k+1
    int length = n; // length = 2k+1

    // x < v : (2k-1)a(2k)a
    // x > v : (2k)a(2k+1)a

    while (length > 1) {
        int shift = (length >> 2) << 1;

        int xSh = ask(l + shift);
        int xShNext = ask(l + shift + 1);

        if (xSh == xShNext) {
            l += shift + 2;
            length -= shift + 2;
        } else {
            length = shift + 1;
        }
    }

    int ans = ask(l);
    cout << "! " << ans << endl;

    return 0;
}
