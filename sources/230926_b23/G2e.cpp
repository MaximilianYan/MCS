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

    return grand.size();
}

int gxor(const vector<vector<int>>& space, const vector<int>& pos) {
    int res = 0;
    for (int i = 0; i < space.size(); ++i) {
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

    vector<int> possible({ 1, 2 });

    for (int iN = 0; iN < n; ++iN) {
        int a = space[iN].size() - 1;
        for (int iC = 0; iC <= a; ++iC) {

            vector<bool> grand(a, true);
            for (int transform : possible)
                if (iC - transform >= 0)
                    grand[space[iN][iC - transform]] = false;

            space[iN][iC] = mex(grand);
        }
    }


    if (gxor(space, pos))
        cout << "First" << endl;
    else
        cout << "Second" << endl;

    return 0;
    /*
    if (!gxor(space, pos)) return cout << "-1" << endl, 0;


    while (true) {
        /*for (int transform : possible)
            if (grandNums[counter - transform] == 0) {
                counter -= transform;
                cout << transform << endl;
                break;
            }
        *\/
        int ansN = 0;
        int ansC = 1;
        do {
            ansN = 0;
            do {
                vector<int> trans(pos);

                trans[ansN] -= ansC;
                if (trans[ansN] < 0) continue;

                if (!gxor(space, trans)) goto gotAnswer;

            } while (++ansN < n);
        } while (++ansC, true);
    gotAnswer:


        cout << ansN + 1 << " " << ansC << endl;
        pos[ansN] -= ansC;

        int inputN = 0;
        int inputC = 0;
        cin >> inputN;
        if (inputN == -1) return 0;

        cin >> inputC;
        pos[inputN - 1] -= inputC;
    }

    return 0;*/
}
