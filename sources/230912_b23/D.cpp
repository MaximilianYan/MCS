/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230912_b23 изучаем язык
 * @date 2023-09-27
 */

#include <cstdio>

int main() {
    long long int l = 0;
    long long int r = 0;
    long long int d = 0;
    scanf("%lld %lld %lld", &l, &r, &d);

    long long int i = l - l % d;
    if (i < l) i += d;
    while (i <= r) {
        printf("%lld ", i);
        i += d;
    }
}
