#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int mex(const vector<bool> grand) {
    for (int mex = 0; mex < grand.size(); ++mex)
        if (grand[mex]) return mex;

    return -1;
}

int mex(const set<int>& nums) {
    for (int mex = 0; mex < 300; ++mex)
        if (!nums.count(mex)) return mex;

    return -1;
}

int countFenceGrand(short n) {
    static int grandNums[300] = {};
    static bool isGrandNumsCalced[300] = { 0};

    if (isGrandNumsCalced[n]) return grandNums[n];

    int grandRes = 0;

    for (short downC = 1; downC <= 2 && downC <= n; ++downC) {
        for (short nn = 0; nn <= n - downC; ++nn) {
            grandRes ^= countFenceGrand(nn);
            grandRes ^= countFenceGrand(n - nn - downC);
        }
    }

    grandRes = grandRes == 0 ? 1 : 0;

    grandNums[n] = grandRes;
    isGrandNumsCalced[n] = true;

    cout << "g("<<n<<") = " << grandNums[n] << endl;
    return grandNums[n];
}

int main() {
    short n = 0;
    cin >> n;

    int grand = countFenceGrand(n);
    // int grand = countGrand(startFence, fenceMap);
    // cout << "g(" << n << ") = " << grand << endl;
    // int grand = 1;

    if (grand)
        cout << "First" << endl;
    else
        cout << "Second" << endl;

    return 0;
}
