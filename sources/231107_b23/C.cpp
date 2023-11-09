#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <vector>

using namespace std;

long long int MOD = 12345;

class LineC {
public:
    const long long int NMax;
    vector<long long int> count;

    LineC(long long int nMax) : NMax(nMax), count(NMax + 1, 0) {};

    const vector<long long int>& operator=(const vector<long long int>& init) {
        count = init;
        return init;
    }

    operator long long int() const {
        long long int res = 0;
        for (long long int n : count) (res += n, res %= MOD);
        return res;
    }

    friend void operator<<(LineC& lo, const LineC& ro);

};

void operator<<(LineC& lo, const LineC& ro) {
    lo.count[0] = ro;
    for (long long int i = 0; i < ro.NMax; ++i) {
        lo.count[i + 1] = ro.count[i];
    }
}

int main() {
    long long int n = 0;
    cin >> n;
    vector<LineC> field(n + 1, LineC(2));

    {
        long long int pos = -1;

        field[++pos].count[0] = 1; // [0]
        const vector<long long int> moves({ +1 });

        while (++pos <= n) {
            for (long long int move : moves) {
                signed long long int prev = pos - move;
                if (prev >= 0) field[pos] << field[prev];
            }
        }
    }

    cout << field[n] << endl;

    return 0;
}
