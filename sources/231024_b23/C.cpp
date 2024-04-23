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

typedef long double VecType_t;
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
    /// @brief Comparing
    friend bool operator==(const Vec2& lo, const Vec2& ro);

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
    out << fixed << setprecision(6) << vec.x << " " << vec.y;

    return out;
}

VecType_t operator,(const Vec2& lo, const Vec2& ro) {
    return lo.x * ro.x + lo.y * ro.y;
}

bool operator==(const Vec2& lo, const Vec2& ro) {
    return
        lo.x == ro.x &&
        lo.y == ro.y
        ;
}

typedef VecType_t MatType_t;
class Mat {
public:
    MatType_t data[2][2];

    Mat() {
        data[0][0] = 0;
        data[0][1] = 0;
        data[1][0] = 0;
        data[1][1] = 0;
    }
    Mat(MatType_t a, MatType_t b, MatType_t c, MatType_t d) {
        data[0][0] = a;
        data[0][1] = b;
        data[1][0] = c;
        data[1][1] = d;
    }

    operator MatType_t() {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }
};


typedef VecType_t LineType_t;
class Line {
public:
    LineType_t a, b, c;

    Line() : a(0), b(0), c(0) {};

    /// @brief Line via two points
    Line(Vec2 x, Vec2 y) {
        // if ((x[2] - y[2]) == 0) {
            // a = 0;
            // b = 1;
            // c = -x[2];
        // }

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
    Mat mat_bc, mat_ac, mat_ab;

    mat_bc = Mat(
        lo.b, lo.c,
        ro.b, ro.c
    );
    mat_ac = Mat(
        lo.a, lo.c,
        ro.a, ro.c
    );
    mat_ab = Mat(
        lo.a, lo.b,
        ro.a, ro.b
    );

    MatType_t det_bc = mat_bc;
    MatType_t det_ac = mat_ac;
    MatType_t det_ab = mat_ab;

    if (det_ab == 0) {
        if (det_bc == 0 && det_ac == 0) {
            // coincedental
            return true;
        } else {
            // parallel
        }
    }
    return false;
    // if (lo.a == 0 || ro.a == 0) {
    //     return (lo.a == ro.a) && (lo.c * ro.b == ro.c * lo.b);
    // }
    // return (lo.b * ro.a == ro.b * lo.a) && (lo.c * ro.a == ro.c * lo.a);
}

bool operator!=(const Line& lo, const Line& ro) {
    return !(lo == ro);
}

bool operator%(const Line& lo, const Line& ro) {
    Mat mat_bc, mat_ac, mat_ab;

    mat_bc = Mat(
        lo.b, lo.c,
        ro.b, ro.c
    );
    mat_ac = Mat(
        lo.a, lo.c,
        ro.a, ro.c
    );
    mat_ab = Mat(
        lo.a, lo.b,
        ro.a, ro.b
    );

    MatType_t det_bc = mat_bc;
    MatType_t det_ac = mat_ac;
    MatType_t det_ab = mat_ab;

    if (det_ab == 0) {
        if (det_bc == 0 && det_ac == 0) {
            // coincedental
        } else {
            return true;
            // parallel
        }
    }
    return false;
    // if (lo == ro) {
    //     return false;
    // }
    // if (lo.a == 0 || ro.a == 0) {
    //     return (lo.a == ro.a);
    // }
    // return (lo.b * ro.a == ro.b * lo.a);
}

Vec2 operator^(const Line& lo, const Line& ro) {
    Mat mat_bc, mat_ac, mat_ab;

    mat_bc = Mat(
        lo.b, lo.c,
        ro.b, ro.c
    );
    mat_ac = Mat(
        lo.a, lo.c,
        ro.a, ro.c
    );
    mat_ab = Mat(
        lo.a, lo.b,
        ro.a, ro.b
    );

    MatType_t det_bc = mat_bc;
    MatType_t det_ac = mat_ac;
    MatType_t det_ab = mat_ab;

    if (det_ab == 0) {
        if (det_bc == 0 && det_ac == 0) {
            // coincedental
            return Vec2(239000, 239000);
        } else {
            // parallel
            return Vec2(-239000, -239000);
        }
    }

    return Vec2(det_bc / det_ab, -det_ac / det_ab);

    // if (lo.a == 0) {
    //     Vec2 res(0, 0);
    //     res[2] = -lo.c / lo.b;
    //     res[1] = -(res[2] * ro.b + ro.c) / ro.a;

    //     return res;
    // }

    // if (ro.a == 0) {
    //     Vec2 res(0, 0);
    //     res[2] = -ro.c / ro.b;
    //     res[1] = -(res[2] * lo.b + lo.c) / lo.a;

    //     return res;
    // }


    // Vec2 res(0, 0);
    // res[2] = -(ro.a * lo.c - lo.a * ro.c) / (ro.a * lo.b - lo.a * ro.b);
    // res[1] = -(ro.a * lo.b * res[2] + ro.a * lo.c) / (ro.a * lo.a);

    // return res;
}


class Segment {
public:
    Vec2 points[2];

