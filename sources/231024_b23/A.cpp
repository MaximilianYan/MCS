#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <limits>
#include <list>
#include <cmath>

using namespace std;

typedef int VecType_t;
class Vec2 {
public:
    VecType_t x, y;

    friend istream& operator>>(istream& in, Vec2& vec);
    friend VecType_t operator,(const Vec2& lo, const Vec2& ro);

    double abs() const {
        return sqrt(x * x + y * y);
    }
};

istream& operator>>(istream& in, Vec2& vec) {
    in >> vec.x >> vec.y;

    return in;
}

VecType_t operator,(const Vec2& lo, const Vec2& ro) {
    return lo.x * ro.x + lo.y * ro.y;
}

int main() {
    Vec2 a, b;
    cin >> a >> b;

    cout << setprecision(5) << acos((double)(a, b) / a.abs() / b.abs()) << endl;

    return 0;
}
