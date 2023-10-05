#include <iostream>

main() {
    int a, b, d;
    std::cin >> a >> b >> d;

    std::cout << (abs(a-b)<d ? b : a+(a<b?d:-d));
}
