#include <iostream>
#include <random>
#include <functional>
#include <utility>
#include <cstdio>

using namespace std;

typedef int Value_t;
typedef long long int X_t;
const X_t X_t_delta = 1;
typedef int Y_t;

class RandomM {
public:
    RandomM();

    Y_t operator()();
private:
    /// @brief a seed source for the random number engine
    std::random_device rd;
    /// @brief mersenne_twister_engine seeded with rd()
    std::mt19937 gen;
    std::uniform_int_distribution<Y_t> distrib;
};

class DTree {
public:
    DTree();

    // void insert(Value_t value, X_t x, Y_t y);
    // void insert(Value_t value, X_t x);
    void insertRight(Value_t value);

    void erase(X_t x);

    friend ostream& operator<<(ostream& output, DTree& ro);

    Value_t operator()();

    Value_t findKMax(int k);
    Value_t findKey(X_t k);

    // void wrtieDownLR(vector<X_t>& keys, int l, int r);

private:
    class Node {
    public:
        Node(Value_t value/*, X_t x*/, Y_t y);
        ~Node();
        // Node(Value_t value);

        // Node* getLeft() const;
        // Node* getRight() const;

        // /// @brief Comaring .x with ro
        // bool operator<(const X_t& ro) const;
        // /// @brief Comaring .x with ro
        // bool eqX(const X_t& ro) const;
        // /// @brief Comaring lo.x with ro.x
        // friend bool operator<=(const DTree::Node& lo, const DTree::Node& ro);
        // /// @brief Comaring lo.x with ro.x
        // friend bool operator>(const DTree::Node& lo, const DTree::Node& ro);
        /// @brief Comaring lo.y with ro.y
        friend bool operator<<=(const DTree::Node& lo, const DTree::Node& ro);
        /// @brief Comaring lo.y with ro.y
        friend bool operator>>(const DTree::Node& lo, const DTree::Node& ro);

        void updateSize() const;

        Node* left;
        Node* right;
        mutable int size;
        Value_t value;
    private:
    public:
        // X_t x;
    private:
        Y_t y;

    };
    // friend bool operator<=(const DTree::Node& lo, const DTree::Node& ro);
    // friend bool operator>(const DTree::Node& lo, const DTree::Node& ro);
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
    int size() const;

    // void tempInsert(Node* newNode);

    /// @brief merge
    friend DTree operator+(const DTree& lo, const DTree& ro);
    /// @brief split
    // friend pair<DTree, DTree> operator/(const DTree& tree, const X_t& x);
    friend pair<DTree, DTree> operator/(const DTree& tree, const X_t& sizeL);

    /// @brief dfs callback function type
    typedef function<void(Value_t, void*)> DfsCBFunc_t;
    /// @brief Deep-first tree bypass
    void dfs(DfsCBFunc_t preorder, DfsCBFunc_t inorder, DfsCBFunc_t postorder, void* userdata = nullptr);

    /// @brief dfs callback function type
    typedef function<void(Node*, void*)> DeepDfsCBFunc_t;
    /// @brief Deep-first tree bypass
    void deepDfs(DeepDfsCBFunc_t preorder, DeepDfsCBFunc_t inorder, DeepDfsCBFunc_t postorder, void* userdata = nullptr);

    Node* root;

    static RandomM randomm;
};


int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    DTree tree;

    int n = 0, m = 0;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        tree.insertRight(i);
    }

    for (int i = 1; i <= m; ++i) {
        int l = 0, r = 0;
        cin >> l >> r;

        // cout << "tree:             " << tree << endl;
        auto leftTree = tree / (l - 1);
        // cout << ":                 " << leftTree.first << "|" << leftTree.second << endl;
        auto rightTree = leftTree.second / (r - l + 1);
        // cout << ":                 " << leftTree.first << "|" << rightTree.first << "|" << rightTree.second << endl;
        tree = rightTree.first + leftTree.first + rightTree.second;
        // cout << ":                 " << tree << endl;
    }

    cout << tree << endl;

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

RandomM::RandomM() : rd(), gen(rd()), distrib(0) {
}

