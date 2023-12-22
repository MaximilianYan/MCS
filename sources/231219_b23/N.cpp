#include <iostream>
#include <random>
#include <functional>
#include <utility>
#include <string>
#include <sstream>
#include <stdint.h>

using namespace std;

class Node {
public:
    Node(int value = 0);
    ~Node();

    void extract();
    bool isSingle();
    void operator<<=(Node& ro);
    void operator>>=(Node& ro);

    Node* getR();
    Node* getL();

    int operator()();

private:
    Node* left;
    Node* right;

    int value;

    static void normaliseConnections(Node* left, Node* center, Node* right);
};

class Root {
public:
    Root();
    ~Root();

    void operator<<=(Node& ro);

    Node* begin();
    Node* end();

private:
    Node* root;

    bool forFlag;
};

int main() {
    string str;
    cin >> str;

    vector<int> field(str.length(), 0);

    Root root;
    for (int pos = 0; pos < str.length(); ++pos) {
        Node* add = new Node(pos);

        root <<= *add;
    }

    Node* ans = nullptr;

    for (int i1 = 0; i1 < str.length(); ++i1) {
        char minc = 'z';
        // for (int pos = 0; pos < str.length() - i1; ++pos) {
        //     if (field[pos] == i1)
        //         minc = min(minc, str[pos + field[pos]]);
        // }
        for (Node* pos = root.begin(); pos != root.end(); pos = pos->getR()) {
            if (field[(*pos)()] == i1)
                minc = min(minc, str[(*pos)() + field[(*pos)()]]);
        }

        // for (int pos = 0; pos < str.length() - i1; ++pos) {
        //     if (field[pos] == i1) {
        //         if (str[pos + field[pos]] == minc) {
        //             field[pos] += 1;
        //         }
        //     }
        // }
        for (Node* pos = root.begin(); pos != root.end(); pos = pos->getR()) {
            if (field[(*pos)()] == i1) {
                if (str[(*pos)() + field[(*pos)()]] == minc) {
                    field[(*pos)()] += 1;
                }
            }
            if ((*pos)() + field[(*pos)()] == str.length()) {
                ans = pos;
                goto endOfFor;
            }
        }
    }
endOfFor:

    for (int pos = (*ans)(); pos < str.length(); ++pos) {
        cout << str[pos];
    }
    cout << endl;

    return 0;
}

Node::Node(int value) : left(this), right(this), value(value) {}

Node::~Node() {
    extract();
}

void Node::extract() {
    Node* oldLeft = left;
    Node* oldRight = right;

    oldLeft->right = oldRight;
    oldRight->left = oldLeft;

    left = this;
    right = this;
}

bool Node::isSingle() {
    if (
        (left == this && left != right) ||
        (right == this && left != right)) {
        cout << "ERR:: " << __LINE__ << endl;
    }
    return left == this;
}

void Node::operator<<=(Node& ro) {
    ro.extract();

    Node* oldLeft = left;
    Node* oldRight = this;

    normaliseConnections(oldLeft, &ro, oldRight);
}

void Node::operator>>=(Node& ro) {
    ro.extract();

    Node* oldLeft = this;
    Node* oldRight = right;

    normaliseConnections(oldLeft, &ro, oldRight);
}

Node* Node::getR() {
    return right;
}
Node* Node::getL() {
    return left;
}

int Node::operator()() {
    return value;
}

void Node::normaliseConnections(Node* left, Node* center, Node* right) {
    left->right = center;
    right->left = center;

    center->left = left;
    center->right = right;
}

Root::Root() : root(nullptr) {}

Root::~Root() {
    while (!root->isSingle()) {
        delete root->getR();
    }
    delete root;
    root = nullptr;
}

void Root::operator<<=(Node& ro) {
    if (!root) root = &ro;
    else *root <<= ro;
}

Node* Root::begin() {
    forFlag = true;
    return root;
}

Node* Root::end() {
    if (forFlag) {
        forFlag = false;
        return nullptr;
    }
    return root;
}
