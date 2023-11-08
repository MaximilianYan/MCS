#include <iostream>
#include <stdint.h>

using namespace std;

void printH(uint32_t n);
void printB(uint32_t n) {
    for (int i = 32; --i >= 0;) {
        cout << (int)(bool)(n & (1 << i));

        if (!(i % 8)) cout << ' ';
    }
    cout << endl;
}

void printH(uint32_t n) {
    for (int i = 8; --i >= 0;) {
        cout << uppercase << hex << ((n >> (i << 2)) & ((1 << 4) - 1));

        if (!(i % 2)) cout << ' ';
    }
    cout << endl;
}

int main() {
    uint32_t n = 0;
    cin >> *(int32_t*)(&n);

    printB(n);
    printH(n);

    return 0;
}