Y_t RandomM::operator()() {
    return distrib(gen);
}

// ----------------------------------------------- DTREE  segment -----------------------------------------------
// ---------------------------------------------------(public)---------------------------------------------------
// -----------------------------------------------------    -----------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

RandomM DTree::randomm;

DTree::DTree() : root(nullptr) {}

// void DTree::insert(Value_t value, X_t x, Y_t y) {
//     Node* newNode = new Node(value, x, y);

//     if (!*this) {
//         root = newNode;
//         return;
//     }

//     ///          \x/
//     /// spl[0] | {x} | spl[1]
//     auto spl = *this / x;
//     *this = spl.first + newNode + spl.second;

//     return;
// }

// void DTree::insert(Value_t value, X_t x) {
//     insert(value, x, randomm());
// }

void DTree::insertRight(Value_t value) {
    Node* newNode = new Node(value, randomm());

    if (!*this) {
        root = newNode;
        return;
    }

    ///          \x/
    /// spl[0] | {x} | spl[1]
    // auto spl = *this / x;
    *this = *this + newNode;

    return;
}


void DTree::erase(X_t x) {
    ///          \x/
    /// spl[0] | spl[1]
    auto spl = *this / x;
    ///         \x/
    /// splR[0]={x} | splR[1]
    auto splR = spl.second / (x + X_t_delta);

    delete splR.first.root;
    *this = spl.first + splR.second;
}

ostream& operator<<(ostream& output, DTree& ro) {
    ro.dfs(
        [](Value_t value, void* outputPtr) -> void {
        ostream& output = *(ostream*)outputPtr;

        // output << "(";
    },

        [](Value_t value, void* outputPtr) -> void {
        ostream& output = *(ostream*)outputPtr;

        // output << value;
        output << value << " ";
    },

        [](Value_t value, void* outputPtr) -> void {
        ostream& output = *(ostream*)outputPtr;

        // output << ")";
    },

        (void*)&output
    );

    return output;
}

Value_t DTree::operator()() {
    if (!*this) return 0;

    return root->value;
}

Value_t DTree::findKMax(int k) {
    if (DTree(left()).size() + 1 == k) {
        return (*this)();
    }

    if (DTree(left()).size() + 1 > k) {
        return DTree(left()).findKMax(k);
    }

    return DTree(right()).findKMax(k - DTree(left()).size() - 1);
}

// Value_t DTree::findKey(X_t k) {
//     if (this->root->eqX(k)) {
//         return (*this)();
//     }

//     if (*this->root < k) {
//         return DTree(right()).findKey(k);
//     }

//     return DTree(left()).findKey(k);
// }

// void DTree::wrtieDownLR(vector<X_t>& keys, int l, int r) {
//     struct Userdata {
//         vector<X_t>& keys;
//         int number;
//         int l, r;
//     };

//     Userdata userdata{ keys, 0, l, r };
//     deepDfs(
//         [](Node* root, void* userdata) -> void {},

//         [](Node* root, void* userdata) -> void {
//         ((Userdata*)userdata)->number++;

//         if (
//             ((Userdata*)userdata)->number >= ((Userdata*)userdata)->l &&
//             ((Userdata*)userdata)->number <= ((Userdata*)userdata)->r
//             )
//             ((Userdata*)userdata)->keys.emplace_back(root->x);
//     },

//         [](Node* root, void* userdata) -> void {},

//         (void*)&userdata
//     );
// }


// --------------------------------------------- DTREENODE  segment ---------------------------------------------
// ---------------------------------------------------        ---------------------------------------------------
// -----------------------------------------------------    -----------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

DTree::Node::Node(Value_t value/*, X_t x*/, Y_t y) :
    value(value),
    // x(x),
    y(y),
    left(nullptr),
    right(nullptr),
    size(1) {
}

DTree::Node::~Node() {
    if (left) delete left;
    if (right) delete right;
}

// DTree::Node::Node(Value_t value) : DTree::Node::Node(value, X_t(), Y_t()) {}

