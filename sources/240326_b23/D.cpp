#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <iomanip>

using namespace std;

static bool DEBUG = false;

typedef int Random_t;

class RandomM {
public:
    RandomM();

    Random_t operator()();
private:
    /// @brief a seed source for the random number engine
    std::random_device rd;
    /// @brief mersenne_twister_engine seeded with rd()
    std::mt19937 gen;
    std::uniform_int_distribution<Random_t> distrib;
};

typedef int PointCoord_t;

class Point {
public:
    PointCoord_t x;
    PointCoord_t y;

    static const vector<Point> neighbours;

    bool operator==(const Point& ro) const {
        return
            x == ro.x &&
            y == ro.y
            ;
    }
    bool operator!=(const Point& ro) const {
        return
            x != ro.x ||
            y != ro.y
            ;
    }
    Point operator+(const Point& ro) const {
        return{
            x + ro.x,
            y + ro.y
        };
    }
    bool operator<(const Point& ro) const {
        if (x < ro.x)
            return true;
        if (x > ro.x)
            return false;
        if (y < ro.y)
            return true;
        if (y > ro.y)
            return false;
        return false;
    }

    class Distance {
    public:
        Distance() : inf(true), d(-1) {};
        Distance(PointCoord_t init) : inf(false), d(init) {};

        bool lessInf() { return !inf; }

        void setZero() {
            inf = false;
            d = 0;
        }

        Distance operator+(const PointCoord_t& ro) const {
            if (inf) return Distance();
            return Distance(d + 1);
        }

        bool operator==(const Distance& ro) const {
            if (inf && ro.inf) return true;
            if (inf || ro.inf) return false;
            return d == ro.d;
        }
        bool operator<(const Distance& ro) const {
            if (inf) return false;
            if (ro.inf) return true;
            return d < ro.d;
        }

    private:
        bool inf;
    public:
        PointCoord_t d;
    };
};

class MazeGenerator {
public:
    MazeGenerator();

    void generate();

    Point run(Point pos, vector<Point>& commands);
    bool apply(Point& pos, vector<Point>::iterator commandsBegin, vector<Point>::iterator commandsEnd);

    static const int SIZE = 10;
private:
    static RandomM randomm;

    void generateWalls();
    void generateStart();

    Point getFurthest(Point pos);

    void clearField();

    Point getRandomPoint();

    vector<vector<Point::Distance>> calcBfs(Point pos);
    bool checkReachability(set<Point> points);

public:
    vector<vector<bool>> field;
    Point start;
    Point finish;
    vector<vector<Point::Distance>> solution;
};

class ANSWER {
public:
    static string str;
};

const int MAZE_COUNT = 870;

