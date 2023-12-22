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
    bool isDual();
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

    void addBadEnd();
    void deleteBadEnd();

    bool isSingle();

    void eraseThis(Node*& node);

private:
    Node* root;

    bool hasBadEnd;
};

int main() {
    string str;
    cin >> str;

    Root root;
    for (int pos = 0; pos < str.length(); ++pos) {
        Node* add = new Node(pos);

        root <<= *add;
    }

    root.addBadEnd();

    Node* ans = nullptr;

    for (int i1 = 0; i1 < str.length(); ++i1) {
        char minc = 'z';

        for (Node* pos = root.begin(); pos != root.end(); pos = pos->getR()) {
            minc = min(minc, str[(*pos)() + i1]);
        }

        for (Node* pos = root.begin(); pos != root.end(); pos = pos->getR()) {
            if (str[(*pos)() + i1] != minc) {
                root.eraseThis(pos);

                continue;
            }
            if ((*pos)() + i1 == str.length()) {
                ans = pos;
                goto endOfFor;
            }
        }

        if (root.isSingle()) {
            ans = root.begin();
            break;
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

bool Node::isDual() {
    return left == right;
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

Root::Root() : root(nullptr), hasBadEnd(false) {}

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
    return root;
}

Node* Root::end() {
    if (hasBadEnd)
        return root->getL();
    return nullptr;
}

void Root::addBadEnd() {
    if (hasBadEnd) return;

    *root <<= *(new Node(-239));

    hasBadEnd = true;
}

void Root::deleteBadEnd() {
    if (!hasBadEnd) return;

    delete root->getL();

    hasBadEnd = false;
}

bool Root::isSingle() {
    if (hasBadEnd) {
        return root->isDual();
    } else {
        return root->isSingle();
    }
}

void Root::eraseThis(Node*& node) {
    // if (hasBadEnd) {
    //     if (node == end()) {
    //         cout << "ERR: " << __LINE__ << endl;
    //     }
    // }
    if (isSingle()) {
        if (node != root) {
            cout << "ERR: " << __LINE__ << endl;
            return;
        }

        deleteBadEnd();
        delete root;
        root = nullptr;
        return;
    }

    Node* oldLeft = node->getL();
    Node* old = node;
    node = oldLeft;

    if (root == old) root = old->getR();

    delete old;
}
