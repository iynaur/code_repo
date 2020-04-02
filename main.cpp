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
#include "leetcode_bintree.h"
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


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    leetcode_bintree_test();

}
