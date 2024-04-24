#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    int n = 0, m = 0;
    cin >> n >> m;

    vector<long long> pref(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        int a = 0;
        cin >> a;
        pref[i] = pref[i - 1] + a;
    }

    int k = 0, l = 0;
    while (m--) {
        cin >> k >> l;
        cout << pref[l] - pref[k - 1] << endl;
    }

}
