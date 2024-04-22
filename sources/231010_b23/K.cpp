#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int n = 0;
    cin >> n;

    for (int i = 2, limit = sqrt(n); i <= limit; ++i) {
        if (!(n % i)) return cout << "NO" << endl, 0;
    }
    cout << "YES" << endl;

}
