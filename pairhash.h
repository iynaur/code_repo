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

struct pair_hash {
  template <typename T1, typename T2>
  std::size_t operator () (const std::pair<T1, T2> &p) const {
    std::size_t h1 = std::hash<T1>()(p.first);
    std::size_t h2 = std::hash<T2>()(p.second);
    return h1 ^ h2;
  }

  std::size_t operator () (const std::pair<int, int> &p) const {
    long long l;
    memcpy(&l, &p.first, 4);
    memcpy((char*)&l +4, &p.second, 4);
    return std::hash<long long>()(l);
  }
};
using namespace std;
typedef unordered_map<pair<int, int>, int, pair_hash> umapii;
