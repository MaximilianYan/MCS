#include <iostream>
#include <stdint.h>

using namespace std;

uint32_t reverse(uint32_t n) {
    uint32_t nRevers = 0;

    nRevers = n & 1;
    for (int i = 1; i < 32; ++i) {
        nRevers <<= 1;
        n >>= 1;
        nRevers |= (n & 1);
    }

    return nRevers;
}

int main() {
    uint32_t n = 0;
    cin >> n;

    uint32_t nRevers = reverse(n);

    uint32_t rightRem[33] = {}; // ____(n) 
    uint32_t leftRem[33] = {};  // ____(n)

    rightRem[0] = 0;
    rightRem[32] = n;

    leftRem[0] = nRevers;
    leftRem[32] = 0;

    for (int i = 0; i < 32; ++i) {
        rightRem[i] = n & ((1 << i) - 1);
        leftRem[32 - i] = nRevers & ((1 << i) - 1);
    }

    uint32_t minSum = 0;
    for (int i = 0; i <= 32; ++i) {
        uint32_t sum = rightRem[i] + leftRem[i];
        sum += leftRem[i] > 0;

        if (sum < minSum || i == 0) minSum = sum;
    }

    cout << minSum << endl;

    return 0;
}
