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
    vector<int> arr;

    for (int i = 0; i < n; ++i) {
        int in = 0;
        cin >> in;
        arr.emplace_back(in);
    }

    sort(arr.begin(), arr.end());

    if (arr.size() % 2) {
        cout << arr[n / 2] << endl;
    } else {
        cout << setprecision(6) << ((double)arr[n / 2] + arr[n / 2 - 1]) / 2 << endl;
    }

    return 0;
}
