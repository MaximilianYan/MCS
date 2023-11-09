#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

int mex(const vector<bool> grand) {
    for (int mex = 0; mex < grand.size(); ++mex)
        if (grand[mex]) return mex;

    return -1;
}

int mex(const set<int>& nums) {
    for (int mex = 0; mex < 300; ++mex)
        if (!nums.count(mex)) return mex;

    return -1;
}

class Fence {
public:

    Fence(const set<short>& seq) : stickSeq(seq) {};

    // all counting starts with 0
    // all sizes starts with 1

    size_t seqCount() const {
        return stickSeq.size();
    }

    Fence push(int n, int nn, int downCount) const {
        set<short> newSeq(stickSeq);

        if (nn == 0 || nn == n - downCount) {
            newSeq.erase(n);

            if (n != downCount)
                addSeq(newSeq, n - downCount);
        } else {
            newSeq.erase(n);

            addSeq(newSeq, nn);
            addSeq(newSeq, n - nn - downCount);
        }

        return Fence(newSeq);
    }

    bool operator<(const Fence& right) const {
        return this->stickSeq < right.stickSeq;

        // if (this->stickSeq.size() < right.stickSeq.size()) return true;
        // if (this->stickSeq.size() > right.stickSeq.size()) return false;

        // for (int i = 0; i < this->stickSeq.size(); ++i) {
            // if (this->stickSeq[i] < right.stickSeq[i]) return true;
            // if (this->stickSeq[i] > right.stickSeq[i]) return false;
        // }

        // return false;
    }

    const set<short>& getSeq() const {
        return stickSeq;
    }

private:
    const set<short> stickSeq;

    static void addSeq(set<short>& seq, short n) {
        if (seq.count(n))
            seq.erase(n);
        else
            seq.emplace(n);
    }
};

int countGrand(const Fence& fence, map<Fence, int>& fenceMap) {
    if (fenceMap.count(fence)) {
        return fenceMap[fence];
    }

    int grand = 0;
    if (fence.seqCount() == 0) {
        grand = 0;
    } else {


        set<int> grandNums;
        for (short n : fence.getSeq()) {
            for (int nn = 0; nn < n; ++nn) {
                for (int downCount = 1; downCount <= 2; ++downCount) {
                    if (nn <= n - downCount) {
                        grandNums.emplace(countGrand(fence.push(n, nn, downCount), fenceMap));
                    }
                }
            }
        }
        grand = mex(grandNums);
    }


    /*{
        for (int n = 0; n < fence.seqCount(); ++n) {
            for (int nn = 0; nn < fence.seqNSize(n); ++nn) {
                cout << "|";
            }
            cout << "_";
        }

        cout << " : (" << grand << ")" << endl;
    }*/


    fenceMap.emplace(fence, grand);
    return grand;
}

int main() {
    int n = 0;
    cin >> n;

    Fence startFence(set<short>({ (short)n }));
    map<Fence, int> fenceMap;

    int grand = countGrand(startFence, fenceMap);
    // cout << "g(" << n << ") = " << grand << endl;
    // int grand = 1;

    if (grand)
        cout << "First" << endl;
    else
        cout << "Second" << endl;

    return 0;
}
