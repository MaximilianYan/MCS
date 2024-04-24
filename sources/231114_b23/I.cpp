#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int LIMIT = 100001;

int getMin(const vector<int>& minTree, int l, int r, int N, int log2N, int level = 0) {
    // minTree[i] = min(minTree[(i << 1) + 0], minTree[(i << 1) + 1]);

    if (level == log2N - 1) return minTree[(1 << level) - 1 + l];

    int segSize = N >> level;
    if (l % segSize == 0) {
        if (r < l + segSize - 1) {
            return getMin(minTree, l, r, N, log2N, level + 1);
        }
        if (r > l + segSize - 1) {
            return min(
                minTree[(1 << level) - 1 + l / segSize],
                getMin(minTree, l + segSize, r, N, log2N, level + 1)
            );
        }
        return minTree[(1 << level) - 1 + l / segSize];
    }
    if ((r + 1) % segSize == 0) {
        if (l > r - segSize + 1) {
            return getMin(minTree, l, r, N, log2N, level + 1);
        }
        if (l < r - segSize + 1) {
            return min(
                getMin(minTree, l, r - segSize, N, log2N, level + 1),
                minTree[(1 << level) - 1 + (r + 1) / segSize - 1]
            );
        }
        cout << "VTm?!" << endl;
    }

    return min(
        getMin(minTree, l, r / segSize * segSize - 1, N, log2N, level + 1),
        getMin(minTree, r / segSize * segSize, r, N, log2N, level + 1)
    );
}

int main() {
    int n = 0, m = 0;
    cin >> n >> m;

    int N = 1;
    int log2N = 1;
    while (N < n) {
        N <<= 1;
        log2N += 1;
    }

    vector<int> arr(N, 0);

    for (int i = 1; i < n; ++i) {
        cin >> arr[i];
    }
    for (int i = n; i < N; ++i) {
        arr[i] = LIMIT;
    }

    vector<int> minTree(2 * N, -1);
    {
        for (int level = log2N - 1; level >= 0; --level) {
            int shift = (1 << level) - 1;
            for (int i = shift; i < shift + (1 << level); ++i) {
                if (level == log2N - 1) minTree[i] = arr[i - shift];
                else minTree[i] = min(minTree[(i << 1) + 0], minTree[(i << 1) + 1]);
            }
        }
    }

    int k = 0, l = 0;
    while (m--) {
        cin >> k >> l;
        cout << getMin(minTree, k - 1, l - 1, N, log2N) << endl;
    }

}
