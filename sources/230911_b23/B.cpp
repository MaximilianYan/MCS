#include <cstdio>

main() {
    long long n, s = 1;
    scanf("%d", &n);

    do
        printf("%d ", s);
    while ((s *= n) <= 1e9 & n > 1);
}
