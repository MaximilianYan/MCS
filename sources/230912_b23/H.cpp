/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230912_b23 изучаем язык
 * @date 2023-09-27
 */

#include <cstdio>

int main() {
    int n = 0;
    int sequence[200] = {};

    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", sequence + i);

    int maxC = 0;
    int maxN = 0;

    for (int pos = 0; pos < n; ++pos) {
        int counter = 0;

        for (int i = 0; i < n; ++i)
            counter += sequence[i] == sequence[pos];

        if (counter > maxC) {
            maxC = counter;
            maxN = sequence[pos];
        }
    }

    printf("%d", maxN);
}
