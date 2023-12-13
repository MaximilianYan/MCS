// basic treap: split, merge, insert, +remove
#include <iostream>
#include <random>
#include <utility>
#include <sstream>

using namespace std;

//random_device dev;
//mt19937 gen (dev ());
mt19937 gen(1234567890);

struct Node;
using PNode = Node*;
struct Node
{
    int x;
    int y;
    PNode left;
    PNode right;

    Node(int x_) {
        x = x_;
        y = uniform_int_distribution <int>(0, 1E9) (gen);
        left = nullptr;
        right = nullptr;
    }

    int value;
};

PNode tFind(PNode t, int x) {
    if (t == nullptr) {
        return nullptr;
    }
    if (t->x == x) {
        return t;
    }
    if (t->x < x) {
        return tFind(t->right, x);
    } else {
        return tFind(t->left, x);
    }
}

void tOutputRecur(PNode t) {
    if (t == nullptr) {
        return;
    }
    cout << "(";
    tOutputRecur(t->left);
    cout << t->x;
    tOutputRecur(t->right);
    cout << ")";
}

void tOutput(PNode t) {
    tOutputRecur(t);
    cout << endl;
}

pair <PNode, PNode> tSplit(PNode t, int x) { // first: < x ; second: >= x
    if (t == nullptr) {
        return { nullptr, nullptr };
    }
    if (t->x < x) {
        auto temp = tSplit(t->right, x);
        t->right = temp.first;
        return { t, temp.second };
    } else {
        auto temp = tSplit(t->left, x);
        t->left = temp.second;
        return { temp.first, t };
    }
}

PNode tMerge(PNode l, PNode r) {
    if (l == nullptr) {
        return r;
    }
    if (r == nullptr) {
        return l;
    }
    if (l->y > r->y) {
        l->right = tMerge(l->right, r);
        return l;
    } else {
        r->left = tMerge(l, r->left);
        return r;
    }
}

PNode tInsert(PNode t, int x, int value) {
    auto temp = tSplit(t, x);
    auto v = new Node(x);
    v->value = value;
    // (temp.first | v) | temp.second
    auto half = tMerge(temp.first, v);
    return tMerge(half, temp.second);
}

void tDelete(PNode t) {
    if (t == nullptr) {
        return;
    }
    tDelete(t->left);
    tDelete(t->right);
    delete t;
}

PNode tRemove(PNode t, int x) {
    auto one = tSplit(t, x);
    auto two = tSplit(one.second, x + 1);
    // TODO one.first | two.first | two.second
    tDelete(two.first);
    return tMerge(one.first, two.second);
}

void funcPtr(PNode& root, PNode actual, int l, int k);

void funcNext(PNode& root, PNode prev, int l, int k) {
    PNode actual = nullptr;
    if (prev->right) {
        actual = prev->right;
        while (actual->left) actual = actual->left;
        if (actual->x != prev->x + 1)
            actual = nullptr;
    } else {
        actual = tFind(root, l);
    }
    funcPtr(root, actual, l, k);
}

void func(PNode& root, int l, int k) {
    PNode actual = tFind(root, l);
    funcPtr(root, actual, l, k);
}

void funcPtr(PNode& root, PNode actual, int l, int k) {
    if (!actual) {
        root = tInsert(root, l, k);
    } else {
        funcNext(root, actual, l + 1, actual->value);
        actual->value = k;
    }
}

void tOutputRecurB(PNode t, int& i, int& max, stringstream& output) {
    if (t == nullptr) {
        return;
    }
    // cout << "(";
    tOutputRecurB(t->left, i, max, output);
    while (i++ < t->x) output << "0 ";
    output << t->value << " ";
    max = t->x;
    tOutputRecurB(t->right, i, max, output);
    // cout << ")";
}

int main() {
    int n = 0, m = 0;
    cin >> n >> m;

    PNode root = nullptr;

    for (int i = 1; i <= n; ++i) {
        int l = 0;
        cin >> l;
        func(root, l, i);
    }

    int i = 1;
    int max = 0;
    stringstream output;
    tOutputRecurB(root, i, max, output);
    cout << max << endl << output.str() << endl;

    // 	int const size = 1000000; // test for speed
    // 	PNode root = nullptr;
    // 	tOutput (root);
    // 	for (int i = 1; i <= size * 2; i += 2)
    // 	{
    // 		root = tInsert (root, i);
    // //		tOutput (root); // set size to 10 and then uncomment
    // 	}
    // 	for (int i = 1; i <= size; i++)
    // 	{
    // //		cout << tFind (root, i); // set size to 10 and then uncomment
    // 		tFind (root, i);
    // 	}
    // 	for (int i = 1; i <= size * 2; i += 2)
    // 	{
    // 		if (size * 2 - i == 111) tOutput (root);
    // 		root = tRemove (root, i);
    // //		tOutput (root); // set size to 10 and then uncomment
    // 		if (size * 2 - i == 111) tOutput (root);
    // 	}


    return 0;
}
