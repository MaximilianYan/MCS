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

int logLimit;
int limit;

vector<int> rev;
/// @brief Сопостовление индексов при перегруппировке
void calcRev() {
    rev = vector<int>(limit, 0);
    for (int i = 0; i < limit; i++)
        for (int k = 0; k < logLimit; k++)
            if (i & (1 << k))
                rev[i] ^= 1 << (logLimit - k - 1);
}

using Num = complex <double>;

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




int main() {
    string s;
    cin >> s;
    // limit = int(s.size());
    // logLimit = int(log2(limit) + 0.5);
    // limit = int(1); // logLimit = 0
    // limit = int(2); // logLimit = 1
    limit = 1;
    logLimit = 0;
    while (limit < s.size()) {
        limit <<= 1;
        logLimit += 1;
    }
    limit <<= 2;
    logLimit += 2;
    // limit <<= 3;
    // logLimit += 3;


    calcRev();
    calcZ();

    string reverseS = s;
    reverse(reverseS.begin(), reverseS.end());
    vector<Num> a1(limit), a2(limit), a3(limit);
    for (int i = 0; i < s.size(); i++) {
        a1[i] = Num(s[i] - '0');
        a2[i] = Num(s[i] - '0');
        a3[2 * i] = Num(reverseS[i] - '0');
    }

    auto fa1 = fft(a1);
    auto fa2 = fft(a2);
    auto fa3 = fft(a3);
    auto fc = vector<Num>(limit);
    for (int i = 0; i < limit; i++)
        fc[i] = fa1[i] * fa2[i] * fa3[i];

    auto c = fft(fc, true);
    vector<int> res(limit);
    for (int i = 0; i < limit; i++)
        res[i] = int(c[i].real() + 0.5);


    // for (int i = 0; i < limit; ++i) {
    //     cout << res[i] << " ";
    // }
    // cout << endl;


    long long sum = 0;
    sum = res[2 * (s.size() - 1)];
    // for (int i = s.size(); i < 2 * s.size(); ++i) {
    //     sum += res[i];
    // }
    for (int i = 0; i < s.size(); i++) {
        sum -= a1[i].real();
    }
    sum /= 2;

    cout << sum << endl;

    return 0;
}