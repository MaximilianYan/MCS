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

    for (int pos = 0; pos < n / 2; ++pos) {
        int minC = 0;
        for (int i = 0; i < n / 2; ++i)
            if (sequence[i] < sequence[minC]) minC = i;

        printf("%d ", sequence[minC]);
        sequence[minC] = 2147483647;
    }

    for (int pos = n / 2; pos < n; ++pos) {
        int maxC = n / 2;
        for (int i = n / 2; i < n; ++i)
            if (sequence[i] > sequence[maxC]) maxC = i;

        printf("%d ", sequence[maxC]);
        sequence[maxC] = -1;
    }
}
