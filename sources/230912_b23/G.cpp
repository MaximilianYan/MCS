/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230912_b23 изучаем язык
 * @date 2023-09-27
 */

#include <cstdio>

int main() {
    int counter[256] = {};
    char buffer[200] = {};
    int kFilter = 0;

    scanf("%s", buffer);
    scanf("%d", &kFilter);

    for (int i = 0; buffer[i]; ++i) {
        ++counter[buffer[i]];
    }

    for (char i = 'a'; i <= 'z'; ++i)
        if (counter[i] >= kFilter)
            printf("%c ", i);
}
