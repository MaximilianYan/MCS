#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <iomanip>
#include <algorithm>

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

        bool isZero() {
            if (inf) return false;
            return d == 0;
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

const int MAZE_COUNT = 5000;
// const int MAZE_COUNT = 1000;

int main() {
    string t;
    cin >> t;

    if (t == "g") {
        struct Info {
            MazeGenerator m;
            Point pos;
            // bool done;
        };

        vector<Info> mazes;
        vector<Point> commands;
        int i = 0;

        while (commands.size() < 9900) {
            if (mazes.size() > 10 * MAZE_COUNT) {
                i = i + 2 * MAZE_COUNT - mazes.size();
                mazes.erase(mazes.begin(), mazes.begin() + mazes.size() - 2 * MAZE_COUNT);
            }

            int prevSize = mazes.size();
            for (; mazes.size() - i < MAZE_COUNT;) {
                mazes.emplace_back();
                mazes.rbegin()->m.generate();

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

                if (!(mazes.size() % 500))
                    cout << "generated " << ((double)mazes.size() - i) / MAZE_COUNT << endl;

            }

            for (int j = prevSize; j < mazes.size(); ++j) {
                mazes[j].pos = mazes[j].m.start;
                mazes[j].m.apply(mazes[j].pos, commands.begin(), commands.end());
            }


            // for (int i = 0; i <  /*mazes.size()*/; ++i) {
                // cout << i << endl;

                // if (DEBUG) {   /// ------------------------------------------------------ DEBUG OUTPUT ----------------------------------------
                //     cout << endl << endl << endl << "RUN ITER" << endl;
                //     for (int i = 0; i < mazes.begin()->m.SIZE + 2; ++i) {
                //         for (Info& maze : mazes) {
                //             for (int j = 0; j < mazes.begin()->m.SIZE + 2; ++j) {
                //                 if (maze.pos == Point{ i, j })
                //                     cout << " !";
                //                 else if (maze.m.start == Point{ i, j })
                //                     cout << " S";
                //                 else if (maze.m.finish == Point{ i, j })
                //                     cout << " @";
                //                 else if (maze.m.field[i][j])
                //                     if (maze.m.solution[i][j].d == -1)
                //                         cout << " x";
                //                     else
                //                         cout << setw(2) << maze.m.solution[i][j].d;
                //                 else
                //                     cout << " #";
                //             }

                //             cout << "       ";
                //         }
                //         cout << endl;
                //     }
                //     string in;
                //     cin >> in;
                // }   /// ------------------------------------------------------ DEBUG OUTPUT ----------------------------------------


            sort(mazes.begin(), mazes.end(), [](const Info& lo, const Info& ro) -> bool {
                return
                    lo.m.solution[lo.pos.x][lo.pos.y]
                    <
                    ro.m.solution[ro.pos.x][ro.pos.y]
                    ;
            });

            // cout << i << endl;

            while (mazes[i].m.solution[mazes[i].pos.x][mazes[i].pos.y].isZero()) ++i;

            int comBeginI = commands.size();
            mazes[i].pos = mazes[i].m.run(mazes[i].pos, commands);


            vector<Point>::iterator commandsBegin = commands.begin() + comBeginI;

            for (int j = i + 1; j < mazes.size(); ++j) {
                mazes[j].m.apply(mazes[j].pos, commandsBegin, commands.end());
            }

            if (!(i % 100))
                // cout << "done " << ((double)i) / mazes.size() << endl;
                cout << "i: " << i << "   | commands size: " << commands.size() << endl;
            // }
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
    // static int counter = 0;
    // if (counter == 0) {
    //     start = Point{ 1, 1 };
    //     finish = Point{ 10, 10 };
    // } else if (counter == 1) {
    //     start = Point{ 1, 1 };
    //     finish = Point{ 1, 10 };
    // } else if (counter == 2) {
    //     start = Point{ 1, 10 };
    //     finish = Point{ 1, 1 };
    // }
    // counter++;
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


        // if (DEBUG) {   /// ------------------------------------------------------ DEBUG OUTPUT ----------------------------------------
        //     cout << endl << endl << endl << "RUN ITER" << endl;
        //     for (int i = 0; i < SIZE + 2; ++i) {
        //         for (int j = 0; j < SIZE + 2; ++j) {
        //             if (pos == Point{ i, j })
        //                 cout << " !";
        //             else if (start == Point{ i, j })
        //                 cout << " S";
        //             else if (finish == Point{ i, j })
        //                 cout << " @";
        //             else if (field[i][j])
        //                 if (solution[i][j].d == -1)
        //                     cout << " x";
        //                 else
        //                     cout << setw(2) << solution[i][j].d;
        //             else
        //                 cout << " #";
        //         }
        //         cout << endl;
        //     }
        //     string in;
        //     cin >> in;
        // }   /// ------------------------------------------------------ DEBUG OUTPUT ----------------------------------------


    }

    return pos;
}

bool MazeGenerator::apply(Point& pos, vector<Point>::iterator commandsBegin, vector<Point>::iterator commandsEnd) {
    // cout << "start  " << start.x << " " << start.y << endl;
    // cout << "pos    " << pos.x << " " << pos.y << endl;
    // cout << "finish " << finish.x << " " << finish.y << endl;
    if (pos == finish) return true;
    // cout << "?.?" << endl;
    for (;commandsBegin != commandsEnd; ++commandsBegin) {
        Point next = pos + *commandsBegin;
        // cout << "step";
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

    // static int counter = 0;
    // if (counter >= 3) {
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
    // }
    // ++counter;

    start = *points.begin();
}

void MazeGenerator::generateStart() {
    // Point start1;
    // do start1 = getRandomPoint();
    // while (!field[start1.x][start1.y]);

    start = getFurthest(start);

    // if (DEBUG) {   /// ------------------------------------------------------ DEBUG OUTPUT ----------------------------------------
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
    //     // string in;
    //     // cin >> in;
    // }   /// ------------------------------------------------------ DEBUG OUTPUT ----------------------------------------


    finish = getFurthest(start);
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
"ESSESEENEEENNNNWNNEEEEEWNNWWNNWWNWNEWWSSWSEWSSWWSNNWNWNWENNENEENWWENWWSWNWNWNEESENESENEESESWSENENENENEESSWESSSESSWWWWSSEESSESNENENNENNWWNNEWSWWNWSSWNNENWWSSSEEENNNEENEESEESSEESNEESWNWNWSNNWWWSSNWNNWSWWNWNWWSSSWWEESESSEWSSESWWNNSWWSSESWNWSWSNENWNNNNWWNWWWENENNEEWNWNEESEENEESNEENNWNESEENSSESSSWSESESEESESNEENEENEWWWSSWSWSWWNNWNWSWNNENEWNWNWSSWSSESWWNSEWWWNNNENWWSSWSSNWNWNWNEEENEESEESNENENESSSESENENNNENEWWNNNEWWWWSSNWWNSSWSWSWENENESSWESNESESESNESEWWSEWWWSWSESEENENENSSWWSSWWSNWNWWWNEWSSSEWWSSNWNWNNENNEWNNWNWSSSWEESESSSEESESENEESWSSWESSEENNEESEESNWNEENWWNEENNEWWSWWSNWNWNSWNWWWENWNSSESESSSEWWSSEWWNNNENENENNEEENSSESESESWSWSWSNWWSSEESWSESSEEESWWNNWSWWNWNENWWNEESNNWNWEESENENESESSNENENNNNESSSWENESENENSSSEWWSWSWNWSSESWSESSEESESESNESENNWNEWWNENEESNNENWNWSWWWNSSWWSNNWNNWSWWSWNWNENNEEWNWNWSNNENESESEESSNNNWWEEEENSSESSEEWNSWSWWNWSWSNWNWNSWSSWSSWSWEESEEWSSSSWSWSESEENEWNWNNSWNNWEEENENNENWWWSNNEENESEESSNNWNNENWNWWNNEENSSWSSESESEENESEEENNWNEWWNNWWWWSSNWSWSWNNSSENESESESWESWWWESEWSWWSWSNWNSSESSSEESNENEESESEWWSWSWEESEWSWSWNWSNWNSWESSEWSNWWNNWSWSNNWNNEWWNWSNNNNEWNWSWNSWNSWWSNWNENENWNWWSSNNEENNENSEESENENWNEENSSESSSENSWNEEEWSSSEWWNWSNWNSWSWNNSSSESSSWWSSWNNNNENENNSNWNWEENSEESESNNEENWNEWWWSWNSWSWNNWEEENENEESESNENEESSNNEWWNSSSWWSSNWNWNWSWNSSSEWWSSNWENWWNENWEENEWNWEENEESEESNENESSSNESESSWSSWWEESESESNNNWWNEWWSWNNSWNWENESEESENENSEESSWENESESWSWSSNNWSNEWWSWSWSNWSSESEWSSWEENESSEESNNNEWSWSWSWSNWWNNNWNWNSWSSWESEESNENENENSEESEEWSEESNNENESESEENNWENENNWNWNWWNSWSWWSWWSWSSSEWSESEWNWNWNENWNEENENWENESSESNNEEESSWNWWNSWENNNWENEESENSSESSSESNENEWNWSNWNWNSWWSNWNEEWNWSWSNWSWNNWNSSESSESWSSWEESNWWSWSWESEEWSWSWNEWNSWSWNNEENSEESESESENESNNEESSSWWESNENSESESWSEWSENSSSWWNSEWWSNEWWWNSSESENSWWESEWWSWNSSENESESENENNENNWNNWNWNENEENSESNESESNESSESWSWESSSWSWNWNWWWSSSESSWESSSENENEWNNWNWNWSNNWWNEWWNWENNENWNEEWWWSNNWNWNSWSWSNWWNNWEEESSENESNESSESESEWSNENEWNENWWNNEWNWNWEEENEWWSWWNSSESEESEWSSSWSWESESENSESESENENWWWNEWWNSSEWSWWSNWENNWENENSENNSESESESNENENNWEENNWESSWSWSWNNNWWWSNNWNWWSNWWNEWWNSWSWSSWENENENEWNWNWNWNSSWSWNSWWSESSSESNESEWSSWSESWSEEWSWWNSWSSEENENESNENSEESSEENWWSWNENWSSEEWSSNWWNSWNNWNSWSSWSNWNWSNNENNWEEENSEESSESSESWWESESENNNNEEWNWNWNWNNEEWNESESNEENEWWSNNWNWWENNWENESESSWWSSSWEENESENSSSWSWSSWEESNEWWNNWNWSSWNSWSESSSEENSEWSSWSNWENNENNNWWNSSWSSSEESEESWENNWNWNWNWWSNENNWNENWNWENENESEENNNWESEENSSESWSSEENNNSWNWWWSWWSNNWNNWWWNSSENNENEWNNWWSSSWSWESESEESSENWWSWSWWSWSNWNNWNWENENENESENSNEENENEEEWWSWNNWSWSSWSWENSSWSWSSESWESESESNENESSEEWSWESESENNWNENWWNEEWNWSNEENNNEEESSESEESNNWENNWEEESENSSSWESENEWNWEESNNENWNWNWSWWNWNWENNWNWWWNSSWSWSESEWSWSESEWWNSWSSEWNNENWEEESENENNESESSSWWSEESEWSWEESNESNNNNWWSWSSEWWSWNSSSEEWEESEWSNWWNWSSNNWWNSSWESWWWSESWNNSEEWNEWNWNSSWESSEWWSNWSNNNENENEWNNWSWSSSWSWNWSSEENEENEESESWSWSSEWSEENNWENESENNSSWSWWESWNWSSWWSSWNWNNEWNWSNNNENNNWEEENESEENNENEWNWNWWNSWWNENWNWNSWSWNWNNEWWNSWSESESESWEENESNWNEESSESEWSSWSNWNWNSWWNWENENESENWNWENNENWWENESNNEESSEWWSWSSEESESSWWWNWEEENSEENENSESSSENWENWNNEWWNSSNWWSNWWSWNNEWNENWNEENWENWNESESESSNWEEENNSSWSWESEEWSWWSNWWSEWSWSWSEEESENENSSWWNNWNSWWNWNNSSESESSWEENENENNNWNWNWWNWSWWNWSWSENSSWNWSNNWSWSSWSNNEWNWNNEENENWWNENWSNWNWNWSWSENWWNSSWESSWSESEENSEWWNSSSEENSEWSWSEESWWNSEENEWWWSNNWWSSWESESESSWWNWSWNNSSESEWNENEENWNWEESESWEEESNNENENSSENESWSSWESWSWWSEWNSSWWNWENWWNSWNNNWNEEENNWWWNEENEWNNENSENENENENSSEWWSSSWNSEESEENENNWWNWNWEEENENWEENESESSWSWESEESWSESWSNNWWSWNSWSWSWWWSESESWENESSNEESSNENNWNWEENWWWNNWNNWSWSSNNWWENEEENSENNSSENEENNEWWNENWWSWWSNWNNWWSWSSEWSNWSWNENWENENENEWWNWSSESESEESEWSWSWESSESESNNENEWWNWWSSWWNNWWSSWWSEEWSSEWWSENWNENNWWEENEWNWSWNENENNEEWWSNWSSNWSSEWWWSNWNNWENEENEWWSSSSNWSWSESSWSESESWESENENENNSENESSNNESESEEESWSWSEESNNESESNEENWNWEENNNWEENENNWNWSWSWNNWWWENNENESNESNEESNWWSWSWSSEWSWNNWEENSEESSEESSESEWSEWWNWNSWSSESEWSWNNWSSESWNEWNWNWWSSEWNWSSEENNWNNNWENNNNEENSESWSSWEENSESSSWEENNSSWWNSWESSEWWWSWWNNENWSSEEWSEESESSENNSEENEENNWWENNESSENSESWWNWWSWNWNENWWNNWEENSNEESENWWNSNWENENESESEEESSSNNWWWNWENWENWWSWWWSEWSSWNENWWNWWEENENNEWNESNESESWSSESESSWEESNNNEWWWWSSNWWSSNWWNSWSWSWSNNEWWNNENEWNWSNWSSSNWSWESWESEWSSSESEWWWNSWSSEENSEEENENSSWEENENSESSESSEWWWNWNWSSWESEENESSSNESEWWNNSWSWESENNESNENEEENNNNESEESWEENNWNWNWWSWNNWNENWEEESEESENNWENEWWWSWSWNWWSWSWNNEWSSEEESSWENESESSNENESESEWWNSSWWWNNENWSNNNEWWNSWSWWSNWNWNENWNWWWSSSWWSWSNWNWWNWEENESNNEWNWSWSNNNWSWSNNEENSSEENSSENESEESSNEEENWESESEWSNWSSNNENENESESEESSNENESSENSSWSEWWSWSEEWWNWNSSESWESEWWWSSWSWWNWNNENENNNSNEWWWNWNWEEESSSNNWEESNENEEWWNNWENNWSSWSNNNWENEENEESSWSESENESNNNEESSWWSWNEWSSWESSESSSWWNWSWNWNNSSEWSEENNEWWWENWNENWEENNNWWWSNWNNENENWWWENWSNNENENESEESSEWSSWSWWNWSSWSSWESESSESSWEENESSWEENENEWNNWNWSWWNNEWWNENENESEESESSWSWWNWNWNWSSWSSEESESWWNSWSWNSSWSNWNNENNWWEESENENWNWWSNNENNWEENESENSEENNWWWENWWNWNWSWSWSWESESEWSWSWSESEWSWNWNSEWWSESSENSENENENSENENNEESSWSWSEENSEESSSESWWSEENEESENENENNWENSSEWWSSESSENWNNEEENEENNWWNEWNNWENESENSSSSWSSEESNESSWWEESWSWESWWWSWSWNWWWSESSEWSWNWNWNNSWNNENEENNENENWEENSSENSESWSWWESENESESENEENENWWENENWWWNSSWSSWEESSESSWSWNWNNWNEEWWWWSSSWSEWSWEEENEENENEENSSEWSWSWESWESEWSWSSWNWWSWSWNWWNWNWENENENEESESWNNNWEEENENEENNESSESESSSSWSESENWNENENWENWWSNWEEESEENNSSSWSWSESSWSWWNWSNWSWSWESWESWEEENENSSEWWNWEENSSSSWWWWSSWSWSEESNESSWSSWWSEWSESESEEESSSWWSSEWNNNWNWNNWEENWEESEESSESWSESEENNNNWENESNWNEWNNWNEEESESSWESSEESNWENEENWNWWNWNENENEWNWNSSWWWWSWSESNWNWWSWNWWNSSWENESSESENSSWWENSSWSNWNNWWSSNNWENEWNWWSSWNSSEESESWSWSEEESNWNWWENNWNENNNWWWSNWSSSEEEESESEESNEEENSWESSSESWENEWENENNWESSESWSWWWNSESWESESEWWNWSNWSWSWNSSEWSWSNNNNWSNNNNNENWENNEESENENWWNENENSENEENWEENSSEWSSWSESENSWSWSWENSSWEEENENNWWSWSENWNNWENNENNWNWSWNENENWWSSWSWSWESESSESWWNWWSWSNNNWSSEEWSSWWEEENSSEENESEESSESNNEWNNWNWNWEEESNEESENENEWWNWWNEWNSWWSSNWNEWNWNEWNENEESENEENSSESESWWNSEWSESSWSSWWSWWWNEENNSENSSWSWESWSEWSWWSWSWSNNWNWWSNWSSEWSWEEESESNENSNNEWWSWSSWSESEWSWSWNSESESNENESEESWSWSEWSEWSWNWNNNWWNSSSWSNNENEENNWNWWNNNEESENESENNNSEESSSESENESNEESNNWENWNWNWSWSWNSWNWWNWENEEEESESENESESSSSWSSESSEWWSNWEESSSWWNWWSSESWSWWNNNWSWNWNWSWNWSSSWSSESWSWSNEENENENEEESSESWSWSWSSWESENENSSSSENNWEESSNESENNESESESWWSNWSSSEENNSWSWWWNWWSSENNNEEENNENNNWNWENEWEENNSESWSSWSESWESEWWSSWWESENEENWNNWENESNEESSNNWNNWWNNENEENENWWWWSSNWNWWNWWNSWSWNWNWNSWNWWENEESESSESSENEENSSEWSWSSEWSWNWNNWNWSWSWWSSESSWSEESNWEESESWESESSEEEWSWSSEWSWWESENESNNENNWNWNWSWNWNWEEESNENENWNEENSSESWSEEWWSSNWSWSSESESWESEESSSEWWNSSENENNENENWENWWNSSSWWSWNNEENNWENNWNENWWWWENEEENEWWSSNSESESESSWENWNWNWEESENNWWWNWWNSWSWSWNNWNNSSWSNWNEEWWNWNSSWSWESESWESWWEENEENSSEESSWSSESENEWNNNNEENEEEESSEWWSSWWSNENESNNWNWNEESESESSSWWSEWWSWESESSEEESNEEWSSWESWESWSEWWSSWNWNNENNEENNWNWNWWNEENNNEWWWNSWSEWSNWNWSWSNWNNENENESESESNNENENWWWEEENNSESSWSNNWEEESEESWSSWWEENNSSSWSSWSNWSEWSEENSWWSWSESWESENSSESNNNWENENNNEWNWWEEESWEENNENNEWWWWNWSWWSWSSESESSEWSWWNSESWENWNNNENWWSSSWNWSESSWEEESSNENWNNEWNNWNEEESEENNNEEESEESNENWNENEWNNWWWSWSNWNEENEENSEESENSSSWSESSWWSWSWNWWWSWESSWEENESSWWESWSNWSSWSWSEESNENNSSSSEEENNENNWWSSESEWSWWNNWNWWSWWSEESSESESSESSEWWNNSWWNWWNNWNNNEENNNWNWWENNNEEEWNWNNSWSWSNWSWESSEWSWSWNNNENNWNNWEENENEENNENSESWNWENWWSWSWESWNNEWNSSWSSESSWSWSSESWWNENWNNNWSSNNNWEENNWWSSSNWNENEWNNWWNNWNEEENSSEEWSEESENESNENWNNESSESWSSSWNSEWWSSWEESSNEWNWNEWENWEENSESESEWWSWSWNWSESWEESENNNESNWNWWWNSNWWSNNEWNWWSWSEWSSWEESENSSEWSESENWWSSWSNWNNWNENNWEESESESSSWEENNNNNWWNWNSSSSWWSSWNWWNEEWWNWENENNWNNNWSWSEWSSWWESSESWWSWNWNSSEESENSESEENENNENNESSEWSWSWSSESESWESEWNWWNNWSNNENENWEEESSEEENNSSWSSWSEESSENWEEENNWESENESNNEESSESSESSEWSWNSESESWSEENEWEENNWWSNNEENNNENENSSEWWWNSSWSSESESEEWSWWEEESSWSESSWNWWNWWNNWWWWNWNNSWSSSEESSENSWSWNWNWWSWSSSESEEWENESSEWSSEEENSESEEWWSSNNWNNENEENWWWSWNWNWWNENNNWWSNNWENENESESSESENENENESESSENSWNWWWWSWSSWWESSESESSSWSWNEWWSNNWNNWEEESESNEESNEESSWSSWWSWSESENENENEENSSSWSWWSESENENESNENNWEENSESSWSWWSSWWSNWWWWSWNSSEEENENNNWWNWWSWWNWWSNNEWWSNNNNEENNENWWNEESENWEESSEWWSWNNWENWEESNENWWSNWSWSSWSEESEWWNWNWNNNWWENENENESEENEENWNENEWNWWEENWENENSESESSWENSENEESNNWEESSSWWSWSWSESSSSESWSSESEENWESSNNNNENENWWNWSWWWSWWNSESEWSSWWSSEENENNESEESESWSWSSWNWNSSWEEESSWEWWWSESWSWSESEESSNNWWSSWNSWSSWNNENESESNNNNWWENEENWNNENWWWNWWSWWNNWNSWSSWSSEESSEWWSSESSSWNSWWSSNWNWWNENWSWSSWWNWNWSWSEESSENNENSEESWSWSWSESESNNNENENNWNWNWSWSSNNENEEWNEENEESSESWSWSSESSWWNWNWSSESEWWSWESEWSSESWSWNSNWNNNWEENNWWEEESEEESSSNENESSESEESWESENNEENNWNENNWEESEEESESWWSWNWSWWSWNWWWWWNEWNWWSWWNWWWSNWNNENEEWNEESESESNENWNNEENEWWSWSWNWSSEWNNEWNWENNWWEEESESEENSESNENESESSESWSWSWSWEESENSSWSSWSWSNNEESESENNSSSNEESNENEWNNWEESNENNESSESWNSEENSSEWSWWWNWWSSESSWESESNENNWWNWNWWSWWNNNWEEWWSSWSWNWSWSSNNEWWSNNNNENENEESNWWWNWNNWENWEENEESEEESNESSNNWWNWSSNNWWWSSSEEWWNNSEWWSWNWSSSSWSSESSENESESSWWSEEWSEWSSESESWENWNEESNWNWNENEWWWWSSESSEESEWSEESSESNNEWWWNNEWWNSWSWSNSSSEESSWSWWSSNWNSWWSWESESSWEENEENEESSNNNEESESEESENEEESSSSESSWSWSNWNNSWSEEWSWNNWWWSSESESWSENESEENSSWSSESWWWSSWNNWSSESESSEESEWNNEENWWSNNNNNEENENEEESSENEENEESESSWSSSENEESESSENNENWWSWWNNWNWNNWWSNWWWWNWNSWWNENESENWWEENWWNSSSESEWSWSWNNWNSWSSSEWSWWSNWNSWWNESESENSENNWNNENEEESESEESSWWSWESWWSEWWSWSNWWSSESESEWSWWSNENENNEWWNWNWENNEEESNENEENWNWWNSSWWSSNWNSWSSEWSSESEESSESEENEENESSESEWWSWSSESEENWNWNWWNWNEWENEWWSWWNSSESSSESEWSWSSESWEESWWNWNWNEWNWSWWSSWNWWWWSSSEESNSESSESNNENWNWNNEEENSSNENSNENEENNWESSSEWESSESESEESESWSWSWSWSSNWNWWNWNWWSWWNSSEESEESNENEEESSSEEENEESSWSWNNEENEENWEWWWNWWSWWWNWWWSSESEEESSEESEENSSWWNNSSWWNSSEENENESEENSSWSSESSEEENSSWSWNSSSEWWNSSSWSSEENENWWSSSWSESEEEEENEEESESWNNEENNEENWWSNNENESENSSSWSWNNNENEESNEESESEEENNWWNNWEWSWWWSWWSSWWNSNWWSWSSWEESNSESESEEWSWNWWNSSWSSESWWSSWSNWNENEEEWWSSWENEEWNWNNEEWWNWWSWSESWSSWSESEENSSESESEEWSSWNWWNSWSSWSEENNWNWSWWSNNNEEENNENNWNWSWWSWSSSWSWSNWWSENWNNWENWWNWNNNENEESEENSENEEENESENWNEESSEEENSSWSSSEESSNEENWESSWSSWWNWNWWNEEESESEWEESSSSWSNWSSWSWNWESSSWWWSEEENESSEEWSSESSWWSSSSWNWNWSNENNEEWNENNWENENWWEESESESEWSSSENESSNENNENWWSNNWNEEENEEWNWWSWSWWNWWNWSWNENWWSSWSEEWWNENWSWSSSESEESWWSWEESEESEWWNEWNWNWNWSWWNNEEWNENEEESESESSESEENNWNEWWNENENESEESEESNEEESSSESSSWENENEESESNEENNWWNWWNWSWNSSWESESESWSWNWNNWNNNEESSNEEESESWSWSSSESWSWNWSWSEESENEENNNWWNWNWNEENNENEESSEEENNWWWWSWSWSWSEESESESSNSSWWSSWSEESSEENNWNWSWWWNNENEWNENWNENENNEESSSWSWNWNSWSWSSSESSWSWSEENENSSENENNENWWSNWNEWWSWWSNWSWWSESWSEWSSSSEENEEESEENEESSSWSWNWNEEWSSWSSSESSEWSSWWSSWNWNWSNNNEEESEENSESNEEENEENWWSSNNWSNNWWNNWWEENENEWEESSNENENESEESNNESSSSEWWSWNESS"
;
