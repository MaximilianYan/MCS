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
    string s1, s2;

    cin >> s1 >> s2;

    vector<vector<int>> field(s1.length() + 1, vector<int>(s2.length() + 1, 300));
    // field[a][b] <-> (a)-prefix from s1 + (b)-postfix from s2

    // way between field[s1.length()][0] and field[0][s2.length]

    const int l1 = s1.length();
    const int l2 = s2.length();

    field[l1][0] = 0;

    for (int x = l1; x >= 0; --x) {
        for (int y = 0; y <= l2; ++y) {

            if (x < l1) {
                field[x][y] = min(field[x][y], field[x + 1][y] + 1);
            }
            if (y > 0) {
                field[x][y] = min(field[x][y], field[x][y - 1] + 1);
            }
            if (x < l1 && y > 0) {
                int cost = 1;

                if (s1[x] == s2[l2 - y]) cost = 0;

                field[x][y] = min(field[x][y], field[x + 1][y - 1] + cost);
            }

        }
    }

    cout << field[0][l2] << endl;

    return 0;
}
