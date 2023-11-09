#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class Stair {
public:
    Stair() : value(0), sum(numeric_limits<long long int>::min()) {};

    long long int operator=(long long int init) {
        sum = init;
        return init;
    }

    operator int() const {
        return sum;
    }

    friend istream& operator>>(istream& input, Stair& ro);

    void operator<<(const Stair& ro) {
        long long int newSum = ro.sum + value;
        if (newSum > sum) sum = newSum;
    }

private:
    long long int value;
    long long int sum;

};

istream& operator>>(istream& input, Stair& ro) {
    input >> ro.value;

    return input;
}

int main() {
    long long int n = 0;
    cin >> n;
    vector<Stair> field(n + 1);
    for (long long int i = 1; i < field.size(); ++i) cin >> field[i];

    {
        long long int pos = -1;

        field[++pos] = 0; // [0]

        const vector<long long int> moves({ +1, +2 });

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
