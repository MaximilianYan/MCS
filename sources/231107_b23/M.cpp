#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <limits>
#include <list>
#include <sstream>
#include <string>

using namespace std;

class Cell {
public:
    Cell();

    enum Type {
        CLEAR = 0,
        MUSHROOM,
        TREE,
    };

    void operator=(Cell::Type init);

    void start();
    void reset();

    void operator<<(const Cell& ro);

    friend ostream& operator<<(ostream& out, const Cell& ro);

    bool isProcessed() const;

    friend bool operator==(const Cell& lo, const Cell& ro);

private:
    Type type;

    class Profit {
    public:
        Profit();

        void operator=(long long int init);

        void reset();

        bool operator>(const Profit& ro) const;

        Profit operator+(const Type& type) const;

        friend ostream& operator<<(ostream& out, const Profit& ro);

        bool isProcessed() const;

        friend bool operator==(const Profit& lo, const Profit& ro);

    private:
        bool processed;
        long long int profit;
    };
    friend ostream& operator<<(ostream& out, const Profit& ro);
    friend bool operator==(const Profit& lo, const Profit& ro);

    Profit profit;
};

class Position {
public:
    Position(long long int posM, long long int posN);

    friend Position operator-(const Position& lo, const Position& ro);

    bool correct() const;

    long long int m() const;
    long long int n() const;

    friend ostream& operator<<(ostream& out, const Position& ro);

    friend bool operator==(const Position& lo, const Position& ro);

    class Iterator;

    Position::Iterator begin() const;
    Position::Iterator end() const;

private:
    long long int posM;
    long long int posN;
};

class Position::Iterator {
public:
    Iterator(const Position& limit);

    Position::Iterator& operator++();
    friend bool operator!=(const Position::Iterator& lo, const Position::Iterator& ro);

    Position& operator*();

    Position::Iterator& end();

private:
    Position pos;
    const Position limit;
};

int main() {
    long long int m = 0, n = 0, g = 0, t = 0;

    cin >> m >> n >> g >> t;

    vector<vector<Cell>> field(m, vector<Cell>(n, Cell()));

    while (g--) {
        long long int x = 0, y = 0;
        cin >> x >> y;

        field[x - 1][y - 1] = Cell::Type::MUSHROOM;
    }
    while (t--) {
        long long int x = 0, y = 0;
        cin >> x >> y;

        field[x - 1][y - 1] = Cell::Type::TREE;
    }

    const vector<Position> moves = { {0, +1}, {+1, 0} };
    {
        field[0][0].start();

        for (Position pos : Position(m, n)) {
            for (Position move : moves) {

                Position prev = pos - move;
                if (prev.correct()) {
                    // cout << prev << " -> " << pos << endl;
                    field[pos.m()][pos.n()] << field[prev.m()][prev.n()];
                };

            }
        }
    }

    cout << field[m - 1][n - 1] << endl;

    if (!field[m - 1][n - 1].isProcessed()) return 0;

    string ans;
    {
        Position pos(m - 1, n - 1);

        while (true) {
            stringstream buffer;
            buffer << pos << endl;
            ans = buffer.str() + ans;

            if (pos == Position(0, 0)) break;

            for (Position move : moves) {

                Position prev = pos - move;
                if (prev.correct()) {
                    Cell predict = field[pos.m()][pos.n()];
                    predict.reset();
                    predict << field[prev.m()][prev.n()];

                    if (predict == field[pos.m()][pos.n()]) {
                        pos = prev;
                        break;
                    }
                };

            }
        }
    }

    cout << ans;
    

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

Cell::Cell() : type(Type::CLEAR) {}

void Cell::operator=(Cell::Type init) {
    type = init;
}

void Cell::start() {
    profit = 0;
}

void Cell::reset() {
    profit.reset();
}

void Cell::operator<<(const Cell& ro) {
    Profit newProfit = ro.profit + type;

    if (newProfit > profit) {
        profit = newProfit;
    }
}

bool Cell::isProcessed() const {
    return profit.isProcessed();
}

bool operator==(const Cell& lo, const Cell& ro) {
    return lo.profit == ro.profit;
}

Cell::Profit::Profit() : processed(false), profit(0) {}

void Cell::Profit::operator=(long long int init) {
    processed = true;
    profit = init;
}

void Cell::Profit::reset() {
    processed = false;
    profit = 0;
}

bool Cell::Profit::operator>(const Cell::Profit& ro) const {
    if (!isProcessed()) return false;
    if (!ro.isProcessed()) return true;

    return profit > ro.profit;
};

Cell::Profit Cell::Profit::operator+(const Cell::Type& type) const {
    Profit res;

    if (!isProcessed()) return res;

    switch (type) {

    case Cell::Type::TREE:
        return res;
        break;

    case Cell::Type::MUSHROOM:
        res.processed = true;
        res.profit = profit + 1;
        break;
    case Cell::Type::CLEAR:
        res.processed = true;
        res.profit = profit;
        break;
    }

    return res;
}

ostream& operator<<(ostream& out, const Cell& ro) {
    out << ro.profit;
    return out;
}

Position::Position(long long int posM, long long int posN) : posM(posM), posN(posN) {}

Position operator-(const Position& lo, const Position& ro) {
    return Position(
        lo.posM - ro.posM,
        lo.posN - ro.posN
    );
}

bool Position::correct() const {
    return
        m() >= 0 &&
        n() >= 0
        ;
}

long long int Position::m() const {
    return posM;
}
long long int Position::n() const {
    return posN;
}

ostream& operator<<(ostream& out, const Cell::Profit& ro) {
    if (ro.isProcessed())
        out << ro.profit;
    else
        out << -1;
    return out;
}

bool Cell::Profit::isProcessed() const {
    return processed;
}

bool operator==(const Cell::Profit& lo, const Cell::Profit& ro) {
    if (
        !lo.isProcessed() ||
        !ro.isProcessed()
        ) return false;

    return lo.profit == ro.profit;
}

ostream& operator<<(ostream& out, const Position& ro) {
    out << ro.m() + 1 << " " << ro.n() + 1;
    return out;
}

bool operator==(const Position& lo, const Position& ro) {
    return
        lo.m() == ro.m() &&
        lo.n() == ro.n()
        ;
}

Position::Iterator Position::begin() const {
    return *this;
}

Position::Iterator Position::end() const {
    return Position::Iterator(*this).end();
}

Position::Iterator::Iterator(const Position& limit) : pos(0, 0), limit(limit) {}

Position::Iterator& Position::Iterator::operator++() {
    ++pos.posN;

    if (pos.n() == limit.n()) {
        pos.posN = 0;
        ++pos.posM;
    }

    return *this;
}

bool operator!=(const Position::Iterator& lo, const Position::Iterator& ro) {
    return
        lo.pos.m() != ro.pos.m() ||
        lo.pos.n() != ro.pos.n()
        ;
}

Position& Position::Iterator::operator*() {
    return pos;
}

Position::Iterator& Position::Iterator::end() {
    pos.posM = limit.posM;
    pos.posN = 0;
    return *this;
}
