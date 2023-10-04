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
    multiset<int> arr;
    cin >> n;

    vector<int> stuff(n, 0);
    int first = 0;

    transform(stuff.begin(), stuff.end(), stuff.begin(), [&arr, &first](const int a) {
        int in = 0;
        cin >> in;

        arr.insert(in);

        if (!first) first = in;

        return in;
    });

    int counter = 1;
    transform(arr.begin(), arr.end(), stuff.begin(), [&first, &counter](const int a) {
        if (a == first) {
            first = 0;
            cout << counter << endl;
        }
        ++counter;

        return a;
    });
}
