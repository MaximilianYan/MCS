/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230926_b23 сортировки
 * @date 2023-10-18
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



int main() {
    int n = 0;
    cin >> n;
    vector<int> arr;

    while (n--) {
        int in = 0;
        cin >> in;
        arr.push_back(in);
    }

    sort(arr.begin(), arr.end());

    for (int a : arr)
        cout << a << ' ';

    cout << endl;
    return 0;
}
