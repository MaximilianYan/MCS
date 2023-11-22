#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <limits>
#include <list>
#include <sstream>
#include <string>

using namespace std;

int main() {
    long long int n = 0;

    cin >> n;

    vector<vector<long long int>> field(n, vector<long long int>(n, 0));

    for (long long int i = 0; i < n; ++i) {
        for (long long int j = 0; j <= i; ++j) {
            cin >> field[i][j];
        }
    }

    {
        for (long long int posN = 1; posN < n; ++posN) {

            field[posN][0] += field[posN - 1][0];

            for (long long int posK = 1; posK < posN; ++posK) {
                field[posN][posK] += max(field[posN - 1][posK], field[posN - 1][posK - 1]);
            }

            field[posN][posN] += field[posN - 1][posN - 1];
        }
    }

    long long int res = field[n - 1][0];
    for (long long int i = 1; i < n; ++i) {
        res = max(res, field[n - 1][i]);
    }

    cout << res << endl;

    return 0;
}
