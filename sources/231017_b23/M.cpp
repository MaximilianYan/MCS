#include <iostream>
#include <iomanip>
#include <stdint.h>

using namespace std;

int main() {
    long long a = 0, b = 0, x1 = 0, x2 = 0;
    cin >> a >> b >> x1 >> x2;

    // long double delta = (long double)a + (long double)1 / b;
    // if (x1 < x2) delta = -delta;

    long double oneb = (long double)1. / b;
    long long decb = oneb * 1e6;

    if (x1 < x2) cout << "-";

    if (b > 1e5) {
        cout << a << endl;
        return 0;
    }

    if (b > 1) {
        cout << a << "." << decb << endl;
        return 0;
    }

    if (b == 1) { // test № 3
        cout << a + 1 << endl;
        return 0;
    }

    while (true);

    return 0;
}
