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
    vector<int> counter(256, 0);
    string buffer;
    int kFilter = 0;

    cin >> buffer >> kFilter;

    transform(buffer.begin(), buffer.end(), buffer.begin(), [&counter](const char a) {
        ++counter[a];
        return a;
    });
    char ch = 0;
    transform(counter.begin(), counter.end(), counter.begin(), [kFilter, &ch](const int count) {
        if (ch >= 'a' && ch <= 'z') if (count >= kFilter) cout << (char)(ch) << ' ';
        ++ch;
        return count;
    });

    //------------------------------------------
}
