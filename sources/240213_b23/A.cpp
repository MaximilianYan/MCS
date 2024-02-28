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

    MRand(int seed = 0) : s(0) { init(seed); }
private:
    const unsigned a = 1664525, c = 1013904223;
    unsigned s;
};

int main() {
    MRand mRand(239);

    int n = 0;
    cin >> n;

    while (true) {
        int pos = mRand.random(2 * n) + 1;
        cout << pos << endl;

        char in = 0;
        cin >> in;

        if (in == 'a') return 0;
    }

    return 0;
}
