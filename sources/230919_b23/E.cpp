/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230919_b23 библиотека C++
 * @date 2023-10-04
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    int counter[256] = {};
    string buffer;

    cin >> buffer;
    int maxC = 'a';

    transform(buffer.begin(), buffer.end(), buffer.begin(), [&counter, &maxC](const char a) {
        ++counter[a];
        if (counter[a] > counter[maxC]) maxC = a;
        return a;
    });

    cout << (char)maxC << endl;

    //------------------------------------------

}
