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

// --------------------------------------------------------------------------------------------------------------
// ---------------------------------------------\\ CLASS POSITION //---------------------------------------------
// ----------------------------------------------\\              //----------------------------------------------

class Position {
public:
    Position(long long int posM, long long int posN);

    friend Position operator-(const Position& lo, const Position& ro);
    friend Position operator+(const Position& lo, const Position& ro);

    bool correct(long long int limitM, long long int limitN) const;

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

    Position::Iterator& begin();
    Position::Iterator& end();

private:
    Position pos;
    const Position limit;
};

// --------------------------------------------------------------------------------------------------------------
// -----------------------------------------------\\ CLASS CELL //-----------------------------------------------
// ------------------------------------------------\\          //------------------------------------------------

class Cell {
public:
    Cell();

    void operator=(const Position& init);

    void start();
    void reset();

    void operator<<(const Cell& ro);
    void discountMove(const Cell& ro, const string& s1, const string& s2);

    friend ostream& operator<<(ostream& out, const Cell& ro);

    bool isProcessed() const;

    friend bool operator==(const Cell& lo, const Cell& ro);

private:
    Position pos;

    class Profit {
    public:
        Profit();

        void operator=(long long int init);

        void reset();

        bool operator>(const Profit& ro) const;

        Profit operator+(const long long int& cost) const;

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

int main() {
    string s1, s2;

    cin >> s1 >> s2;

    ///< field[a][b] corresponds to string mathes ((a-lengthed prefix s1) + (b-lengthed postfix s2))
    vector<vector<Cell>> field(s1.length() + 1, vector<Cell>(s2.length() + 1, Cell()));

    for (int a = 0; a < field.size(); ++a) {
        for (int b = 0; b < field[a].size(); ++b) {
            field[a][b] = Position(a, b);
        }
    }

    const vector<Position> moves = { {0, +1}, {-1, 0}, {-1, +1} };
    {
        field[s1.length()][0].start();

        for (Position pos : Position(s1.length(), s2.length())) {
            for (Position move : moves) {

                Position next = pos + move;
                if (next.correct(s1.length(), s2.length())) {
                    // cout << pos << " -> " << next << endl;

                    if (move == Position(-1, +1)) {
                        field[next.m()][next.n()].discountMove(field[pos.m()][pos.n()], s1, s2);
                    } else {
                        field[next.m()][next.n()] << field[pos.m()][pos.n()];
                    }
                };

            }
        }
    }

    cout << field[0][s2.length()] << endl;

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

// --------------------------------------------------------------------------------------------------------------
// -----------------------------------------------\\ CLASS CELL //-----------------------------------------------
// ------------------------------------------------\\          //------------------------------------------------

Cell::Cell() : pos(0, 0) {}

void Cell::operator=(const Position& init) {
    pos = init;
}

void Cell::start() {
    profit = 0;
}

void Cell::reset() {
    profit.reset();
}

void Cell::operator<<(const Cell& ro) {
    Profit newProfit = ro.profit + 1;

    if (newProfit > profit) {
        profit = newProfit;
    }
}

void Cell::discountMove(const Cell& ro, const string& s1, const string& s2) {
    int cost = 1;

    // hardcoded move {-1, +1}
    if (s1[s1.length() - pos.n()] == s2[ro.pos.m() - 1]) cost = 0;

    Profit newProfit = ro.profit + cost;

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

ostream& operator<<(ostream& out, const Cell& ro) {
    out << ro.profit;
    return out;
}

// --------------------------------------------------------------------------------------------------------------
// -------------------------------------------\\ CLASS CELL::PROFIT //-------------------------------------------
// --------------------------------------------\\                  //--------------------------------------------

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

    return profit < ro.profit;
};

Cell::Profit Cell::Profit::operator+(const long long int& cost) const {
    Profit res;

    if (!isProcessed()) return res;

    res.processed = true;
    res.profit = profit + cost;

    return res;
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

// --------------------------------------------------------------------------------------------------------------
// ---------------------------------------------\\ CLASS POSITION //---------------------------------------------
// ----------------------------------------------\\              //----------------------------------------------

Position::Position(long long int posM, long long int posN) : posM(posM), posN(posN) {}

Position operator-(const Position& lo, const Position& ro) {
    return Position(
        lo.posM - ro.posM,
        lo.posN - ro.posN
    );
}

Position operator+(const Position& lo, const Position& ro) {
    return Position(
        lo.posM + ro.posM,
        lo.posN + ro.posN
    );
}

bool Position::correct(long long int limitM, long long int limitN) const {
    return
        m() >= 0 &&
        n() >= 0 &&
        m() <= limitM &&
        n() <= limitN
        ;
}

long long int Position::m() const {
    return posM;
}
long long int Position::n() const {
    return posN;
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
    return Position::Iterator(*this).begin();
}

Position::Iterator Position::end() const {
    return Position::Iterator(*this).end();
}

// --------------------------------------------------------------------------------------------------------------
// ----------------------------------------\\ CLASS POSITION::ITERATOR //----------------------------------------
// -----------------------------------------\\                        //-----------------------------------------

Position::Iterator::Iterator(const Position& limit) : pos(0, 0), limit(limit) {}

Position::Iterator& Position::Iterator::operator++() {
    ++pos.posN;

    if (pos.n() >= limit.n()) {
        pos.posN = 0;
        --pos.posM;
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

Position::Iterator& Position::Iterator::begin() {
    pos.posM = limit.posM;
    pos.posN = 0;
    return *this;
}

Position::Iterator& Position::Iterator::end() {
    pos.posM = -1;
    pos.posN = 0;
    return *this;
}
