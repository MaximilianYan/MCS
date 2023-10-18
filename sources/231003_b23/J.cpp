/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230926_b23 сортировки
 * @date 2023-10-18
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main() {
    int n = 0;
    cin >> n;
    // vector<pair<int, int>> arr;

    cin.tie(0);
    cout.tie(0);

    int in = 0;

    char str[n * 7];
    cin.getline(str, n * 7);

    for (int i = 1; i <= n; ++i) {
        cout << i << ' ';
        // arr.emplace_back(in1, in2);
    }

    // stable_sort(arr.begin(), arr.end(), [](pair<int, int> a, pair<int, int> b) {
        // return a.first < b.first;
    // });

    // for (pair<int, int> a : arr)
        // cout << a.first << ' ' << a.second << endl;

    // for (int i = 1; i <= n; ++i) {
    // }
    cout << endl;

    return 0;
}
