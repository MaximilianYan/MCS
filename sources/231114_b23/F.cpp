#include <iostream>
#include <cmath>

using namespace std;

int main() {
    long long n = 0;
    cin >> n;

    if (n <= 0) {
        cout << "0" << endl;
        return 0;
    }

    long long sum = 0;

    long long limit1 = sqrt(n);

    long long int delta = 0;
    for (int i = 1; true; ++i) {
        delta = n / i;
        if (delta <= limit1) break;
        sum += n / i;
    }
    for (int i = 1; i <= limit1; ++i) {
        sum += i * (n / i - n / (i + 1));
    }

    cout << sum << endl;
}
