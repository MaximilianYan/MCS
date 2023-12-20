#include <iostream>
#include <random>
#include <functional>
#include <utility>
#include <string>
#include <sstream>
#include <stdint.h>
#include <set>

using namespace std;

class Edge {
public:
    Edge();
    Edge(int v1, int v2);

    friend istream& operator>>(istream& input, Edge& ro);
    friend bool operator<(const Edge& lo, const Edge& ro);

    static set<Edge>::iterator iteratorLowerBound(set<Edge>& arr, int v1);

public:
    int v1;
    int v2;

private:
    void normalise();
};

int main() {
    int n = 0, m = 0;
    cin >> n >> m;

    set<Edge> edges;

    for (int _ = 0; _ < m; ++_) {
        Edge edge;
        cin >> edge;
        edges.emplace(edge);
    }

    int ans = 0;

    auto x1 = Edge::iteratorLowerBound(edges, 0);
    auto x2 = Edge::iteratorLowerBound(edges, 1);
    auto x3 = Edge::iteratorLowerBound(edges, 2);
    auto x4 = Edge::iteratorLowerBound(edges, 3);

    for (int i = 0; i < n; ++i) {
        for (auto edge1 = Edge::iteratorLowerBound(edges, i); edge1 != Edge::iteratorLowerBound(edges, i + 1); ++edge1) {
            for (auto edge2 = edge1; ++edge2 != Edge::iteratorLowerBound(edges, i + 1);) {
                Edge ed = Edge(edge1->v2, edge2->v2);
                ans += (edges.count(ed));
            }
        }
    }

    cout << ans << endl;

    return 0;
}

Edge::Edge() : v1(-1), v2(-1) {}
Edge::Edge(int v1, int v2) : v1(v1), v2(v2) {
    normalise();
}

void Edge::normalise() {
    if (v1 <= v2) return;

    swap(v1, v2);
}

istream& operator>>(istream& input, Edge& ro) {
    input >> ro.v1 >> ro.v2;
    --ro.v1;
    --ro.v2;
    ro.normalise();
    return input;
}

bool operator<(const Edge& lo, const Edge& ro) {
    if (lo.v1 < ro.v1) return true;
    if (lo.v1 > ro.v1) return false;
    if (lo.v2 < ro.v2) return true;
    if (lo.v2 > ro.v2) return false;
    return false;
}

set<Edge>::iterator Edge::iteratorLowerBound(set<Edge>& arr, int v1) {
    return arr.lower_bound(Edge(v1, v1));
}
