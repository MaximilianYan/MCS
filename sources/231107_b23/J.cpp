#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <limits>
#include <list>
#include <sstream>
#include <string>

// #define LOCAL
// #define NOERROR

#ifdef LOCAL
#define error() \
    cout << "ERROR : " << __LINE__ << " LINE" << endl;
#else
#ifndef NOERROR
#define error() \
    while (true);
#endif
#endif

using namespace std;

const long long int MINNUM = numeric_limits<long long int>::min();
const long long int MAXNUM = numeric_limits<long long int>::max();

class Stair {
public:
    Stair() : value(FIELD), sum(), prevStairPtr(nullptr) {};

    long long int operator=(long long int init) {
        if (init != 0) error();
        sum = 0;
        return init;
    }

    operator int() const {
        if (value == SWAMP) return -1;
        return sum;
    }

    friend istream& operator>>(istream& input, Stair& ro);
    friend ostream& operator<<(ostream& output, Stair& ro);

    void operator<<(const Stair& ro) {
        Sum newSum = ro.sum + value;
        if (newSum > sum) sum = newSum, prevStairPtr = &ro;
    }

    Stair const* getPrevStairPtr() const {
        return prevStairPtr;
    }

private:
    enum TYPE {
        GRASS,
        FIELD,
        SWAMP,
    } value;

    class Sum {
    public:
        Sum() : length(0), profit(0) {
            setBad();
        }
        Sum(const Sum& init) : length(init.length), profit(init.profit) {}

        bool isBad() const {
            if (profit < 0) {
                return true;
            }
            return false;
        }

        void setBad() {
            length = MAXNUM;
            profit = -1;
        }

        Sum operator+(const Stair::TYPE& value) const {
            Sum res(*this);

            if (res.isBad()) {
                res.setBad();
                return res;
            }

            res.length += 1;

            switch (value) {
            case SWAMP:
                res.setBad();
                break;

            case GRASS:
                res.profit += 1;
                break;

            case FIELD:
                break;
            }

            return res;
        }

        bool operator>(const Sum& ro) const {
            if (isBad()) return false;

            if (length < ro.length) return true;
            if (length > ro.length) return false;

            if (profit > ro.profit) return true;
            return false;
        }

        Sum operator=(const Sum& init) {
            length = init.length;
            profit = init.profit;
            return init;
        }

        operator int() const {
            return profit;
        }

        long long int operator=(const long long int& init) {
            if (init != 0) error();
            length = 0;
            profit = 0;
            return init;
        }

        friend ostream& operator<<(ostream& output, Sum& ro);

    private:
        long long int length;
        long long int profit;
    };
    Sum sum;

    Stair const* prevStairPtr;

    friend ostream& operator<<(ostream& output, Sum& ro);
};

istream& operator>>(istream& input, Stair& ro) {
    char in = 0;
    input >> in;

    switch (in) {
    case 'w':
        ro.value = Stair::TYPE::SWAMP;
        break;
    case '"':
        ro.value = Stair::TYPE::GRASS;
        break;
    case '.':
        ro.value = Stair::TYPE::FIELD;
        break;
    }

    return input;
}

ostream& operator<<(ostream& output, Stair& ro) {
    output << ro.sum;

    return output;
}

ostream& operator<<(ostream& output, Stair::Sum& ro) {
    if (ro.isBad()) {
        output << -1;
    } else {
        output << ro.length << " " << ro.profit;
    }

    return output;
}


int main() {
    long long int n = 0;
    cin >> n;
    vector<Stair> field(n);
    for (long long int i = 0; i < field.size(); ++i) cin >> field[i];

    const vector<long long int> moves({ +2, +3, +6 });

    {
        long long int pos = -1;

        field[++pos] = 0; // [0]


        while (++pos < n) {
            for (long long int move : moves) {
                signed long long int prev = pos - move;
                if (prev >= 0) field[pos] << field[prev];
            }
        }
    }

    cout << field[n - 1] << endl;

    if (field[n - 1] == -1) return 0;

    string buffer;
    {
        long long int pos = n - 1;

        while (pos >= 0) {
            stringstream buf;
            buf << pos + 1 << " ";
            buffer = buf.str() + buffer;

            if (pos == 0) break;

            for (long long int move : moves) {
                // ДА Я ЗНАЮ ЧТО ВЕКТОР МОЖЕТ ПОМЕНЯТЬ АДРЕС МАССИВА В ПАМЯТИ, НО ВРОДЕ НЕ ДОЛЖЕН
                if (field[pos].getPrevStairPtr() == &*(field.begin() + pos - move)) {
                    pos = pos - move;
                    break;
                }
            }
        }
    }

    cout << buffer << endl;

    return 0;
}
