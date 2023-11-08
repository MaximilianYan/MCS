#include <iostream>
#include <stdint.h>

using namespace std;

typedef uint64_t intType;
const intType BITN = 64;

void printB(intType n) {
    for (int i = BITN; --i >= 0;) {
        cout << (int)(bool)(n & ((intType)1 << i));

        if (!(i % 8)) cout << ' ';
    }
    cout << endl;
}

void printH(intType n) {
    for (int i = (BITN >> 2); --i >= 0;) {
        cout << uppercase << hex << ((n >> ((intType)i << 2)) & ((1 << 4) - 1));

        if (!(i % 2)) cout << ' ';
    }
    cout << endl;
}

int main() {
    long long int p = 0, q = 0;
    double value = 0;

    cin >> p >> q;
    value = (double)p / q;

    intType n = *(intType*)(&value);

    printB(n);
    printH(n);

    return 0;
}
