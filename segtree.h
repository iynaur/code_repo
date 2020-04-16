#pragma once
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


  T get(int l, int r) {//index [l. r]
    return query(l, r, 0, el, 0);
  }

  T get(int index) {//index [0, n)
    return tree[el - 1 + index];
  }

  void set(int index, T value) {
    int i = el - 1 + index;
    tree[i] = value;

    while (i > 0) {
      i = (i - 1) / 2;
      tree[i] = f(tree[i * 2 + 1], tree[i * 2 + 2]);
    }
  }

private:
  std::vector<T> tree;
  int levels;
  int n;
  int el;
  std::function<T(T, T)> f;

  T query(int l, int r, int st, int fi, int node) {
      if (l<=st && r>=fi-1)
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