    Line line;

    Segment() {
        points[0] = Vec2();
        points[1] = Vec2();
        line = Line(points[0], points[1]);
    };

    /// @brief Segment between two points
    Segment(Vec2 p0, Vec2 p1) {
        points[0] = p0;
        points[1] = p1;
        line = Line(points[0], points[1]);
    }

    /// @brief Read line like "Point1_x Point1_y Point2_x Point2_y"
    friend istream& operator>>(istream& in, Segment& segment);

    /// @brief Is the segment a point
    bool isTrivial();

    /// @brief Checks if the point belongs segment's bounding rectangle 
    bool isInRect(const Vec2& point);
    /*
    /// @brief Checks if the segment belongs segment's bounding rectangle
    bool isInRect(const Segment& segment);
    /*
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
    */
};

istream& operator>>(istream& in, Segment& segment) {
    Vec2 point1, point2;
    cin >> point1 >> point2;

    segment = Segment(point1, point2);

    return in;
}

bool Segment::isTrivial() {
    return points[0] == points[1];
}

bool Segment::isInRect(const Vec2& point) {
    return
        point.x >= min(points[0].x, points[1].x) &&
        point.x <= max(points[0].x, points[1].x) &&
        point.y >= min(points[0].y, points[1].y) &&
        point.y <= max(points[0].y, points[1].y)
        ;
}


int main() {
    Segment segments[2];
    for (int i = 0; i < 2; ++i)
        cin >> segments[i];

    // cout << "line 1: " << line1 << endl;
    // cout << "line 2: " << line2 << endl;
    for (int j = 0; j < 2; ++j) {
        bool i = j;
        if (segments[i].isTrivial()) {
            if (segments[!i].isInRect(segments[i].points[0])) {
                cout << segments[i].points[0] << endl;
                return 0;
            } else {
                cout << "Empty" << endl;
                return 0;
            }
        }
    }

    if (segments[0].line == segments[1].line) {
        Vec2 points[4];
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                points[(i << 1) + j] = segments[i].points[j];

        sort(points, points + 4, [](const Vec2& lo, const Vec2& ro) -> bool {
            if (lo.x < ro.x) return 1;
            if (lo.x > ro.x) return 0;
            if (lo.y < ro.y) return 1;
            if (lo.y > ro.y) return 0;
            return 1;
        });


        vector<Vec2> internals;
        for (int i = 1; i < 3; ++i)
            if (
                segments[0].isInRect(points[i]) &&
                segments[1].isInRect(points[i])
                ) internals.emplace_back(points[i]);


        if (internals.size() == 0) {
            cout << "Empty" << endl;
            return 0;
        }

        if (internals.size() == 2) {
            cout << *internals.begin() << ' ' << *internals.rbegin() << endl;
            return 0;
        }

        cout << "WTf???" << endl;
        return 0;
    }

    if (segments[0].line % segments[1].line) {
        cout << "Empty" << endl;
        return 0;
    }

    Vec2 common = segments[0].line ^ segments[1].line;
    if (
        segments[0].isInRect(common) &&
        segments[0].isInRect(common)
        ) cout << common << endl;
    else
        cout << "Empty" << endl;

    // double phi = acos((double)(a, b) / a.abs() / b.abs());
    // cout << setprecision(5) << acos((double)(a, b) / a.abs() / b.abs()) << endl;

    return 0;
}
