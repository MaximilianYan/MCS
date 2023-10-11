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
    vector<int> possible({ 1, 2 });

    for (int i = 0; i <= n; ++i) {

        vector<bool> grand(n + 1, true);
        for (int transform : possible)
            if (i - transform >= 0)
                grand[grandNums[i - transform]] = false;

        grandNums[i] = mex(grand);
    }

    if (grandNums[n])
        cout << "First" << endl;
    else
        cout << "Second" << endl;

    return 0;
}
