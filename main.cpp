#include <iostream>
#include <string>
#include <sstream>
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
//#include "leetcode_bintree.h"
#include "leetcode_list.h"
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
typedef vector<int> vi;
typedef pair<int,int> pii;

typedef vector<lint> vl;
typedef pair<lint,lint> pll;

int main_()
{
    ios_base::sync_with_stdio(0);    cin.tie(NULL);    cout.tie(NULL);

    lint n,l; cin>>n>>l;
    vector<pll> ab(n);
    lint minmin = 1e9;
    lint maxmax = 0;
    for (int i=0;i<n; ++i) {
        cin>>ab[i].first>>ab[i].second;
        minmin = min(minmin, ab[i].first);
        maxmax = max(maxmax, ab[i].second);
    }

    sort(ab.begin(), ab.end(), [](pll a, pll b)
         {
             return a.second < b.second;
         });

    vector<lint> sum(n+1, 0);
    for (int i=1; i<=n; ++i) sum[i] = sum[i-1] + ab[i-1].second;

    lint maxmin = l/n;

    //SegmentTree<lint> segb();
    auto checkmax = [&](lint m)
    {
        int id = upper_bound(ab.begin(), ab.end(), make_pair(m,m), [](pll a, pll b)
                              {
                                  return a.second < b.second;
                              }) - ab.begin();
    };


    for (int rmin = minmin; rmin <= maxmin; ++rmin)
    {

    }





}