int main() {
    string t;
    cin >> t;

    if (t == "g") {
        vector<MazeGenerator> mazes;
        for (int i = 0; i < MAZE_COUNT; ++i) {
            mazes.emplace_back();
            mazes.rbegin()->generate();

            // cout << "maze:" << endl;
            // for (int i = 0; i < mazes.rbegin()->SIZE + 2; ++i) {
            //     for (int j = 0; j < mazes.rbegin()->SIZE + 2; ++j) {
            //         if (mazes.rbegin()->start == Point{ i, j })
            //             cout << "S";
            //         else if (mazes.rbegin()->finish == Point{ i, j })
            //             cout << "F";
            //         else
            //             cout << (mazes.rbegin()->field[i][j] ? "." : "#");
            //     }
            //     cout << endl;
            // }

            if (!(i % 10))
                cout << "generated " << ((double)i) / MAZE_COUNT << endl;

        }


        vector<Point> commands;
        vector<Point> pos;
        
        for (MazeGenerator maze : mazes) pos.emplace_back(maze.start);
        vector<bool> done(mazes.size(), false);

        for (int i = 0; i < mazes.size(); ++i) {
            if (done[i]) continue;

            int comBeginI = commands.size();
            pos[i] = mazes[i].run(pos[i], commands);
            done[i] = true;

            vector<Point>::iterator commandsBegin = commands.begin() + comBeginI;
            for (int j = i; j < mazes.size(); ++j) {
                if (done[j]) continue;
                done[j] = mazes[j].apply(pos[j], commandsBegin, commands.end());
            }

            if (!(i % 10))
                cout << "done " << ((double)i) / mazes.size() << endl;
        }

        ofstream file("A.cpp.coms.out");
        for (Point com : commands) {
            if (com == Point::neighbours[0])
                file << "N";
            if (com == Point::neighbours[1])
                file << "W";
            if (com == Point::neighbours[2])
                file << "S";
            if (com == Point::neighbours[3])
                file << "E";
        }
        file.close();

        cout << "done " << commands.size() << " steps" << endl;


    } else {


        cout << ANSWER::str << endl;
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


// ---------------------------------------------- RANDOMM  segment ----------------------------------------------
// ---------------------------------------------------(public)---------------------------------------------------
// -----------------------------------------------------    -----------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

RandomM::RandomM() : rd(), gen(rd()), distrib(0) {
}

Random_t RandomM::operator()() {
    return distrib(gen);
}


// ----------------------------------------------- POINT  segment -----------------------------------------------
// ---------------------------------------------------(public)---------------------------------------------------
// -----------------------------------------------------    -----------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

const vector<Point> Point::neighbours = {
    {-1, 0},
    {0, -1},
    {+1, 0},
    {0, +1}
};


// ------------------------------------------- MAZEGENERATOR  segment -------------------------------------------
// ---------------------------------------------------(public)---------------------------------------------------
// -----------------------------------------------------    -----------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

RandomM MazeGenerator::randomm;

MazeGenerator::MazeGenerator() {
    clearField();
}

void MazeGenerator::generate() {
    generateWalls();
    generateStart();
    solution = calcBfs(finish);
}

Point MazeGenerator::run(Point pos, vector<Point>& commands) {

    while (pos != finish) {
        for (Point delta : Point::neighbours) {
            Point next = pos + delta;
            if (solution[pos.x][pos.y] == solution[next.x][next.y] + 1) {
                commands.emplace_back(delta);
                pos = next;
                break;
            }
        }


        if (DEBUG) {   /// ------------------------------------------------------ DEBUG OUTPUT ----------------------------------------
            cout << endl << endl << endl << "RUN ITER" << endl;
            for (int i = 0; i < SIZE + 2; ++i) {
                for (int j = 0; j < SIZE + 2; ++j) {
                    if (pos == Point{ i, j })
                        cout << " !";
                    else if (start == Point{ i, j })
                        cout << " S";
                    else if (finish == Point{ i, j })
                        cout << " @";
                    else if (field[i][j])
                        if (solution[i][j].d == -1)
                            cout << " x";
                        else
                            cout << setw(2) << solution[i][j].d;
                    else
                        cout << " #";
                }
                cout << endl;
            }
            string in;
            cin >> in;
        }   /// ------------------------------------------------------ DEBUG OUTPUT ----------------------------------------


    }

    return pos;
}

bool MazeGenerator::apply(Point& pos, vector<Point>::iterator commandsBegin, vector<Point>::iterator commandsEnd) {
    for (;commandsBegin != commandsEnd; ++commandsBegin) {
        Point next = pos + *commandsBegin;
        if (field[next.x][next.y]) pos = next;
        if (pos == finish) return true;
    }

    return false;
}



// ------------------------------------------- MAZEGENERATOR  segment -------------------------------------------
// ---------------------------------------------------        ---------------------------------------------------
// -----------------------------------------------------    -----------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

vector<vector<Point::Distance>> MazeGenerator::calcBfs(Point pos) {
    vector<vector<Point::Distance>> distances(SIZE + 2, vector<Point::Distance>(SIZE + 2, Point::Distance()));
    vector<vector<bool>> checked(SIZE + 2, vector<bool>(SIZE + 2, false));

    distances[pos.x][pos.y].setZero();
    checked[pos.x][pos.y] = true;

    queue<Point> bfsQueue;
    bfsQueue.emplace(pos);

    while (bfsQueue.size()) {
        Point cur = bfsQueue.front();
        bfsQueue.pop();
        for (Point delta : Point::neighbours) {
            Point next = cur + delta;

            if (!field[next.x][next.y]) continue;

            if (checked[next.x][next.y]) continue;
            checked[next.x][next.y] = true;

            distances[next.x][next.y] = distances[cur.x][cur.y] + 1;
            bfsQueue.emplace(next);
        }


        // if (DEBUG) {   /// ------------------------------------------------------ DEBUG OUTPUT ----------------------------------------
        //     cout << endl << endl << endl << "BFS ITER" << endl;
        //     for (int i = 0; i < SIZE + 2; ++i) {
        //         for (int j = 0; j < SIZE + 2; ++j) {
        //             if (cur == Point{ i, j })
        //                 cout << " !";
        //             else if (pos == Point{ i, j })
        //                 cout << " $";
        //             else if (field[i][j])
        //                 if (distances[i][j].d == -1)
        //                     cout << " x";
        //                 else
        //                     cout << setw(2) << distances[i][j].d;
        //             // cout << " .";
        //             else
        //                 cout << " #";
        //         }
        //         cout << endl;
        //     }
        //     cout << "queue size = " << bfsQueue.size();
        //     string in;
        //     cin >> in;
        // }   /// ------------------------------------------------------ DEBUG OUTPUT ----------------------------------------
    }

    return distances;
}

void MazeGenerator::generateWalls() {
    const int N_1 = 20;
    const int N_2 = 500;

    clearField();
    for (int i = 0; i <= SIZE + 1; ++i) {
        field[0][i] = false;
        field[SIZE + 1][i] = false;
        field[i][0] = false;
        field[i][SIZE + 1] = false;
    }

    set<Point> points;
    for (Point point; points.size() < N_1; points.emplace(point)) {
        do point = getRandomPoint();
        while (points.count(point));
    }


    // cout << "generated " << points.size() << " points" << endl;

    for (int i = 0; i < N_2; ++i) {
        Point point = getRandomPoint();

        if (points.count(point)) continue;

        field[point.x][point.y] = false;
        if (!checkReachability(points)) field[point.x][point.y] = true;
    }
}

void MazeGenerator::generateStart() {
    Point start1;
    do start1 = getRandomPoint();
    while (!field[start1.x][start1.y]);

    // DEBUG = true;
    start = getFurthest(start1);

    // {   /// ------------------------------------------------------ DEBUG OUTPUT ----------------------------------------
    //     cout << endl << endl << endl << "GENSTART1" << endl;
    //     for (int i = 0; i < SIZE + 2; ++i) {
    //         for (int j = 0; j < SIZE + 2; ++j) {
    //             if (start1 == Point{ i, j })
    //                 cout << " !";
    //             else if (start == Point{ i, j })
    //                 cout << " S";
    //             else if (finish == Point{ i, j })
    //                 cout << " @";
    //             else if (field[i][j])
    //                 // if (solution[i][j].d == -1)
    //                 //     cout << " x";
    //                 // else
    //                 //     cout << setw(2) << solution[i][j].d;
    //                 cout << " .";
    //             else
    //                 cout << " #";
    //         }
    //         cout << endl;
    //     }
    //     string in;
    //     cin >> in;
    // }   /// ------------------------------------------------------ DEBUG OUTPUT ----------------------------------------


    finish = getFurthest(start);
    // DEBUG = false;
}

Point MazeGenerator::getFurthest(Point pos) {
    vector<vector<Point::Distance>> distances = calcBfs(pos);

    // {   /// ------------------------------------------------------ DEBUG OUTPUT ----------------------------------------
    //     cout << endl << endl << endl << "GETFURTHEST" << endl;
    //     for (int i = 0; i < SIZE + 2; ++i) {
    //         for (int j = 0; j < SIZE + 2; ++j) {
    //             if (pos == Point{ i, j })
    //                 cout << " !";
    //             else if (start == Point{ i, j })
    //                 cout << " S";
    //             else if (finish == Point{ i, j })
    //                 cout << " @";
    //             else if (field[i][j])
    //                 if (distances[i][j].d == -1)
    //                     cout << " x";
    //                 else
    //                     cout << setw(2) << distances[i][j].d;
    //                 // cout << " .";
    //             else
    //                 cout << " #";
    //         }
    //         cout << endl;
    //     }
    //     string in;
    //     cin >> in;
    // }   /// ------------------------------------------------------ DEBUG OUTPUT ----------------------------------------


    Point::Distance furthest(0);
    Point furthestPoint;
    for (int i = 0; i < SIZE + 2; ++i)
        for (int j = 0; j < SIZE + 2; ++j)
            if (distances[i][j].lessInf() && furthest < distances[i][j]) {
                furthest = distances[i][j];
                furthestPoint = { i, j };
            }

    return furthestPoint;
}


void MazeGenerator::clearField() {
    field = vector<vector<bool>>(SIZE + 2, vector<bool>(SIZE + 2, true));
}

bool MazeGenerator::checkReachability(set<Point> points) {
    if (!points.size()) return true;
    const Point& start = *points.begin();

    vector<vector<Point::Distance>> distances = calcBfs(start);


    bool ans = true;
    for (const Point& target : points) {
        ans &= distances[target.x][target.y].lessInf();
    }
    return ans;
}

Point MazeGenerator::getRandomPoint() {
    return { 1 + randomm() % SIZE, 1 + randomm() % SIZE };
}


// ----------------------------------------------- ANSWER segment -----------------------------------------------
// ---------------------------------------------------(public)---------------------------------------------------
// -----------------------------------------------------    -----------------------------------------------------
// --------------------------------------------------------------------------------------------------------------

string ANSWER::str =
"NWWSSESSSSEEEENNNWNNNESWSWWNNWNNNWNNEENEEEESSSESSWSWWNNWWNNNNNNSEESSSWSSSESEENNEENNNESWSSSSSWWWWNWEENNWWWNWNWNNNEEEESSEWWWSWSWWNNNWNNNNNEENEEEESSSSNWWSSWSSSEESEESSWENEESSWSWWWWWWWNNNNENNNWWWNNWWENNNNEEESESSESSESSWSNNENNNNENNENNWNWWSWWSWSSSSWSWWEENEESESSWSSWWWSWNWWNWWWSSESSSWWNWWWSSNNEESESSWSSWNNNEEESSEEENNNENENNNWWWNNNWNNWWWWSWSSSESWNNNENEEEESWWWNNNENENEESSEEESEENNNNNWSSWSWSSESEESSSSSSWSWWSWWWNNNWWNNNWNNESEENNEEEESSEENNNNWWWSWWNWSSEESEENENNENNWWWNNEEENENNENEESSESSWWSSEENNNNWWNNWWWNWWNEEESSSNEESSSEENENEENNNWWWWSNENNNENNSSSSESSSWWSSWWWNNWWNWNNSEENNNWWNWNWNNWWSSSSSSSWENEEESESSSSSESSENWNWNNWWWWSSWWWSSEWNNEEENNNNNSSSESSSWWWWWNNNWNNENNWWWWNSSSSEEEEENEEENNNNWWNNNEEENNNEEEEESSSWNNNWWWWSWWSSSSSEEEEENSWSSEESSSWWSWSWWNENNEEEESSWSSSSESEEENEENENNWWNNENNNWWWSSSWWNNNENNWNWWWWWWSSSSSSESEENNEEENNNNNWNWWSWSWWNNEESSWWWSWSSWWWNNWNNENNNNNWWSWWNNENEEENSSWSSEESESSWWSSSSEEENEENENNNNWNWSSWSSWSSEEEENEENEEENNNNNSSEEEESSWWWWWSWWNWEENNWNNENNNNEEESNWWWNNNWWNNWWSSSSWESSSSEESSESEENNNEEEEESSSSWSWSWWSWWNNWWSEEEENEESSWSSSSENNNNNNNNEEEESSEEEESNNWNNNNNNWWSWWWSSSSEESSESSWWNWNWWSWSNNEEEENNNNEESSSSESSSWSWWWWWNWWWSSESSESSSSSWWWWNNENWNWWSWWWNNNNENSWSSSWWSWWSSSEEEEENEENNNSEEENNNWWSSWWNWWWSSSWWWNNNENNWWNNNWWWWWSSSESSSWWWNNNSSSESSEESNNEEENEESSSESSWSWNNNWWNNNWWNWNWWWSSSSWSSEESEEESESSWWSWWWNNENNEEEEEEENNENWWSSWSSSWWSNWWWNWWNNNNENNEESSSSEEENNEESSSESWNNNNNWNNNWWNWWWWSEEESSSEENEEEEEENNWSWWNWWWNNWWSWESEENNENNNWNNNWWWSEENNEEEEWSSSEEEENNEENNNENNWSSSSSWSSESEEEEEEENENNNNESEEESSSSWSWSSWWNWWWSWWNNEEENENNWWSWWWWNEESSSSSESEESSEENNNEEENEESSEENNNNWWNWNSEENENNNNNNWWSWSNENEEEENENNNENNWWNWWWSWSSESSWSSSESSEEEEEENSEESSSEESESSSWWSWWWWWWWNENNNEESSSEEESSSSWSSSSEEENNENEENNNENNWNWWSWNNNNWWWWSSSWWNWNSSEENNEEENEEENEESSSSWWSSEWWSWSWSWSSWWNNNNENNWNNEEENENENNWWNWWEEEEEEESESSESEEEENSWWSWWWSSSSEESSEWSSESSWSWSWWNWWWWNNNENEENNNENEEEENNWWWNSSEEEEEEEENNNNNNWNWWWNWWWESSWWWSWSSSEEEENEEENNNNWNEESEESSWNNNWWNNWNWWWWNSWWWWWWNNEEENEENENENNNWWWWSESSWWWNNNWESSEEENEEESESSWWWSSWWNWWWNWNWWSSSSSSSSEEENEEEESSSWWWSWWWNWWWEEESESSSEESWNNNWWWWSSSESSWSWSWWNNNNNNENNENEEEEESSSWSSSESSSENEESSWWWNNNENNNWWWWWSSSWWSSESEENEEEENNNENNEENNWWWWSWEESEEENNNWWNWWNNWNNEEEEESSWWEESSWWSWWWWNNENNNSESSWWSSSWWWSEEEESEEESSENNWNNWNWWWNWWWNESSWWWWSWWNWWSWSNNENNWWNWEEENNNEEWWSWSSWSSWWSSESSEENEEEENNWWNEESSEENEESSWSWSWWSSWSWNNWNNEEENNNEEEESEESSSSWSWWWSSWNEEENNWWNNWNWWWWSSSSSWEESESSESEENNNENNNWSSSWSWWNNWWWWWSSSEESEEESEEESSWWEEEEENNNNWWNNEEWSSSWSWWWWWWNNNEEWWSSWWSWWWNNNNENEENEEESSSWWWWSWSSEEESEEEESSWNNWNNEEEENNNEEESSSSSSNNWWNNWNNNWWWWWNEESSWSSSEEENNNEEENEENNWNNESSSEESSWSWSWWNNWWNNWNEESEENEENNNNWWNWWSWSNNEESSEESSWWSWWWWSESSSEEEEEEENNNENEEEESSWWWSSWSWENNENENEEESEESSSSWWSSESSWWNWWWWNNNNEENNEEEESSEESNNNWWNWNNWNWWSWSSSESSSSEENNNENNESSSWSWSSSSSWWWNWWEEENNNNNWWSSWWWWNNNNNNWSEESSEENEESSSWWWSSSSWSSEEENNEEESSWWNNWNNWWNWWWNWNNEEEEEEEEENNWNNNNNEENEEESEWWSSSSSESSSESEENNNEENNNNNNWWSWSWWNNWWWWSSSSESSEEENEESSWWWSSWWSWWNNNNENNWWEESEENEESEEENNWNNENNESSSSSWSWWSWWNNWWSSSWSSWSSSWENNWWWWWWSSWWNNWNENNWNWWWSWWWWSSWWWNNNWWNNWNESSEEEENNENNNNEESSESSSSNEEENEESESSWSSSWWNWSWSSSWWWWNNNNNEEWWNNEENNWWNNNWWSSESSSEENNENNEESSWSSWSSSWWWNNNNNWWWWNSSEENEENNEEENWSSWWSSSNNWWWWWSWWSSSEEEEESESNEESEENNNENNNENNENEEWSSWWWNWWWNNNEENEESEEENNNNNEENNNWNNENNENEWNNEEEESSSEEESSESSWWWNNWWSWWSSEEWWNWWWWWNNNENSEEESSWWWSSSEENEEEEENESWSSESSWWWSWWSSSWNNNWWWWWNNENEENNENEEEWWWWSSSSWWNNWWSWSSWSSENNEENNWWWNNEENNSSWWWNWNWESEENEESEEENNNWWNNWWNSWWNNNWWSWWSSSSEENEESSEENEESSSWWSWW"
;
