#include <iostream>
#include <cmath>

using namespace std;

int main() {
    long long n = 0;
    cin >> n;
    long long sum = 0;

    for (int i = 1; i <= n && i < 1e8; ++i) {
        sum += n / i;
    }
    if (n >= 1e8) {
        sum += n * log((double)n / (double)1e8) + (0.5/n - 0.5/1e8);
    }

    cout << sum << endl;
}
