#include <iostream>
#include <random>
#include <functional>
#include <utility>
#include <string>
#include <sstream>
#include <stdint.h>
#include <set>
#include <queue>
#include <iomanip>

using namespace std;

const int LIMIT = 1e7;

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
    Edge(int v1, int v2, double w);

    friend istream& operator>>(istream& input, Edge& ro);
    friend bool operator<(const Edge& lo, const Edge& ro);

    // static set<Edge>::iterator iteratorLowerBound(const set<Edge>& arr, int v1);

    const int& getV1() const;
    const int& getV2() const;
    const double& getW() const;

    Edge operator-() const;

private:
    int v1;
    int v2;
    double w;

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

int bfsfind(const vector<vector<Vertex>>& edges, Vertex start, Vertex finish) {
    queue<Vertex> vertexes;
    vector<int> length(edges.size(), numeric_limits<int>::max());
    vector<bool> bfsed(edges.size(), false);

    vertexes.emplace(start);
    length[start] = 0;
    bfsed[start] = true;

    while (!vertexes.empty()) {
        if (vertexes.front() == finish) {
            return length[finish];
        }

        for (Vertex vertex : edges[vertexes.front()]) {
            if (!bfsed[vertex]) {
                bfsed[vertex] = true;
                length[vertex] = length[vertexes.front()] + 1;
                vertexes.emplace(vertex);
            }
        }

        vertexes.pop();
    }

    return -1;
}

// double max(const double& lo, const double& ro) {
//     if (lo >= ro) return lo;
//     return ro;
// }

int main() {

    // vector<vector<long long int>> field(n, vector<long long int>(n, 1e9));
    // for (int i = 0; i < n; ++i)
    //     field[i][i] = 0;

    // for (int i = 0; i < m; ++i) {
    //     int a = 0, b = 0, l = 0;
    //     cin >> a >> b >> l;

    //     field[a - 1][b - 1] = l;
    // }

    // for (int k = 0; k < n; ++k)
    //     for (int i = 0; i < n; ++i)
    //         for (int j = 0; j < n; ++j) {
    //             if (field[i][j] > field[i][k] + field[k][j])
    //                 field[i][j] = field[i][k] + field[k][j];
    //         }

    // long long int minSum = 1e9;
    // int minI = -1;
    // for (int k = 0; k < n; ++k) {
    //     long long int sum = 0;
    //     for (int i = 0; i < n; ++i) {
    //         sum += field[k][i];
    //     }

    //     if (sum < minSum) {
    //         minSum = sum;
    //         minI = k;
    //     }
    // }

    // cout << minI + 1 << " " << minSum << endl;

    int n = 0, m = 0;
    Vertex start, finish;

    cin >> n;// >> m;
    cin >> start >> finish;

    vector<vector<Edge>> edges(n, vector<Edge>());

    for (int i = 0; i < n; ++i) {
        Edge e(i, i, 1.0);
        edges[i].emplace_back(e);
    }

    // vector<vector<long long int>> field(n, vector<long long int>(n, 1e9));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            int l = -239;
            cin >> l;
            if (l > -1) edges[i].emplace_back(i, j, l);
        }
    // for (int i = 0; i < m; ++i) {
    //     Edge edge;
    //     cin >> edge;
    //     edges[edge.getV1()].emplace_back(edge);
    //     edges[edge.getV2()].emplace_back(-edge);
    // }

    vector<vector<double>> field(n, vector<double>(n, 1e9));

    field[start][start] = 0;

    vector<bool> reached(n, false);

    while (true) {
        Vertex next(-1);

        double maxD = 1e9;
        for (int i = 0; i < n; ++i) {
            if (!reached[i])
                if (field[start][i] < maxD) {
                    next = i;
                    maxD = field[start][i];
                }
        }

        if (next == -1) break;
        reached[next] = true;

        for (Edge edge : edges[next]) {
            field[start][edge.getV2()] = min(field[start][edge.getV2()], field[start][next] + edge.getW());
        }
    }

    cout << (int)(field[start][finish] == 1e9 ? -1 : field[start][finish]) << endl;

    // vector<vector<Vertex>> edges(n);

    // for (int i = 0; i < n; ++i) {
    //     for (int _ = 0; _ < 3; ++_) {
    //         Vertex connected;
    //         cin >> connected;
    //         Edge edge(i, connected);
    //         edges[edge.getV1()].emplace_back(edge.getV2());
    //     }
    // }

    // cout << bfsfind(edges, x, y) << endl;


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
Edge::Edge(int v1, int v2, double w) : v1(v1), v2(v2), w(w) {
    normalise();
}

void Edge::normalise() {
    if (v1 <= v2) return;

    // swap(v1, v2);
}

istream& operator>>(istream& input, Edge& ro) {
    input >> ro.v1 >> ro.v2 >> ro.w;
    --ro.v1;
    --ro.v2;
    // ro.w = 1.0 - ro.w / 100.0;
    // ro.normalise();
    return input;
}

bool operator<(const Edge& lo, const Edge& ro) {
    if (lo.v1 < ro.v1) return true;
    if (lo.v1 > ro.v1) return false;
    if (lo.v2 < ro.v2) return true;
    if (lo.v2 > ro.v2) return false;
    return false;
}

// set<Edge>::iterator Edge::iteratorLowerBound(const set<Edge>& arr, int v1) {
//     return arr.lower_bound(Edge(v1, v1));
// }

const int& Edge::getV1() const {
    return v1;
}
const int& Edge::getV2() const {
    return v2;
}
const double& Edge::getW() const {
    return w;
}


Edge Edge::operator-() const {
    return Edge(getV2(), getV1(), getW());
}
