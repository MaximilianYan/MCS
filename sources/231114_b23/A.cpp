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
    vector<int> ranks;
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
    cin.tie(0);
    ios_base::sync_with_stdio(false);

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

    vector<string> answer;
    for (int i = k - 1; i >= 0; --i) {
        if (quests[i].type == Op::Type::ASK)
            answer.push_back(dsu.ask(quests[i].edge) + "\n");
        if (quests[i].type == Op::Type::CUT)
            dsu.connect(quests[i].edge);
    }

    for (int i = answer.size() - 1; i >= 0; --i) {
        cout << answer[i];
    }

    return 0;
}

DSU::DSU(int n) : arcs(n, -1), ranks(n, 0) {
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
        cout << "WTF??" << endl;
    }

    arcs[u] = v;
    if (ranks[u] == ranks[v]) ranks[v]++;
    // sizes[v] += sizes[u];
    ranks[u] = -1;



    // int oldColor = colors[verts.u];
    // for (int& verColor : colors) {
    //     if (verColor == oldColor)
    //         verColor = colors[verts.v];
    // }
}

int DSU::root(int vert) {
    if (arcs[vert] == vert) return vert;
    return arcs[vert] = root(arcs[vert]);
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
