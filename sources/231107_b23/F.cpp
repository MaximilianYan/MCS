#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class Stair {
public:
    Stair() : value(0), sumWith(numeric_limits<long long int>::min()), sumWithout(sumWith) {};

    long long int operator=(long long int init) {
        sumWith = init;
        sumWithout = init;
        return init;
    }

    operator int() const {
        return max(sumWith, sumWithout);
    }

    friend istream& operator>>(istream& input, Stair& ro);

    void operator<<(const Stair& ro) {
        long long int newSumWith = ro.sumWithout + value;
        long long int newSumWithout = ro;
        if (newSumWith/**/> sumWith)/**/sumWith/**/= newSumWith;
        if (newSumWithout > sumWithout) sumWithout = newSumWithout;
    }

private:
    long long int value;
    long long int sumWith;
    long long int sumWithout;

};

istream& operator>>(istream& input, Stair& ro) {
    input >> ro.value;

    return input;
}

int main() {
    long long int n = 0;
    cin >> n;
    vector<Stair> field(n + 2); // 0, size-1 - технические
    for (long long int i = 1; i < field.size() - 1; ++i) cin >> field[i];

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
