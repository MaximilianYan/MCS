/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230919_b23 библиотека C++
 * @date 2023-10-04
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int sgn(int a) {
    return a < 0 ? -1 : a > 0 ? 1 : 0;
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
        cout << a + d * sgn(target) << endl;

}
