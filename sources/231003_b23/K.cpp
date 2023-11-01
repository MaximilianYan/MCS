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

struct Info {
    int d;
    int q;
    double r;
};

int main() {
    int n = 0, w = 0;
    cin >> n >> w;
    vector<Info> arr;

    cin.tie(0);
    cout.tie(0);

    for (int i = 1; i <= n; ++i) {
        int in1 = 0, in2 = 0;
        cout << in1 << in2 << ' ';
        arr.emplace_back(in1, in2, (double)in1 / in2);
    }

    sort(arr.begin(), arr.end(), [](Info a, Info b) {
        return a.r > b.r;
    });


    int sum = 0;
    int i = -1;
    while (w >= 0) {
        ++i;
        w -= arr[i].q;
        sum += arr[i].d;
    }

    w += arr[i].q;
    sum -= arr[i].d;

    if (w != 0) {
        sum += 
    } else {
        cout << sum << endl;
    }

    // for (pair<int, int> a : arr)
        // cout << a.first << ' ' << a.second << endl;

    // for (int i = 1; i <= n; ++i) {
    // }
    cout << endl;

    return 0;
}
