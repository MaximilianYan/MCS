#include <iostream>

using namespace std;

class Bi {
public:
    Bi() : a(0), b(0) {}
    Bi(long long int a, long long int b) : a(a), b(b) {}

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
    friend bool operator>(const Bi& lo, const long long int& ro) {
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
    friend Bi operator*(const long long int& lo, const Bi& ro) {
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

    long long int ans() {
        if (a == 0) return b;
        if (b == 0) return a;
        while (true);
    }

private:
    long long int a;
    long long int b;
};

long long int gcd(long long int a, long long int b) {
    Bi rem{ a, b };
    while (rem > 0) {
        iteration(rem);
    }
    return rem.ans();
}

int main() {
    long long int pers[3];
    for (int i = 0; i < 3; ++i) {
        cin >> pers[i];
    }

    long long int n = 0;
    cin >> n;

    long long int gcdIN[3];
    long long int lcmIN[3];
    for (int i = 0; i < 3; ++i) {
        gcdIN[i] = gcd(pers[i], pers[(i + 1) % 3]);
        lcmIN[i] = pers[i] / gcdIN[i] * pers[(i + 1) % 3];
    }

    long long int gcdAll = gcd(pers[0], gcdIN[1]);

    long long int lcmAll = lcmIN[1] / gcd(lcmIN[1], pers[0]) * pers[0];


    long long int answer = 0;

    for (int i = 0; i < 3; ++i) {
        answer += n / pers[i];
        answer -= n / lcmIN[i];
    }
    answer += n / lcmAll;

    cout << answer << endl;

}
