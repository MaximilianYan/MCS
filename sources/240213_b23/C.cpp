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

bool doJump(uint32_t target) {
    cout << target << endl;
    string in;
    cin >> in;
    return (in == "yes");
}

uint32_t filter(uint32_t n) {
    if (n <= 1) n += 2;
    return n;
}

int main() {
    MRand mRand;

    while (true) {
        if (doJump(1)) return 0;

        while (!doJump(filter(mRand.random())));
    }

    return 0;
}
