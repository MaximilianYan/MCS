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
    long long int l = 0;
    long long int r = 0;
    long long int d = 0;
    cin >> l >> r >> d;

    long long int i = 0;

    int count = (r - l) / d + 1;

    vector<long long int> ans(count, 0);
    generate_n(ans.begin(), count, [&i, l, r, d]() -> long long int {
        if (!i) {
            i = l - l % d;
            if (i < l) i += d;
        } else {
            i += d;
        }

        if (i <= r) return i;
        return 0;
    });

    transform(ans.begin(), ans.end(), ans.begin(), [](const long long int a) {
        if (a) cout << a << ' ';
        return a;
    });

    //------------------------------------------

}
