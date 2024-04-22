#include <iostream>
#include <cmath>

using namespace std;

bool ans(int n) {

    if (n == 1) return 0;

    for (int i = 2, limit = sqrt(n); i <= limit; ++i) {
        if (!(n % i)) return 0;
    }
    return 1;
}

int main() {
    int n = 0;
    cin >> n;

    if (ans(n)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

}
