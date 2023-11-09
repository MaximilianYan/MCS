#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

static long long int NEUTRALINT = numeric_limits<long long int>::max();

class Gap {
public:
    Gap() : length(-1), sumUsed(NEUTRALINT), sumFree(NEUTRALINT) {};

    long long int operator=(long long int init) {
        if (init != 0) cout << "CLEAR your EYES" << endl;
        sumUsed = length;
        sumFree = NEUTRALINT;
        return init;
    }

    operator int() const {
        // return max(sumUsed, sumFree);
        return sumUsed;
    }

    // friend istream& operator>>(istream& input, Stair& ro);

    void operator<<(const Gap& ro) {
        // long long int newSumUsed = ro.sumWithout + value;
        // long long int newSumFree = ro.sumUsed;
        // if (newSumUsed < sumUsed) sumUsed = newSumUsed;
        // if (newSumFree < sumFree) sumFree = newSumFree;

        sumFree = ro.sumUsed;
        sumUsed = min(ro.sumFree, ro.sumUsed) + length;
    }

    friend void operator<<(vector<Gap>& lo, const vector<long long int>& ro);

private:
    long long int length;
    long long int sumUsed;
    long long int sumFree;

};

void operator<<(vector<Gap>& lo, const vector<long long int>& ro) {
    for (long long int i = 1; i < ro.size(); ++i) {
        lo[i - 1].length = ro[i] - ro[i - 1];
    }
}

// istream& operator>>(istream& input, Stair& ro) {
//     input >> ro.coord;

//     return input;
// }

int main() {
    long long int n = 0;
    cin >> n;
    vector<long long int> coords(n, -1);
    for (long long int i = 0; i < coords.size(); ++i) cin >> coords[i];
    sort(coords.begin(), coords.end());
    vector<Gap> field(n - 1);
    field << coords;

    {
        long long int pos = -1;

        field[++pos] = 0; // [0]

        const vector<long long int> moves({ +1 });

        while (++pos < field.size()) {
            for (long long int move : moves) {
                signed long long int prev = pos - move;
                if (prev >= 0) field[pos] << field[prev];
            }
        }
    }

    cout << field[field.size() - 1] << endl;

    return 0;
}
