#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <vector>

using namespace std;

int main() {
    int n = 0;
    cin >> n;
    vector<uint64_t> field(n + 1, 0);

    {
        int pos = -1;

        field[++pos] = 1; // [0]
        const vector<int> moves({ +2, +3 });

        while (++pos <= n) {
            for (int move : moves) {
                signed int prev = pos - move;
                if (prev >= 0) field[pos] += field[prev];
            }
        }
    }


    cout << field[n] << endl;

    return 0;
}
