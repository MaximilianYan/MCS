#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <vector>

using namespace std;

int main() {
    int n = 0;
    cin >> n;
    vector<uint64_t> fs(n + 1, 0);

    fs[0] = 0;
    fs[1] = 1;
    for (int i = 2; i <= n; ++i) {
        fs[i] = fs[i - 1] + fs[i - 2];
    }

    cout << fs[n] << endl;

    return 0;
}
