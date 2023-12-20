#include <iostream>
#include <random>
#include <functional>
#include <utility>
#include <string>
#include <sstream>
#include <stdint.h>
#include <set>
#include <queue>

using namespace std;

class Vertex {
public:
    Vertex();
    Vertex(int v);

    friend istream& operator>>(istream& input, Vertex& ro);
    friend ostream& operator<<(ostream& output, const Vertex& ro);

    operator int() const;

private:
    int v;
};

class Edge {
public:
    Edge();
    Edge(int v1, int v2);

    friend istream& operator>>(istream& input, Edge& ro);
    friend bool operator<(const Edge& lo, const Edge& ro);

    static set<Edge>::iterator iteratorLowerBound(const set<Edge>& arr, int v1);

    const int& getV1() const;
    const int& getV2() const;

    Edge operator-() const;

private:
    int v1;
    int v2;

private:
    void normalise();
};

void bfsout(int& r, stringstream& output, const vector<vector<Vertex>>& edges, Vertex start) {
    queue<Vertex> vertexes;
    vector<bool> bfsed(edges.size(), false);

    vertexes.emplace(start);
    bfsed[start] = true;

    while (!vertexes.empty()) {
        output << vertexes.front() << " ";
        ++r;

        for (Vertex vertex : edges[vertexes.front()]) {
            if (!bfsed[vertex]) {
                bfsed[vertex] = true;
                vertexes.emplace(vertex);
            }
        }

        vertexes.pop();
    }
}

void dfsout(int& r, stringstream& output, const vector<vector<Vertex>>& edges, Vertex start) {
    static vector<bool> bfsed(edges.size(), false);

    bfsed[start] = true;

    output << start << " ";
    ++r;

    for (Vertex vertex : edges[start]) {
        if (!bfsed[vertex]) {
            bfsed[vertex] = true;
            dfsout(r, output, edges, vertex);
            output << start << " ";
            ++r;
        }
    }

}

int main() {
    int n = 0, m = 0;
    Vertex v;
    cin >> n >> m >> v;

    // set<Edge> edges;
    vector<vector<Vertex>> edges(n);

    for (int _ = 0; _ < m; ++_) {
        Edge edge;
        cin >> edge;
        // edges.emplace(edge);
        edges[edge.getV1()].emplace_back(edge.getV2());
        edges[edge.getV2()].emplace_back(edge.getV1());
    }

    int r = 0;
    stringstream ans;
    dfsout(r, ans, edges, v);

    cout << r << endl << ans.str() << endl;

    return 0;
}

Vertex::Vertex() : v(0) {}

Vertex::Vertex(int v) : v(v) {}

istream& operator>>(istream& input, Vertex& ro) {
    input >> ro.v;
    --ro.v;
    return input;
}

ostream& operator<<(ostream& output, const Vertex& ro) {
    return output << ro.v + 1;
}

Vertex::operator int() const {
    return v;
}


Edge::Edge() : v1(-1), v2(-1) {}
Edge::Edge(int v1, int v2) : v1(v1), v2(v2) {
    normalise();
}

void Edge::normalise() {
    if (v1 <= v2) return;

    // swap(v1, v2);
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

set<Edge>::iterator Edge::iteratorLowerBound(const set<Edge>& arr, int v1) {
    return arr.lower_bound(Edge(v1, v1));
}

const int& Edge::getV1() const {
    return v1;
}
const int& Edge::getV2() const {
    return v2;
}

Edge Edge::operator-() const {
    return Edge(getV2(), getV1());
}
