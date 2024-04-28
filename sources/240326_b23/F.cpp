#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <iomanip>
#include <algorithm>

using namespace std;


int main() {
    int n = 0;
    cin >> n;

    vector<vector<int>> field(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            char in;
            cin >> in;
            field[i][j] = in - '0';
        }

    int sum = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            if (!(i % 2) && !(j % 2))
                sum += field[i][j];
        }

    cout << sum << endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(i % 2) && !(j % 2))
                cout << field[i][j];
            else
                cout << "0";
        }
        cout << endl;
    }



    return 0;
}

// ---------------------------------------------                    ---------------------------------------------
// ----------------------------------------------                  ----------------------------------------------
// -----------------------------------------------                -----------------------------------------------
// ------------------------------------------------              ------------------------------------------------
// -------------------------------------------------            -------------------------------------------------
// --------------------------------------------------          --------------------------------------------------
// ---------------------------------------------------        ---------------------------------------------------
// ----------------------------------------------------      ----------------------------------------------------
// -----------------------------------------------------    -----------------------------------------------------
// ------------------------------------------------------  ------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

