/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230919_b23 библиотека C++
 * @date 2023-10-04
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    long long int n = 0;
    cin >> n;

    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }

    int count = (9.0 / log10(n));

    vector<long long int> ans(count + 1, 1);
    long long int s = 1;
    generate_n(ans.begin() + 1, count, [&s, n]() {
        s *= n;
        return s;
    });

    transform(ans.begin(), ans.end(), ans.begin(), [](const long long int a) {
        cout << a << ' ';
        return a;
    });
}
