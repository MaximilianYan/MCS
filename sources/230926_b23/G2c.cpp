/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230926_b23 теория игр
 * @date 2023-10-12
 */

#include <iostream>
#include <vector>

using namespace std;

int mex(const vector<bool>& grand) {
    for (int mex = 0; mex < grand.size(); ++mex)
        if (grand[mex]) return mex;

    return -1;
}

int gxor(const vector<vector<int>>& space, const vector<int>& pos) {
    int res = 0;
    for (int i = 0; i < space.size(); ++i) {
        if (space[i].size() != pos[i] + 1) {
            cout << "ERRRROR 23LINE " << space[i].size() << " / " << pos[i] + 1 << endl;
        }
        res ^= space[i][pos[i]];
    }
    return res;
}

int main() {
    int n = 0;
    cin >> n;

    vector<vector<int>> space;
    vector<int> pos(n, 0);
    for (int i = 0; i < n; ++i) {
        int a = 0;
        cin >> a;
        space.emplace_back(a + 1, 0);

        pos[i] = a;
    }

    // vector<int> possible({ 2, 4, 6 });

    for (int iN = 0; iN < n; ++iN) {
        int a = space[iN].size() - 1;
        for (int iC = 0; iC <= a; ++iC) {

            vector<bool> grand(a, true);
            // for (int transform : possible)
                // if (i - transform >= 0)
                    // grand[grandNums[i - transform]] = false;
            // grandNums[i] = mex(grand);

            if (iC > 0) space[iN][iC] = iC;
        }
    }

    if (gxor(space, pos))
        cout << "First" << endl;
    else
        cout << "Second" << endl;

    return 0;

    /*
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

    return 0;*/
}
