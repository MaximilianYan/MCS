#include <iostream>
#include <random>
#include <functional>
#include <utility>
#include <algorithm>
#include <stack>

using namespace std;

typedef int Value_t;
typedef int X_t;
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

    /// @brief returns DTree-pointer to created node
    DTree insert(Value_t value, X_t x, Y_t y);
    void insert(Value_t value, X_t x);

    friend ostream& operator<<(ostream& output, DTree& ro);

    Value_t operator()();

    bool lessX(const DTree& ro);

    DTree l() const;
    DTree r() const;

    // private: !!!!!!!ИЗМЕНЕНИЕ
    class Node {
    public:
        Node(Value_t value, X_t x, Y_t y);
        // Node(Value_t value);

        // Node* getLeft() const;
        // Node* getRight() const;

        /// @brief Comaring .x with ro
        bool operator<(const X_t& ro) const;
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
public:
    bool operator!() const;
private:

    Node*& left() const;
    Node*& right() const;

    // void tempInsert(Node* newNode);

    /// @brief merge
    friend DTree operator+(const DTree& lo, const DTree& ro);
    /// @brief split
    friend pair<DTree, DTree> operator/(const DTree& tree, const X_t& x);

    /// @brief dfs callback function type
    typedef function<void(Value_t, void*)> DfsCBFunc_t;
    /// @brief Deep-first tree bypass
    void dfs(DfsCBFunc_t preorder, DfsCBFunc_t inorder, DfsCBFunc_t postorder, void* userdata = nullptr);
public: //!!!!! ИЗМЕНЕНИЕ
    Node* root;
private:

    static RandomM randomm;
};


int main() {
    int n = 0;
    cin >> n;

    vector<DTree> nodes(n + 1);
    DTree tree;

    {
        struct NodeInput {
        public:
            int i;
            int x;
            int y;
        };
        vector<NodeInput> input;

        for (int i = 1; i <= n; ++i) {
            int x = 0, y = 0;
            cin >> x >> y;
            input.push_back({ i, x, y });
        }

        sort(input.begin(), input.end(), [](const NodeInput& lo, const NodeInput& ro) -> bool {
            return lo.x < ro.x;
        });

        // vector<DTree> leaves;

        stack<DTree::Node*> upstair;
        DTree::Node* prev = nullptr;

        for (const NodeInput& node : input) {
            DTree newNode;
            newNode.insert(node.i, node.x, -node.y);
            nodes[node.i] = newNode;

            if (!prev) {
                tree.root = newNode.root;
                prev = newNode.root;

                continue;
            }

            if (*newNode.root <<= *prev) {
                prev->right = newNode.root;
                upstair.emplace(prev);
                prev = newNode.root;
                continue;
            }

            DTree::Node* prevPrev = nullptr;
            while (!upstair.empty() && (*prev <<= *newNode.root)) {
                prevPrev = prev;
                prev = upstair.top();
                upstair.pop();
            }

            if (*newNode.root <<= *prev) {
                prev->right = newNode.root;
                newNode.root->left = prevPrev;
            } else {
                newNode.root->left = tree.root;
                tree.root = newNode.root;
            }
            prev = newNode.root;



            // if (leaves.empty() || leaves.rbegin()->lessX(newNode)) {
            //     leaves.push_back(newNode);
            // } else
            //     for (int i = 0; i < leaves.size(); ++i) {
            //         if (!leaves[i].lessX(newNode)) {
            //             leaves.insert(leaves.begin() + i, newNode);

            //             if (i > 0 && !!leaves[i - 1].l() && !!leaves[i - 1].r()) {
            //                 leaves.erase(leaves.begin() + i - 1);
            //                 i--;
            //             }
            //             if (i < (leaves.size() - 1) && !!leaves[i + 1].l() && !!leaves[i + 1].r()) {
            //                 leaves.erase(leaves.begin() + i + 1);
            //             }

            //             break;
            //         }
            //     }
        }
    }
    // cout << tree << endl;

    struct NodeInfo {
    public:
        int p;
        int l;
        int r;
    };
    vector<NodeInfo> infos(n + 1, { 0, 0 ,0 });

    nodes.erase(nodes.begin());
    for (DTree& node : nodes) {
        infos[node.l()()].p = node();
        infos[node.r()()].p = node();

        infos[node()].l = node.l()();
        infos[node()].r = node.r()();
    }

    cout << "YES" << endl;
    infos.erase(infos.begin());
    for (NodeInfo& info : infos) {
        cout << info.p << " " << info.l << " " << info.r << endl;
    }

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

DTree DTree::insert(Value_t value, X_t x, Y_t y) {
    Node* newNode = new Node(value, x, y);

    if (!*this) {
        root = newNode;
        return newNode;
    }

    ///          \x/
    /// spl[0] | {x} | spl[1]
    auto spl = *this / x;
    *this = spl.first + newNode + spl.second;

    return newNode;
}

void DTree::insert(Value_t value, X_t x) {
    insert(value, x, randomm());
}

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

Value_t DTree::operator()() {
    if (!*this) return 0;

    return root->value;
}

bool DTree::lessX(const DTree& ro) {
    return *this < ro;
}

DTree DTree::l() const {
    return left();
}
DTree DTree::r() const {
    return right();
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

bool DTree::Node::operator<(const X_t& ro) const {
    return x < ro;
}

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

pair<DTree, DTree> operator/(const DTree& tree, const X_t& x) {
    if (!tree) return { tree, tree };

    if (*tree < x) {
        ///                             \x/
        /// tree.left | tree.root | r[0] | r[1]
        auto r = DTree(tree.right()) / x;
        tree.right() = r.first;
        return { tree, r.second };
    } else {
        ///     \x/
        /// l[0] | l[1] | tree.root | tree.right
        auto r = DTree(tree.left()) / x;
        tree.left() = r.second;
        return { r.first, tree };
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
