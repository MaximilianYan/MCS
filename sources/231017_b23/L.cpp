#include <iostream>
#include <stdint.h>

using namespace std;

typedef uint64_t intType;
const intType BITN = 40;

void printB(intType n, bool endline = true) {
    for (int i = BITN; --i >= 0;) {
        cout << (int)(bool)(n & ((intType)1 << i));

        if (!(i % 8)) cout << ' ';
    }
    if (endline)
        cout << endl;
}

void printH(intType n, bool endline = true) {
    for (int i = (BITN >> 2); --i >= 0;) {
        cout << uppercase << hex << ((n >> ((intType)i << 2)) & ((1 << 4) - 1));

        if (!(i % 2)) cout << ' ';
    }
    if (endline)
        cout << endl;
}

int main() {
    long long int p = 0, q = 0;
    long double value[2] = {};

    cin >> p >> q;
    value[0] = (long double)p / q;

    intType n1 = *(intType*)(value);
    n1 &= ((intType)1 << 40) - 1;

    intType n2 = *(intType*)((uint8_t*)(value) + 5);

    printB(n2, false);
    printB(n1);
    
    printH(n2, false);
    printH(n1);

    return 0;
}
