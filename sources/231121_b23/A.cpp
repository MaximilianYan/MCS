#include <iostream>
#include <random>
#include <functional>

using namespace std;

typedef int Value_t;
typedef int X_t;
typedef int Y_t;

class DTree {
public:
    DTree();

    void insert(Value_t value, X_t x, Y_t y);

    friend ostream& operator<<(ostream& output, DTree& ro);

private:
    class Node {
    public:
        Node(Value_t value, X_t x, Y_t y);
        // Node(Value_t value);

        // Node* getLeft() const;
        // Node* getRight() const;

        /// @brief Comaring lo.x with ro.x
        friend bool operator<=(const DTree::Node& lo, const DTree::Node& ro);
        /// @brief Comaring lo.x with ro.x
        friend bool operator>(const DTree::Node& lo, const DTree::Node& ro);
        /// @brief Comaring lo.y with ro.y
        friend bool operator<<=(const DTree::Node& lo, const DTree::Node& ro);
        /// @brief Comaring lo.y with ro.y
        friend bool operator>>(const DTree::Node& lo, const DTree::Node& ro);

        Node* left;
        Node* right;
        Value_t value;
    private:
        X_t x;
        Y_t y;

    };
    friend bool operator<=(const DTree::Node& lo, const DTree::Node& ro);
    friend bool operator>(const DTree::Node& lo, const DTree::Node& ro);
    friend bool operator<<=(const DTree::Node& lo, const DTree::Node& ro);
    friend bool operator>>(const DTree::Node& lo, const DTree::Node& ro);

    DTree(Node* nodePtr);
    operator Node* ();
    operator Node const* () const;
    bool operator==(Node const* const& ro) const;
    bool operator==(const std::nullptr_t& ro) const;
    bool operator!() const;

    Node*& left() const;
    Node*& right() const;

    // void tempInsert(Node* newNode);

    /// @brief merge
    friend DTree operator+(const DTree& lo, const DTree& ro);

    /// @brief dfs callback function type
    typedef function<void(Value_t, void*)> DfsCBFunc_t;
    /// @brief Deep-first tree bypass
    void dfs(DfsCBFunc_t preorder, DfsCBFunc_t inorder, DfsCBFunc_t postorder, void* userdata = nullptr);

    Node* root;
};


int main() {
    DTree tree;

    // for (int i = 0; i < int(1e9); ++i) {
    for (int i = 0; i < 10; ++i) {
        DTree temp;
        temp.insert(i, i, int(9e8) * i % int(1e9 - 1));
        tree = (tree + temp);
    }

    cout << tree;

    return 0;
}

// ---------------------------------------------                    ---------------------------------------------
// ----------------------------------------------                  ----------------------------------------------
// -----------------------------------------------                -----------------------------------------------
// ------------------------------------------------              ------------------------------------------------
// -------------------------------------------------            -------------------------------------------------
// --------------------------------------------------          --------------------------------------------------
// ---------------------------------------------------        ---------------------------------------------------
// ----------------------------------------------------      ----------------------------------------------------
// -----------------------------------------------------    -----------------------------------------------------
// ------------------------------------------------------  ------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

// ----------------------------------------------- DTREE  segment -----------------------------------------------
// ---------------------------------------------------(public)---------------------------------------------------
// -----------------------------------------------------    -----------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

void DTree::insert(Value_t value, X_t x, Y_t y) {
    Node* newNode = new Node(value, x, y);

    if (!!*this) {
        cout << "TODOTODOTODO" << endl;
        return;
    }

    root = newNode;
}

DTree::DTree() : root(nullptr) {}

ostream& operator<<(ostream& output, DTree& ro) {
    ro.dfs(
        [](Value_t value, void* outputPtr) -> void {
        ostream& output = *(ostream*)outputPtr;

        output << "(";
    },

        [](Value_t value, void* outputPtr) -> void {
        ostream& output = *(ostream*)outputPtr;

        output << value;
    },

        [](Value_t value, void* outputPtr) -> void {
        ostream& output = *(ostream*)outputPtr;

        output << ")";
    },

        (void*)&output
    );

    return output;
}

// --------------------------------------------- DTREENODE  segment ---------------------------------------------
// ---------------------------------------------------        ---------------------------------------------------
// -----------------------------------------------------    -----------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

DTree::Node::Node(Value_t value, X_t x, Y_t y) :
    value(value),
    x(x),
    y(y),
    left(nullptr),
    right(nullptr) {
}

// DTree::Node::Node(Value_t value) : DTree::Node::Node(value, X_t(), Y_t()) {}

// DTree::Node* DTree::Node::getLeft() const {
//     return left;
// }
// DTree::Node* DTree::Node::getRight() const {
//     return right;
// }

bool operator<=(const DTree::Node& lo, const DTree::Node& ro) {
    return lo.x <= ro.x;
}

bool operator>(const DTree::Node& lo, const DTree::Node& ro) {
    return lo.x > ro.x;
}

bool operator<<=(const DTree::Node& lo, const DTree::Node& ro) {
    return lo.y <= ro.y;
}

bool operator>>(const DTree::Node& lo, const DTree::Node& ro) {
    return lo.y > ro.y;
}

// ----------------------------------------------- DTREE  segment -----------------------------------------------
// --------------------------------------------------(private)---------------------------------------------------
// -----------------------------------------------------    -----------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

DTree::DTree(Node* nodePtr) : root(nodePtr) {
}

DTree::operator Node* () {
    return root;
}
DTree::operator Node const* () const {
    return root;
}

bool DTree::operator==(Node const* const& ro) const {
    return root == ro;
}

bool DTree::operator==(const std::nullptr_t& ro) const {
    return *this == (Node*)ro;
}

bool DTree::operator!() const {
    return (*this == nullptr);
}

DTree::Node*& DTree::left() const {
    return root->left;
}
DTree::Node*& DTree::right() const {
    return root->right;
}

DTree operator+(const DTree& lo, const  DTree& ro) {
    if (!lo) return ro;
    if (!ro) return lo;

    if (*lo <<= *ro) {
        ro.left() = (lo + ro.left());
        return ro;
    }

    lo.right() = (lo.right() + ro);
    return lo;
}

void DTree::dfs(DfsCBFunc_t preorder, DfsCBFunc_t inorder, DfsCBFunc_t postorder, void* userdata) {
    if (!*this) return;

    if (preorder) preorder(root->value, userdata);

    DTree(left()).dfs(preorder, inorder, postorder, userdata);

    if (inorder) inorder(root->value, userdata);

    DTree(right()).dfs(preorder, inorder, postorder, userdata);

    if (postorder) postorder(root->value, userdata);
}
