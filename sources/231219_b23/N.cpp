#include <iostream>
#include <random>
#include <functional>
#include <utility>
#include <string>
#include <sstream>
#include <stdint.h>

using namespace std;

int main() {
    string str;
    cin >> str;

    vector<int> field(str.length(), 0);

    for (int i1 = 0; i1 < str.length(); ++i1) {
        char minc = 'z';
        for (int pos = 0; pos < str.length() - i1; ++pos) {
            if (field[pos] == i1)
                minc = min(minc, str[pos + field[pos]]);
        }

        for (int pos = 0; pos < str.length() - i1; ++pos) {
            if (field[pos] == i1) {
                if (str[pos + field[pos]] == minc) {
                    field[pos] += 1;
                }
            }
        }
    }

    int maxPos = 0;
    for (int pos = str.length() - 1; pos >= 0; --pos) {
        if (field[pos] == str.length() - pos) {
            maxPos = pos;
            break;
        }
    }

    for (int pos = maxPos; pos < str.length(); ++pos) {
        cout << str[pos];
    }
    cout << endl;

    return 0;
}
