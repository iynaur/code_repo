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





// Complete the insertionSort function below.
lint insertionSort(const vector<int> &q) {

    map<int, int> cnt;

    for (auto v:q) cnt[v]++;

    auto so = q;
    sort(so.begin(), so.end());

    SegmentTree<int> tree(q.size(), 0);


    lint res=0;
    int n = q.size();
    for (int i=n-1; i>=0; i--)
    {
        int v = q[i];
        auto it = lower_bound(so.begin(), so.end(), v);
        int id = it - so.begin() + (--cnt[v]);


        if (id > 0) res += tree.get(0, id-1);
        tree.set(id, 1);

    }
    return res;

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    palindromeCreation("abc");
    kmpFunc("aasasaaa");

    {
        ScopedNanoTimer t("  ");
        int n = 1000000;
        vector<int> a(n);
        for (int i=0; i<n; ++i) a[i]=rand()%10000000;

        cout<<insertionSort(a);
    }
}
