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

    {
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


using namespace std;
class Solution {

public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.size(), k = queryCharacters.size();
        multiset<int> ms;
        set<pair<int, int>> sp;
        for (int i = 0, j = 0; i < s.size(); i = j) {
            while (j < s.size() and s[i] == s[j]) j += 1;
            sp.emplace(i, j - 1);   // [left, right]
            ms.insert(j - i);
        }
        vector<int> res(k);
        for (int i = 0; i < k; i += 1) {
            int p = queryIndices[i];
            char c = queryCharacters[i];
            if (c != s[p]) {
                auto pr = *prev(sp.upper_bound(make_pair(p, n)));
                ms.erase(ms.find(pr.second - pr.first + 1)); // remove cur seg
                sp.erase(pr);
                if (pr.first < p) { // add left seg
                    sp.emplace(pr.first, p - 1);
                    ms.insert(p - pr.first);
                }
                if (pr.second > p) { // add right seg
                    sp.emplace(p + 1, pr.second);
                    ms.insert(pr.second - p);
                }
                s[p] = c;
                int L = p, R = p;
                if (p + 1 < n and s[p + 1] == c) { // merge right
                    auto it = sp.upper_bound(make_pair(p, n));
                    R = it->second;
                    ms.erase(ms.find(it->second - it->first + 1));
                    sp.erase(it);
                }
                if (p and s[p - 1] == c) { // merge left
                    auto it = prev(sp.upper_bound(make_pair(p, n)));
                    L = it->first;
                    ms.erase(ms.find(it->second - it->first + 1));
                    sp.erase(it);
                }
                sp.emplace(L, R);
                ms.insert(R - L + 1);
            }
            res[i] = *ms.rbegin();
        }
        return res;
    }
};
