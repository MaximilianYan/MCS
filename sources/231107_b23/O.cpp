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

template<typename _Tp>
istream& operator>>(istream& input, vector<_Tp>& arr);

class SeqInf {
public:
    SeqInf();

    friend SeqInf operator+(const SeqInf& lo, const int& ro);
    void operator<<=(const SeqInf& ro);

    friend ostream& operator<<(ostream& output, const SeqInf& ro);
private:
    int length;
};

int main() {
    int n = 0, m = 0;
    cin >> n;

    vector<int> arr1(n, 0);
    cin >> arr1;

    cin >> m;
    vector<int> arr2(m, 0);
    cin >> arr2;


    vector<vector<SeqInf>> field(n + 1, vector<SeqInf>(m + 1));
    ///< field[a][b] - most common subseq berween (a)-prefix arr1 & (b)-prefix arr2

    ///< field[x][0] and field[0][y] are correct

    for (int x = 0; x <= n; ++x) {
        for (int y = 0; y <= m; ++y) {

            if (x > 0) {
                if (arr1[x - 1] == arr2[y]) {
                    field[x][y] <<= field[x - 1][y];
                }
            }

            if (y > 0) {
                if (arr1[x] == arr2[y - 1]) {
                    field[x][y] <<= field[x][y - 1];
                }
            }

            if (arr1[x] = arr2[y]) {
                field[x][y] = field[x][y] + 1;
            }

        }
    }

    cout << field[n][m] << endl;

    return 0;
}

template<typename _Tp>
istream& operator>>(istream& input, vector<_Tp>& arr) {
    for (auto& a : arr) input >> a;
    return input;
}

SeqInf::SeqInf() : length(0) {}

SeqInf operator+(const SeqInf& lo, const int& ro) {
    SeqInf res;
    res.length = lo.length + ro;
    return res;
}

void SeqInf::operator<<=(const SeqInf& ro) {
    if (length < ro.length) {
        length = ro.length;
    }
}

ostream& operator<<(ostream& output, const SeqInf& ro) {
    output << ro.length;
    return output;
}

