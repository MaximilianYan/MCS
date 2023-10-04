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
    int mask[256] = {};
    string bufferS;
    string bufferT;

    cin >> bufferS >> bufferT;

    transform(bufferT.begin(), bufferT.end(), bufferT.begin(), [&mask](const char a) {
        mask[a] = true;
        return a;
    });
    transform(bufferS.begin(), bufferS.end(), bufferS.begin(), [&mask](const char a) {
        if (!mask[a]) cout << (char)a;
        return a;
    });

    //------------------------------------------
}
