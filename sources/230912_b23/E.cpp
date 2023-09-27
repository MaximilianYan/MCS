/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230912_b23 изучаем язык
 * @date 2023-09-27
 */

#include <cstdio>

int main() {
    int counter[256] = {};
    char buffer[200] = {};

    scanf("%s", buffer);

    int maxC = 'a';

    for (int i = 0; buffer[i]; ++i) {
        ++counter[buffer[i]];
        if (counter[buffer[i]] > counter[maxC]) maxC = buffer[i];
    }

    printf("%c", maxC);
}
