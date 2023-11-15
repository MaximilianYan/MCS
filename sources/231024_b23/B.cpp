#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <limits>
#include <list>
#include <cmath>
#include <assert.h>

using namespace std;

typedef double VecType_t;
class Vec2 {
public:
    VecType_t x, y;

    Vec2() : x(0), y(0) {}
    Vec2(VecType_t x, VecType_t y) : x(x), y(y) {}

    /// @brief Coord of Vec2 (x_1 [1] or x_2 [2])
    VecType_t& operator[](int i) {
        if (i == 1) return x;
        if (i == 2) return y;
        assert(0 && "incorrect Vec2[]");
        return x;
    }

    /// @brief Read Vec2 like "Point_x Point_y"
    friend istream& operator>>(istream& in, Vec2& vec);
    /// @brief Write Vec2 like "x y"
    friend ostream& operator<<(ostream& out, const Vec2& vec);
    /// @brief Scalar product
    friend VecType_t operator,(const Vec2& lo, const Vec2& ro);

    /// @brief Absolute (length)
    double abs() const {
        return sqrt(x * x + y * y);
    }
};

istream& operator>>(istream& in, Vec2& vec) {
    in >> vec.x >> vec.y;

    return in;
}

ostream& operator<<(ostream& out, const Vec2& vec) {
    out << vec.x << " " << vec.y;

    return out;
}

VecType_t operator,(const Vec2& lo, const Vec2& ro) {
    return lo.x * ro.x + lo.y * ro.y;
}

typedef VecType_t LineType_t;
class Line {
public:
    LineType_t a, b, c;

    Line() : a(0), b(0), c(0) {};

    /// @brief Line via two points
    Line(Vec2 x, Vec2 y) {
        if ((x[2] - y[2]) == 0) {
            a = 0;
            b = 1;
            c = -x[2];
        }

        a = -(x[2] - y[2]);
        b = x[1] - y[1];
        c = -(a * x[1] + b * x[2]);
    }

    /// @brief Read line like "Point1_x Point1_y Point2_x Point2_y"
    friend istream& operator>>(istream& in, Line& line);
    /// @brief Write line parameters like "a b c"
    friend ostream& operator<<(ostream& out, const Line& line);

    /// @brief Are lines coincedental
    friend bool operator==(const Line& lo, const Line& ro);
    /// @brief Negative (lo == ro)
    friend bool operator!=(const Line& lo, const Line& ro);
    /// @brief Are lines parallel (lo != ro);
    friend bool operator%(const Line& lo, const Line& ro);

    /// @brief Common point of the lines (single or incorrect)
    friend Vec2 operator^(const Line& lo, const Line& ro);
};

istream& operator>>(istream& in, Line& line) {
    Vec2 point1, point2;
    cin >> point1 >> point2;

    line = Line(point1, point2);

    return in;
}

ostream& operator<<(ostream& out, const Line& line) {
    cout << line.a << " ";
    cout << line.b << " ";
    cout << line.c;

    return out;
}

bool operator==(const Line& lo, const Line& ro) {
    if (lo.a == 0 || ro.a == 0) {
        return (lo.a == ro.a) && (lo.c * ro.b == ro.c * lo.b);
    }
    return (lo.b * ro.a == ro.b * lo.a) && (lo.c * ro.a == ro.c * lo.a);
}

bool operator!=(const Line& lo, const Line& ro) {
    return !(lo == ro);
}

bool operator%(const Line& lo, const Line& ro) {
    if (lo == ro) {
        return false;
    }
    if (lo.a == 0 || ro.a == 0) {
        return (lo.a == ro.a);
    }
    return (lo.b * ro.a == ro.b * lo.a);
}

Vec2 operator^(const Line& lo, const Line& ro) {
    if (lo.a == 0) {
        Vec2 res(0, 0);
        res[2] = -lo.c / lo.b;
        res[1] = -(res[2] * ro.b + ro.c) / ro.a;

        return res;
    }

    if (ro.a == 0) {
        Vec2 res(0, 0);
        res[2] = -ro.c / ro.b;
        res[1] = -(res[2] * lo.b + lo.c) / lo.a;

        return res;
    }


    Vec2 res(0, 0);
    res[2] = -(ro.a * lo.c - lo.a * ro.c) / (ro.a * lo.b - lo.a * ro.b);
    res[1] = -(ro.a * lo.b * res[2] + ro.a * lo.c) / (ro.a * lo.a);

    return res;
}


int main() {
    Line line1, line2;

    cin >> line1 >> line2;

    cout << "line 1: " << line1 << endl;
    cout << "line 2: " << line2 << endl;

    if (line1 == line2) {
        cout << -1 << endl;
        return 0;
    }

    if (line1 % line2) {
        cout << 0 << endl;
        return 0;
    }

    cout << (line1 ^ line2) << endl;

    // double phi = acos((double)(a, b) / a.abs() / b.abs());
    // cout << setprecision(5) << acos((double)(a, b) / a.abs() / b.abs()) << endl;

    return 0;
}
