#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <cmath>
#include <functional>
#include <chrono>
#include <cstring>

#include "segtree.h"
#include "pairhash.h"
#include "kmp.h"
using namespace std;

struct ScopedNanoTimer
{
    chrono::high_resolution_clock::time_point t0;
    string title;

    ScopedNanoTimer(string title_)
        : t0(chrono::high_resolution_clock::now())
    {
        title=title_;
    }
    ~ScopedNanoTimer(void)
    {
        auto  t1 = chrono::high_resolution_clock::now();
        auto nanos = chrono::duration_cast<chrono::milliseconds>(t1-t0).count();

        cout<<title<<" cost "<<nanos<<" ms\n";
    }
};

using namespace std;

typedef long long lint;
typedef unsigned long long ulint;


class Solution {
public:
    int maxChunksToSorted(const vector<int>& a) {
        int n = a.size();
        SegmentTree<int> seg(n);

        vector<pair<int, int>>  ap(n); // value index
        for (int i=0; i<n; ++i) ap[i] = {a[i], i};
        sort(ap.begin(), ap.end());
        int res=0;
        for (int i=0; i<n; ++i)
        {
            pair<int, int> p = ap[i];
            seg.set(p.second, 1);
            if (seg.get(0,i) == i+1)res++;
        }
        return res;
    }
};




int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    Solution s;
    s.maxChunksToSorted({0});

}
