#include <iostream>
#include <cmath>

using namespace std;

bool ans(long long int n) {

    if (n == 1) return 0;

    for (long long int i = 2, limit = sqrt(n); i <= limit; ++i) {
        if (!(n % i)) return 0;
    }
    return 1;
}

int main() {
    long long int n = 0;
    cin >> n;

    if (ans(n)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

}
