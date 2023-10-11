/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230926_b23 теория игр
 * @date 2023-09-27
 */

#include <iostream>
#include <vector>

using namespace std;

int mex(const vector<bool> grand) {
    for (int mex = 0; mex < grand.size(); ++mex)
        if (grand[mex]) return mex;

    return -1;
}

int main() {
    int n = 0;

    cin >> n;

    vector<int> grandNums(n + 1, 0);
    vector<int> possible({ 1, 2, 4 });

    for (int i = 0; i <= n; ++i) {

        vector<bool> grand(n + 1, true);
        for (int transform : possible)
            if (i - transform >= 0)
                grand[grandNums[i - transform]] = false;

        grandNums[i] = mex(grand);
    }

    if (!grandNums[n])
        return cout << "-1" << endl, 0;

    int counter = n;
    while (true) {
        for (int transform : possible)
            if (grandNums[counter - transform] == 0) {
                counter -= transform;
                cout << transform << endl;
                break;
            }

        int input = 0;
        cin >> input;
        if (input == -1) return 0;
        counter -= input;
    }

    return 0;
}
