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

    Fence(const vector<short>& seq) : stickSeq(seq) {};

    // all counting starts with 0
    // all sizes starts with 1

    size_t seqCount() const {
        return stickSeq.size();
    }

    short seqNSize(int n) const {
        return stickSeq[n];
    }

    Fence push(int n, int nn, int downCount) const {
        vector<short> newSeq(stickSeq);

        if (nn == 0 || nn == seqNSize(n) - downCount) {
            newSeq[n] -= downCount;
            if (newSeq[n] == 0)
                newSeq.erase(newSeq.begin() + n);
        } else {
            newSeq.emplace(newSeq.begin() + n, -7);
            newSeq[n + 1] -= nn + downCount;
            newSeq[n] = nn;
        }

        return Fence(newSeq);
    }

    bool operator<(const Fence& right) const {
        if (this->stickSeq.size() < right.stickSeq.size()) return true;
        if (this->stickSeq.size() > right.stickSeq.size()) return false;

        for (int i = 0; i < this->stickSeq.size(); ++i) {
            if (this->stickSeq[i] < right.stickSeq[i]) return true;
            if (this->stickSeq[i] > right.stickSeq[i]) return false;
        }

        return false;
    }

private:
    const vector<short> stickSeq;
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
        for (int n = 0; n < fence.seqCount(); ++n) {
            for (int nn = 0; nn < fence.seqNSize(n); ++nn) {
                for (int downCount = 1; downCount <= 2; ++downCount) {
                    if (nn <= fence.seqNSize(n) - downCount) {
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

    Fence startFence(vector<short>(1, n));
    map<Fence, int> fenceMap;

    // int grand = countGrand(startFence, fenceMap);
    // cout << "g(" << n << ") = " << grand << endl;
    int grand = 1;

    if (grand)
        cout << "First" << endl;
    else
        cout << "Second" << endl;

    return 0;
}
