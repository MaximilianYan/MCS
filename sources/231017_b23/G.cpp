#include <iostream>
#include <stdint.h>

using namespace std;

void printH(uint16_t n);
void printB(uint16_t n) {
    for (int i = 16; --i >= 0;) {
        cout << (int)(bool)(n & (1 << i));

        if (!(i % 8)) cout << ' ';
    }
    cout << endl;
}

void printH(uint16_t n) {
    for (int i = 4; --i >= 0;) {
        cout << uppercase << hex << ((n >> (i << 2)) & ((1 << 4) - 1));

        if (!(i % 2)) cout << ' ';
    }
    cout << endl;
}

int main() {
    uint16_t n = 0;
    cin >> *(int16_t*)(&n);

    printB(n);
    printH(n);

    return 0;
}
