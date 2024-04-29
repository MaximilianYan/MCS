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

int const logLimit = 18;
int const limit = 1 << logLimit;



vector<int> rev;
/// @brief Сопостовление индексов при перегруппировке
void calcRev() {
    rev = vector<int>(limit, 0);
    for (int i = 0; i < limit; i++)
        for (int k = 0; k < logLimit; k++)
            if (i & (1 << k))
                rev[i] ^= 1 << (logLimit - k - 1);
}

using Num = complex<long double>;

double const Pi = acos(-1.0);



vector<Num> z;
/// @brief первообразные корни степени limit
void calcZ() {
    z = vector<Num>(limit);
    for (int i = 0; i < limit; i++)
        z[i] = Num(cos(i * 2 * Pi / limit),
            sin(i * 2 * Pi / limit));
}

vector<Num> fft(const vector<Num>& a0, bool inv = false) {
    vector<Num> a = a0;
    for (int i = 0; i < limit; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    if (inv)
        reverse(z.begin() + 1, z.end());
    for (int k = 0, span = 1, step = limit / 2; k < logLimit;
        k++, span *= 2, step /= 2) {
        for (int i = 0; i < limit; i += 2 * span)
            for (int j = 0; j < span; j++) {
                int u = i + j;
                int v = i + j + span;
                Num x = a[u] + a[v] * z[j * step];
                Num y = a[u] + a[v] * z[j * step + limit / 2];
                a[u] = x;
                a[v] = y;
            }
    }
    if (inv) {
        reverse(z.begin() + 1, z.end());
        for (int i = 0; i < limit; i++)
            a[i] /= limit;
    }
    return a;
}

vector<Num> readNumber(int& sgn) {
    string s;
    cin >> s;
    vector<Num> res(limit, Num(0));
    int n = int(s.size());

    int nSh = n;
    sgn = 1;
    if (s[0] == '-') {
        sgn = -1;
        --nSh;
    }
    for (int i = 0; i < nSh; i++)
        res[i] = Num(s[n - 1 - i] - '0');
    return res;
}

vector<int> mul(const vector<Num>& a, const vector<Num>& b) {
    vector<Num> fa = fft(a);
    vector<Num> fb = fft(b);
    vector<Num> fc = vector<Num>(limit);
    for (int i = 0; i < limit; i++)
        fc[i] = fa[i] * fb[i];
    vector<Num> c = fft(fc, true);

    vector<int> res(limit);
    long long carry = 0;
    for (int i = 0; i < limit; i++) {
        carry += (long long)(c[i].real() + 0.5);
        res[i] = carry % 10;
        carry /= 10;
    }

    return res;
}

const int SHIFT = limit / 2;

int main() {
    calcRev();
    calcZ();
    int sgnA = 1;
    int sgnB = 1;

    vector<Num> a = readNumber(sgnA);
    vector<Num> b = readNumber(sgnB);

    vector<Num> aLess(limit, Num(0));
    vector<Num> aGrrt(limit, Num(0));
    vector<Num> bLess(limit, Num(0));
    vector<Num> bGrrt(limit, Num(0));

    copy(a.begin() + SHIFT, a.end(), aLess.begin());
    copy(a.begin(), a.begin() + SHIFT, aGrrt.begin());
    copy(b.begin() + SHIFT, b.end(), bLess.begin());
    copy(b.begin(), b.begin() + SHIFT, bGrrt.begin());

    vector<Num> aKarr(limit, Num(0));
    vector<Num> bKarr(limit, Num(0));
    for (int i = 0; i < limit; ++i)
        aKarr[limit - 1 - i] =
        aGrrt[limit - 1 - i] +
        aLess[limit - 1 - i];
    for (int i = 0; i < limit; ++i)
        bKarr[limit - 1 - i] =
        bGrrt[limit - 1 - i] +
        bLess[limit - 1 - i];


    vector<int> resLess = mul(aLess, bLess);
    vector<int> resGrrt = mul(aGrrt, bGrrt);
    vector<int> resKarr = mul(aKarr, bKarr);

    vector<int> res(2 * limit, 0);

    for (int i = 0; i < SHIFT; ++i)
        res[2 * limit - 1 - i] = resLess[limit - 1 - i];
    for (int i = 0; i < SHIFT; ++i)
        res[2 * limit - 1 - i - SHIFT] =
        resLess[limit - 1 - i - SHIFT] +
        resKarr[limit - 1 - i] -
        resLess[limit - 1 - i] -
        resGrrt[limit - 1 - i];
    for (int i = 0; i < SHIFT; ++i)
        res[2 * limit - 1 - i - 2 * SHIFT] =
        resKarr[limit - 1 - i - SHIFT] -
        resLess[limit - 1 - i - SHIFT] -
        resGrrt[limit - 1 - i - SHIFT] +
        resGrrt[limit - 1 - i];
    for (int i = 0; i < SHIFT; ++i)
        res[2 * limit - 1 - i - 3 * SHIFT] =
        resGrrt[limit - 1 - i - SHIFT];



    if (sgnA * sgnB == -1) {
        cout << "-";
    }
    bool started = false;
    for (int i = 2 * limit - 1; i >= 0; i--) {
        started |= (i == 0) | (res[i] != 0);
        if (started)
            cout << res[i];
    }
    cout << endl;
    return 0;
}