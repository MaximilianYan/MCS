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
    vector<pair<int, int>> arrA, arrB;

    for (int i = 0; i < n; ++i) {
        int in = 0;
        cin >> in;
        arrA.emplace_back(i, in);
    }

    for (int i = 0; i < n; ++i) {
        int in = 0;
        cin >> in;
        arrB.emplace_back(i, in);
    }

    sort(arrB.begin(), arrB.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;
    });

    int time = -arrB[0].second;
    int deadline = arrA[arrB[0].first].second;
    for (pair<int, int> b : arrB) {
        time += b.second;
        deadline = min(deadline, time + arrA[b.first].second);
    }

    if (deadline < time)
        cout << -1 << endl;
    else {
        for (pair<int, int> b : arrB)
            cout << b.first + 1 << ' ';
    }

    cout << endl;

    return 0;
}
