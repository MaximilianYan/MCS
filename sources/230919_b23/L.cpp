/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230919_b23 библиотека C++
 * @date 2023-10-04
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <set>

using namespace std;

int main() {
    int n = 0;
    cin >> n;

    vector<int> stuff(n, 0);
    multiset<int> sarr;

    transform(stuff.begin(), stuff.end(), stuff.begin(), [&sarr](const int a) {
        int in = 0;
        cin >> in;

        sarr.insert(in);

        return in;
    });

    int ans = 0;

    transform(sarr.begin(), sarr.end(), stuff.begin(), [&ans](const int a) {
        if (ans == a) ++ans;
        return a;
    });

    cout << ans << endl;
}
