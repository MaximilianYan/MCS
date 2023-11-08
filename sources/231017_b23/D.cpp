#include <iostream>
#include <stdint.h>

using namespace std;

int main() {
    int n = 0;
    cin >> n;

    uint32_t ps[12] = {};
    for (int i = 0; i < n; ++i) {
        cin >> ps[i];
    }

    uint32_t mmask = (1 << 30) - 1;
    int set = 0;

    uint32_t max = 0;

    for (set = 1; set < (1 << n); ++set) {
        uint32_t res = 1;
        for (int i = 0; i < n; ++i) {
            if (!(set & (1 << i))) continue;
            res *= ps[i];
            res &= mmask;
        }

        if (res > max) max = res;
    }

    cout << max << endl;

    return 0;
}
