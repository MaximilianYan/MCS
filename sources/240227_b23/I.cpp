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
    int m = 0;
    cin >> m;
    vector<vector<vector<Num>>> ss(2, vector<vector<Num>>(4, vector<Num>(m, 0)));

    for (int si = 0; si < 2; ++si) {
        for (int i = 0; i < m; ++i) {
            char in = 0;
            cin >> in;
            ss[si]
                [in == 'A' ? 0 : in == 'T' ? 1 : in == 'G' ? 2 : 3]
                [i] = Num(1);
        }
    }


    // string s;
    // cin >> s;

    limit = m;
    // logLimit = int(log2(limit) + 0.5);
    logLimit = int(log2(limit) + 0);
    // // limit = int(1); // logLimit = 0
    // // limit = int(2); // logLimit = 1
    // long long maxDegreeN = 4 * (s.size() - 1) + 1 + 100000;

    // limit = 1;
    // logLimit = 0;
    // while (limit < maxDegreeN) {
    //     // while (limit < s.size()) {
    //     limit <<= 1;
    //     logLimit += 1;
    // }
    // // limit <<= 2;
    // // logLimit += 2;
    // // limit <<= 3;
    // // logLimit += 3;


    calcRev();
    calcZ();

    for (int i = 0; i < 4; ++i)
        reverse(ss[1][i].begin(), ss[1][i].end());
    // string reverseS = s;
    // reverse(reverseS.begin(), reverseS.end());
    // vector<Num> a1(limit), a2(limit), a3(limit);
    // for (int i = 0; i < s.size(); i++) {
    //     a1[i] = Num(s[i] - '0');
    //     a2[i] = Num(s[i] - '0');
    //     a3[2 * i] = Num(reverseS[i] - '0');
    // }

    vector<vector<vector<Num>>> fas(2, vector<vector<Num>>(4));
    for (int si = 0; si < 2; ++si) {
        for (int i = 0; i < 4; ++i) {
            fas[si][i] = fft(ss[si][i]);
        }
    }
    // auto fa1 = fft(a1);
    // auto fa2 = fft(a2);
    // auto fa3 = fft(a3);
    vector<vector<Num>> fc(4, vector<Num>(limit));
    // auto fc = vector<Num>(limit);

    for (int li = 0; li < 4; ++li) {
        for (int i = 0; i < limit; i++)
            fc[li][i] = fas[0][li][i] * fas[1][li][i];
    }


    vector<vector<Num>> c(4, vector<Num>(limit));
    for (int i = 0; i < 4; ++i) {
        c[i] = fft(fc[i], true);
    }
    // auto c = fft(fc, true);

    vector<vector<int>> res(4, vector<int>(limit));
    for (int li = 0; li < 4; ++li)
        for (int i = 0; i < limit; i++)
            res[li][i] = int(c[li][i].real() + 0.5);

    vector<int> resSum(limit);
    for (int li = 0; li < 4; ++li)
        for (int i = 0; i < limit; i++)
            resSum[i] += res[li][i];
    // for (int i = 0; i < limit; ++i) {
    //     cout << res[i] << " ";
    // }
    // cout << endl;


    int max = -1;
    int maxShift = -1;

    for (int i = 0; i < limit; ++i) {
        if (resSum[i] > max) {
            max = resSum[i];
            maxShift = (i + 1) % limit;
        }
    }

    cout << max << " " << maxShift << endl;


    // long long sum = 0;
    // sum = res[2 * (s.size() - 1)];
    // // for (int i = s.size(); i < 2 * s.size(); ++i) {
    // //     sum += res[i];
    // // }
    // for (int i = 0; i < s.size(); i++) {
    //     sum -= a1[i].real();
    // }
    // sum /= 2;

    // cout << sum << endl;

    return 0;
}