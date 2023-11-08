#include <iostream>
#include <stdint.h>

using namespace std;

uint32_t sgn(uint32_t x) {
    if (x > 0) return +1;
    if (x < 0) return -1;
    return 0;
}

bool solve() {
    uint32_t x, y;
    cin >> x >> y;

    // отсекать право, лево и добавлять слева нули

    if (y == 0) return true;

    while (!(y & 1)) y >>= 1;
    // теперь y кончается единицами

    int size = 0;
    // длина y от ..1 до 1.. (считая с 0)
    for (int i = 0; i < 32; ++i) {
        if (y & (1 << i)) size = i;
    }

    uint32_t mask = (1 << (size + 1)) - 1;
    if (size == 31) mask = ~0;

    for (int i = 0; i < 32; ++i) {
        if ((x & mask) == y) return true;
        x >>= 1;
    }

    return false;
}

int main() {
    int t = 0;
    cin >> t;

    while (t--) {
        if (solve())
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }

    return 0;
}
