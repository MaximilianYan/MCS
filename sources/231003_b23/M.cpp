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
    long long int n = 0, x = 0;
    cin >> n >> x;
    vector<long long int> arr;

    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < n; ++i) {
        int in = 0;
        cin >> in;
        arr.emplace_back(in);
    }

    int min = 0;
    int max = n - 1;

    while (arr[min] + arr[max] != x && min <= max) {
        while (arr[min] + arr[max] > x)
            --max;
        while (arr[min] + arr[max] < x)
            ++min;
    }

    if (arr[min] + arr[max] != x)
        cout << "NO" << endl;
    else
        cout << "YES" << endl;

    // sort(arr.begin(), arr.end(), [](Info a, Info b) {
    //     return a.r > b.r;
    // });

    return 0;
}
