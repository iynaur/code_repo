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

template <typename T>
class SegmentTree {
    int left(int i) {return(2*i + 1);}
    int right(int i) {return(2*i + 2);}
    int pa(int i) {return (i-1)/2;}
public:
  SegmentTree(const std::vector<T>& data,
              std::function<T(T, T)> f = std::plus <T>()) {
    this->f = f;
    this->n = data.size();
    // build tree
    levels = 1, el = 1;

    while (el < static_cast<int>(data.size())) {
      el <<= 1;
      ++levels;
    }

    tree.assign(2 * el, T());

    if (0){
        for (size_t i = 0; i < data.size(); ++i)
            tree[i + el - 1] = data[i];

        for (int i = el - 2; i >= 0; --i)
            tree[i] = f(tree[2 * i + 1], tree[2 * i + 2]);
    }
  }

  SegmentTree(int n, T val = T(),
              std::function<T(T, T)> f = std::plus <T>()) :
    SegmentTree(std::vector<T>(n, val), f) {
  }


  T get(int l, int r) {
    return query(l, r, 0, el, 0);
  }

  T get(int index) {
    return tree[el - 1 + index];
  }

  void set(int index, T value) {
    int i = el - 1 + index;
    tree[i] = value;

    do {
      i = (i - 1) / 2;
      tree[i] = f(tree[i * 2 + 1], tree[i * 2 + 2]);
    } while (i > 0);
  }

private:
  std::vector<T> tree;
  int levels;
  int n;
  int el;
  std::function<T(T, T)> f;

  T query(int l, int r, int st, int fi, int node) {
      if (l==st && r==fi-1)
      {
           return tree[node];
      }
    if (l == r)
      return get(l);

    int mid = (st + fi) / 2;

    if (r < mid) {
      return query(l, r, st,  mid, left(node));
    } else if (l >= mid) {
      return query(l, r, mid, fi, right(node));
    } else {
      T lv  = query(l,   mid - 1, st,  mid, left(node));
      T rv = query(mid, r,       mid, fi, right(node));
      return f(lv, rv);
    }
  }
};

// Complete the insertionSort function below.
lint insertionSort(vector<int> &q) {

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

    {
        ScopedNanoTimer t("  ");
        int n = 1000000;
        vector<int> a(n);
        for (int i=0; i<n; ++i) a[i]=rand()%10000000;

        cout<<insertionSort(a);
    }
}
