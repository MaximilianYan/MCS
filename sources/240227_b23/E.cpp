#include <iostream>
#include <random>
#include <functional>
#include <utility>
#include <string>
#include <sstream>
#include <stdint.h>
#include <algorithm>
#include <cmath>
#include <complex>
#include <vector>

using namespace std;

unsigned long long int const logLimit = 19;
unsigned long long int const limit = 1 << logLimit;

unsigned long long int const DIGITS2ONE = 9;
unsigned long long int DIGITS2ONE_MOD;

vector<unsigned long long int> rev;
/// @brief Сопостовление индексов при перегруппировке
void calcRev() {
    rev = vector<unsigned long long int>(limit, 0);
    for (unsigned long long int i = 0; i < limit; i++)
        for (unsigned long long int k = 0; k < logLimit; k++)
            if (i & (1 << k))
                rev[i] ^= 1 << (logLimit - k - 1);
}

using Num = complex<long double>;

double const Pi = acos(-1.0);



vector<Num> z;
/// @brief первообразные корни степени limit
void calcZ() {
    z = vector<Num>(limit);
    for (unsigned long long int i = 0; i < limit; i++)
        z[i] = Num(cos(i * 2 * Pi / limit),
            sin(i * 2 * Pi / limit));
}

vector<Num> fft(const vector<Num>& a0, bool inv = false) {
    vector<Num> a = a0;
    for (unsigned long long int i = 0; i < limit; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    if (inv)
        reverse(z.begin() + 1, z.end());
    for (unsigned long long int k = 0, span = 1, step = limit / 2; k < logLimit;
        k++, span *= 2, step /= 2) {
        for (unsigned long long int i = 0; i < limit; i += 2 * span)
            for (unsigned long long int j = 0; j < span; j++) {
                unsigned long long int u = i + j;
                unsigned long long int v = i + j + span;
                Num x = a[u] + a[v] * z[j * step];
                Num y = a[u] + a[v] * z[j * step + limit / 2];
                a[u] = x;
                a[v] = y;
            }
    }
    if (inv) {
        reverse(z.begin() + 1, z.end());
        for (unsigned long long int i = 0; i < limit; i++)
            a[i] /= limit;
    }
    return a;
}

vector<Num> readNumber(int& sgn) {
    string s;
    cin >> s;
    vector<Num> res(limit, Num(0));
    unsigned long long int n = (unsigned long long int)(s.size());

    unsigned long long int nSh = n;
    sgn = 1;
    if (s[0] == '-') {
        sgn = -1;
        --nSh;
    }
    for (unsigned long long int i = 0; i < nSh; ++i) {
        unsigned long long mult = 1;
        for (unsigned long long int oi = 0; oi < DIGITS2ONE; ++oi) {
            if (i % DIGITS2ONE == oi)
                res[i / DIGITS2ONE] += Num((s[n - 1 - i] - '0') * mult);
            mult *= 10;
        }
    }

    return res;
}

vector<unsigned long long int> mul(const vector<Num>& a, const vector<Num>& b) {
    vector<Num> fa = fft(a);
    vector<Num> fb = fft(b);
    vector<Num> fc = vector<Num>(limit);
    for (unsigned long long int i = 0; i < limit; i++)
        fc[i] = fa[i] * fb[i];
    vector<Num> c = fft(fc, true);

    vector<unsigned long long int> res(limit);
    long long carry = 0;
    for (unsigned long long int i = 0; i < limit; i++) {
        carry += (long long)(c[i].real() + 0.5);
        res[i] = carry % DIGITS2ONE_MOD;
        carry /= DIGITS2ONE_MOD;
    }

    return res;
}

int main() {
    DIGITS2ONE_MOD = 1;
    for (unsigned long long int i = 0; i < DIGITS2ONE; ++i)
        DIGITS2ONE_MOD *= 10;

    calcRev();
    calcZ();
    int sgnA = 1;
    int sgnB = 1;

    vector<Num> a = readNumber(sgnA);
    vector<Num> b = readNumber(sgnB);

    vector<unsigned long long int> res = mul(a, b);


    if (sgnA * sgnB == -1) {
        cout << "-";
    }
    bool started = false;
    for (unsigned long long int j = 0; j < limit; j++) {
        unsigned long long int i = limit - 1 - j;

        unsigned long long mult = DIGITS2ONE_MOD;
        for (unsigned long long int oi = 0; oi < DIGITS2ONE; ++oi) {
            mult /= 10;

            started |= (((res[i] / mult) % 10) != 0) | (i == 0 && mult == 1);
            if (started)
                cout << ((res[i] / mult) % 10);
        }

        // started |= (((res[i] / 10) % 10) != 0);
        // if (started)
        //     cout << ((res[i] / 10) % 10);

        // started |= (i == 0) | (res[i] != 0);
        // if (started)
        //     cout << res[i] % 10;
    }
    cout << endl;
    return 0;
}