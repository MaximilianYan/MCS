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

    // void next() { s = s * a + c; }

    // int random(int k) {
    //     long long z = (1LL << 32) / k * k;
    //     do next(); while (s >= z);
    //     return (s * 1LL * k) / z;
    // }

    unsigned random() {
        return s = s * a + c;
    }

    MRand(uint32_t a, uint32_t c, uint32_t seed = 0) : a(a), c(c), s(0) { init(seed); }
private:
    uint32_t a, c;
    // const undigned m = 2^*32;
    uint32_t s;
};

int main() {

    uint32_t a = 0, c = 0, s = 0;
    cin >> a >> c >> s;
    MRand mRand(a, c, s);

    for (int i = 0; i < 10; ++i) {
        cout << mRand.random() << ' ';
    }

    return 0;
}
