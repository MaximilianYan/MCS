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

    int count = 0;

    for (int pos = 0; pos < n; ++pos)
        count += sequence[pos] < sequence[0];

    printf("%d", count + 1);
}
