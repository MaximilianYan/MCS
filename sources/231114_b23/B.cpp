#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <list>
#include <sstream>
#include <string>

using namespace std;

class Edge {
public:
    int u;
    int v;

    friend istream& operator>>(istream& input, Edge& ro);
};

class DSU {
public:
    DSU(int n);

    string ask(Edge verts);
    void connect(Edge verts);

    bool isDic() const;
private:
    int root(int vert);

    vector<int> arcs;
    vector<int> ranks;
    int conCom;
};

int main() {
    int n = 0, m = 0;
    cin >> n >> m;

    DSU dsu(n);

    cout.tie(0);

    for (int i = 0; i < m; ++i) {
        Edge edge;
        cin >> edge;

        dsu.connect(edge);

        cout << dsu.isDic() ? 1 : 0;
    }

    return 0;
}

DSU::DSU(int n) : arcs(n, -1), ranks(n, 0), conCom(n) {
    iota(arcs.begin(), arcs.end(), 0);
}

string DSU::ask(Edge verts) {
    stringstream res;

    if (root(verts.u) == root(verts.v)) {
        res << "YES";
    } else {
        res << "NO";
    }

    return res.str();
}

void DSU::connect(Edge verts) {
    if (root(verts.u) == root(verts.v)) return;

    int u = root(verts.u);
    int v = root(verts.v);

    if (ranks[u] > ranks[v])
        swap(u, v);

    if (ranks[u] == -1 ||
        ranks[v] == -1) {
        cout << "WTF?? < " << __LINE__ << endl;
    }

    arcs[u] = v;
    if (ranks[u] == ranks[v]) ranks[v]++;
    // sizes[v] += sizes[u];
    ranks[u] = -1;
    --conCom;

    if (conCom <= 0) cout << "WTF?? < " << __LINE__ << endl;


    // int oldColor = colors[verts.u];
    // for (int& verColor : colors) {
    //     if (verColor == oldColor)
    //         verColor = colors[verts.v];
    // }
}

bool DSU::isDic() const {
    return conCom == 2;
    ;
}

int DSU::root(int vert) {
    if (arcs[vert] == vert) return vert;
    return arcs[vert] = root(arcs[vert]);
}

istream& operator>>(istream& input, Edge& ro) {
    cin >> ro.u >> ro.v;
    ro.u--;
    ro.v--;

    return input;
}
