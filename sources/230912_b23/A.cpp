/**
 * @file A.cpp
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230912_b23 изучаем язык
 * @date 2023-09-21
 */

#include <cstdio>

int abs(int a) {
    return a < 0 ? -a : a;
}

int mulsgn(int n, int sgn) {
    return sgn == 0 ? 0 : sgn < 0 ? -n : n;
}

int main() {
    int a = 0;
    int b = 0;
    int d = 0;

    scanf("%d %d %d", &a, &b, &d);

    int target = b - a;

    if (abs(target) <= d)
        printf("%d", b);
    else
        printf("%d", a + mulsgn(d, target));

}