// DTree::Node* DTree::Node::getLeft() const {
//     return left;
// }
// DTree::Node* DTree::Node::getRight() const {
//     return right;
// }

// bool DTree::Node::operator<(const X_t& ro) const {
//     return x < ro;
// }

// bool DTree::Node::eqX(const X_t& ro) const {
//     return x == ro;
// }

// bool operator<=(const DTree::Node& lo, const DTree::Node& ro) {
//     return lo.x <= ro.x;
// }

// bool operator>(const DTree::Node& lo, const DTree::Node& ro) {
//     return lo.x > ro.x;
// }

bool operator<<=(const DTree::Node& lo, const DTree::Node& ro) {
    return lo.y <= ro.y;
}

bool operator>>(const DTree::Node& lo, const DTree::Node& ro) {
    return lo.y > ro.y;
}

void DTree::Node::updateSize() const {
    size = 1;
    size += DTree(left).size();
    size += DTree(right).size();
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
int DTree::size() const {
    return root ? root->size : 0;
}

DTree operator+(const DTree& lo, const  DTree& ro) {
    if (!lo) return ro;
    if (!ro) return lo;

    if (*lo <<= *ro) {
        ro.left() = (lo + ro.left());
        ro.root->updateSize();
        return ro;
    }

    lo.right() = (lo.right() + ro);
    lo.root->updateSize();
    return lo;
}

// pair<DTree, DTree> operator/(const DTree& tree, const X_t& x) {
//     if (!tree) return { tree, tree };

//     if (*tree < x) {
//         ///                             \x/
//         /// tree.left | tree.root | r[0] | r[1]
//         auto r = DTree(tree.right()) / x;
//         tree.right() = r.first;
//         tree.root->updateSize();
//         return { tree, r.second };
//     } else {
//         ///     \x/
//         /// l[0] | l[1] | tree.root | tree.right
//         auto l = DTree(tree.left()) / x;
//         tree.left() = l.second;
//         tree.root->updateSize();
//         return { l.first, tree };
//     }
// }

pair<DTree, DTree> operator/(const DTree& tree, const X_t& sizeL) {
    if (!tree) return { tree, tree };

    if (DTree(tree.left()).size() > sizeL) {
        ///     \x/
        /// l[0] | l[1] | tree.root | tree.right
        auto l = DTree(tree.left()) / sizeL;
        tree.left() = l.second;
        tree.root->updateSize();
        return { l.first, tree };
    } else if (DTree(tree.left()).size() == sizeL) {
        DTree l = tree.left();
        tree.left() = DTree(nullptr);
        tree.root->updateSize();
        return { l, tree };
    } else if (DTree(tree.left()).size() == sizeL - 1) {
        DTree r = tree.right();
        tree.right() = DTree(nullptr);
        tree.root->updateSize();
        return { tree, r };
    } else {
        ///                             \x/
        /// tree.left | tree.root | r[0] | r[1]
        auto r = DTree(tree.right()) / (sizeL - DTree(tree.left()).size() - 1);
        tree.right() = r.first;
        tree.root->updateSize();
        return { tree, r.second };
    }
}

void DTree::dfs(DfsCBFunc_t preorder, DfsCBFunc_t inorder, DfsCBFunc_t postorder, void* userdata) {
    if (!*this) return;

    if (preorder) preorder(root->value, userdata);

    DTree(left()).dfs(preorder, inorder, postorder, userdata);

    if (inorder) inorder(root->value, userdata);

    DTree(right()).dfs(preorder, inorder, postorder, userdata);

    if (postorder) postorder(root->value, userdata);
}

void DTree::deepDfs(DeepDfsCBFunc_t preorder, DeepDfsCBFunc_t inorder, DeepDfsCBFunc_t postorder, void* userdata) {
    if (!*this) return;

    if (preorder) preorder(root, userdata);

    DTree(left()).deepDfs(preorder, inorder, postorder, userdata);

    if (inorder) inorder(root, userdata);

    DTree(right()).deepDfs(preorder, inorder, postorder, userdata);

    if (postorder) postorder(root, userdata);
}
