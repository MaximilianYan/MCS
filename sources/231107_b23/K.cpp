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

class Stair {
public:
    Stair() : value(0) {};
    Stair(int value) : value(value) {};

    int operator=(int init) {
        value = init;
        return init;
    }

    operator int() const {
        return value;
    }

    // friend istream& operator>>(istream& input, Stair& ro);
    // friend ostream& operator<<(ostream& output, Stair& ro);

    // void operator<<(const Stair& ro) {
    //     Sum newSum = ro.sum + value;
    //     if (newSum > sum) sum = newSum, prevStairPtr = &ro;
    // }

    // Stair const* getPrevStairPtr() const {
    //     return prevStairPtr;
    // }

private:
    int value;

    // enum TYPE {
    //     GRASS,
    //     FIELD,
    //     SWAMP,
    // } value;

    // class Sum {
    // public:
    //     Sum() : length(0), profit(0) {
    //         setBad();
    //     }
    //     Sum(const Sum& init) : length(init.length), profit(init.profit) {}

    //     bool isBad() const {
    //         if (profit < 0) {
    //             return true;
    //         }
    //         return false;
    //     }

    //     void setBad() {
    //         length = MAXNUM;
    //         profit = -1;
    //     }

    //     Sum operator+(const Stair::TYPE& value) const {
    //         Sum res(*this);

    //         if (res.isBad()) {
    //             res.setBad();
    //             return res;
    //         }

    //         res.length += 1;

    //         switch (value) {
    //         case SWAMP:
    //             res.setBad();
    //             break;

    //         case GRASS:
    //             res.profit += 1;
    //             break;

    //         case FIELD:
    //             break;
    //         }

    //         return res;
    //     }

    //     bool operator>(const Sum& ro) const {
    //         if (isBad()) return false;

    //         if (length < ro.length) return true;
    //         if (length > ro.length) return false;

    //         if (profit > ro.profit) return true;
    //         return false;
    //     }

    //     Sum operator=(const Sum& init) {
    //         length = init.length;
    //         profit = init.profit;
    //         return init;
    //     }

    //     operator int() const {
    //         return profit;
    //     }

    //     long long int operator=(const long long int& init) {
    //         if (init != 0) error();
    //         length = 0;
    //         profit = 0;
    //         return init;
    //     }

    //     friend ostream& operator<<(ostream& output, Sum& ro);

    // private:
    //     long long int length;
    //     long long int profit;
    // };
    // Sum sum;

    // Stair const* prevStairPtr;

    // friend ostream& operator<<(ostream& output, Sum& ro);
};

// istream& operator>>(istream& input, Stair& ro) {
//     char in = 0;
//     input >> in;

//     switch (in) {
//     case 'w':
//         ro.value = Stair::TYPE::SWAMP;
//         break;
//     case '"':
//         ro.value = Stair::TYPE::GRASS;
//         break;
//     case '.':
//         ro.value = Stair::TYPE::FIELD;
//         break;
//     }

//     return input;
// }

// ostream& operator<<(ostream& output, Stair& ro) {
//     output << ro.sum;

//     return output;
// }

// ostream& operator<<(ostream& output, Stair::Sum& ro) {
//     if (ro.isBad()) {
//         output << -1;
//     } else {
//         output << ro.length << " " << ro.profit;
//     }

//     return output;
// }

int main() {
    int n = 0, k = 0;

    cin >> n >> k;

    vector<int> coeffs(k + 1, 0);
    coeffs[k] = 1;

    for (int i = 0; n - i > 0; ++i) {
        for (int j = 0; j < k; ++j) {
            coeffs[j] += coeffs[j + 1];
        }
    }

    cout << coeffs[0] << endl;
    return 0;

    ///< field[n][k] = C из (n) по (k)
    vector<vector<int>> field(n + 1, vector<int>(k + 1, 0));

    {
        /// C(0, 0) = 1
        /// C(0, k) = 0
        /// C(n, 0) = 1

        field[0][0] = 1;

        for (int posN = 1; posN <= n; ++posN) {
            field[posN][0] = field[posN - 1][0]; /// = 1
            for (int posK = 1; posK <= k; ++posK) {
                field[posN][posK] = field[posN - 1][posK] + field[posN - 1][posK - 1];
            }
        }
    }

    cout << field[n][k] << endl;

    return 0;
}
