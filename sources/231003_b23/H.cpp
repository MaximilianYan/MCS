/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230926_b23 сортировки
 * @date 2023-10-18
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n = 0;
    cin >> n;
    vector<pair<int, int>> arr;

    for (int i = 0; i < n; ++i) {
        int in1 = 0, in2 = 0;
        cin >> in1 >> in2;
        arr.emplace_back(in1, in2);
    }

    stable_sort(arr.begin(), arr.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.first < b.first;
    });

    for (pair<int, int> a : arr)
        cout << a.first << ' ' << a.second << endl;

    return 0;
}
