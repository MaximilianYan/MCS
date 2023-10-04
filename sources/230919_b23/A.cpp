/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230919_b23 библиотека C++
 * @date 2023-10-04
 */

#include <iostream>
#include <vector>

using namespace std;

int abs(int a) {
    return a < 0 ? -a : a;
}

int mulsgn(int n, int sgn) {
    return sgn == 0 ? 0 : sgn < 0 ? -n : n;
}

int main() {
    int a = 0;
    int b = 0;
    int d = 0;

    cin >> a >> b >> d;

    int target = b - a;

    if (abs(target) <= d)
        cout << b << endl;
    else
        cout << a + mulsgn(d, target) << endl;

}
