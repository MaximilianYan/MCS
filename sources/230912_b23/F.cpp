/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230912_b23 изучаем язык
 * @date 2023-09-27
 */

#include <cstdio>

int main() {
    int mask[256] = {};
    char bufferS[200] = {};
    char bufferT[200] = {};

    scanf("%s", bufferS);
    scanf("%s", bufferT);

    for (int i = 0; bufferT[i]; ++i) {
        mask[bufferT[i]] = 1;
    }


    for (int i = 0; bufferS[i]; ++i) {
        if (!mask[bufferS[i]]) printf("%c", bufferS[i]);
    }
}
