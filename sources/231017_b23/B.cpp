#include <iostream>
#include <stdint.h>

using namespace std;

int64_t sgn(int64_t x) {
    if (x > 0) return +1;
    if (x < 0) return -1;
    return 0;
}

int main() {
    int64_t a = 0, b = 0;

    cin >> a >> b;

    if (!b) {
        cout << "Na nol' delit' nel'zya!!!" << endl;
        return 0;
    }

    int64_t q = a / b;

    if (a < 0 && (a % b)) {
        q -= sgn(b);
    }

    cout << q << endl;

    return 0;
}
