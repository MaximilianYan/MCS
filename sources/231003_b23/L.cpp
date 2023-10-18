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
    vector<int> arr(1001, 0);

    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < n; ++i) {
        int in = 0;
        cin >> in;
        arr[in]++;
    }

    // sort(arr.begin(), arr.end(), [](Info a, Info b) {
    //     return a.r > b.r;
    // });

    for (int i = 1; i <= 1000; ++i) {
        if (arr[i])
            for (int j = 0; j < arr[i]; ++j)
                cout << i << ' ';
    }

    cout << endl;

    return 0;
}
