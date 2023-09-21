/**
 * @file A.cpp
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230912_b23 изучаем язык
 * @date 2023-09-21
 */

#include <cstdio>

int main() {
    long long int n = 0;
    scanf("%d", &n);

    if (n == 1) printf("1");
    else
        for (long long int s = 1; s <= 1e9; s *= n)
            printf("%d ", s);

}
