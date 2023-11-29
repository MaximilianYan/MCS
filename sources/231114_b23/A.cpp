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
};

class DSU {
public:
    DSU(int n);

    string ask(Edge verts);
    void connect(Edge verts);

private:
    int root(int vert);

    vector<int> arcs;
};

class Op {
public:
    Op();
    friend istream& operator>>(istream& input, Op& ro);

    enum Type {
        CUT,
        ASK,
    };

    Type type;
    Edge edge;
};

int main() {
    int n = 0, m = 0, k = 0;
    cin >> n >> m >> k;

    DSU dsu(n);
    vector<Op> quests(k);

    for (int i = 0; i < m; ++i) {
        int u = 0, v = 0;
        cin >> u >> v;
    }

    for (int i = 0; i < k; ++i) {
        cin >> quests[i];
    }

    string answer = "";
    for (int i = k - 1; i >= 0; --i) {
        if (quests[i].type == Op::Type::ASK)
            answer = dsu.ask(quests[i].edge) + "\n" + answer;
        if (quests[i].type == Op::Type::CUT)
            dsu.connect(quests[i].edge);
    }

    cout << answer;

    return 0;
}

DSU::DSU(int n) : arcs(n, -1) {
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

    arcs[u] = v;



    // int oldColor = colors[verts.u];
    // for (int& verColor : colors) {
    //     if (verColor == oldColor)
    //         verColor = colors[verts.v];
    // }
}

Op::Op() : type(ASK), edge({ -1, -1 }) {}

istream& operator>>(istream& input, Op& ro) {
    string command = "";
    cin >> command;

    if (command == "cut")
        ro.type = Op::Type::CUT;
    if (command == "ask")
        ro.type = Op::Type::ASK;

    cin >> ro.edge.u >> ro.edge.v;
    ro.edge.u--;
    ro.edge.v--;

    return input;
}

int DSU::root(int vert) {
    if (arcs[vert] == vert) return vert;
    return arcs[vert] = root(arcs[vert]);
}
