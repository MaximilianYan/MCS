/**
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief 230912_b23 изучаем язык
 * @date 2023-09-21
 */

#include <cstdio>

int main() {
    long long int input = 0;
    scanf("%d", &input);

    long long int n = 0;
    long long int factor = 1;
    while (input) {
        n += (input % 5) * factor;
        factor *= 5;
        input /= 10;
    }

    // prlong long intf("debug number : %d\n", n);

    long long int sum = 0;
    for (sum = 0; n; sum += n % 7, n /= 7);

    long long int out[19] = {};
    long long int numC = 0;

    while (sum) {
        out[numC++] = sum % 3;
        sum /= 3;
    }

    while ((--numC) >= 0) {
        printf("%d", out[numC]);
    }

}
