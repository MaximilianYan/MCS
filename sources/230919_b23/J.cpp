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

    vector<int> stuff(n / 2, 0);
    multiset<int> sarr1;
    multiset<int> sarr2;

    transform(stuff.begin(), stuff.end(), stuff.begin(), [&sarr1](const int a) {
        int in = 0;
        cin >> in;

        sarr1.insert(in);

        return in;
    });
    transform(stuff.begin(), stuff.end(), stuff.begin(), [&sarr2](const int a) {
        int in = 0;
        cin >> in;

        sarr2.insert(in);

        return in;
    });

    transform(sarr1.begin(), sarr1.end(), stuff.begin(), [](const int a) {
        cout << a << ' ';
        return a;
    });
    transform(sarr2.rbegin(), sarr2.rend(), stuff.begin(), [](const int a) {
        cout << a << ' ';
        return a;
    });
}
