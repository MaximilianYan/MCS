#include <iostream>

using namespace std;

class Bi {
public:
    Bi() : a(0), b(0) {}
    Bi(int a, int b) : a(a), b(b) {}

    friend istream& operator>>(istream& input, Bi& ro) {
        return input >> ro.a >> ro.b;
    }
    friend ostream& operator<<(ostream& output, const Bi& ro) {
        return output << ro.a << ' ' << ro.b;
    }
    friend bool operator==(const Bi& lo, const Bi& ro) {
        return
            lo.a == ro.a &&
            lo.b == ro.b
            ;
    }
    friend bool operator!=(const Bi& lo, const Bi& ro) {
        return !(lo == ro);
    }
    friend bool operator>(const Bi& lo, const int& ro) {
        return
            lo.a > ro &&
            lo.b > ro
            ;
    }

    void operator=(const Bi& ro) {
        this->a = ro.a;
        this->b = ro.b;
    }
    void operator-=(const Bi& ro) {
        this->a -= ro.a;
        this->b -= ro.b;
    }
    friend Bi operator*(const int& lo, const Bi& ro) {
        return Bi(lo * ro.a, lo * ro.b);
    }
    friend Bi operator-(const Bi& lo, const Bi& ro) {
        return Bi(lo.a - ro.a, lo.b - ro.b);
    }

    void positive() {
        a = abs(a);
        b = abs(b);
    }

    friend void iteration(Bi& rem/*, Bi& coefA, Bi& coefB*/) {
        if (rem.a >= rem.b) {
            // coefA -= rem.a / rem.b * coefB;
            rem.a = rem.a % rem.b;
        } else {
            // coefB -= rem.b / rem.a * coefA;
            rem.b = rem.b % rem.a;
        }
    }

    int ans() {
        if (a == 0) return b;
        if (b == 0) return a;
        while (true);
    }

private:
    int a;
    int b;
};

int main() {
    Bi p1, p2;

    cin >> p1 >> p2;

    Bi segment = p2 - p1;
    segment.positive();

    Bi rem = segment;
    while (rem > 0) {
        iteration(rem);
    }

    cout << rem.ans() + 1 << endl;

}
