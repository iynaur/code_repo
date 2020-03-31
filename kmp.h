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
using namespace std;
vector<int>  kmpFunc(const string &s)
{
  int n = s.size();
  vector<int> a(n, 0);// a0=0 a1=1   a(n-1)=n-1;
  for (int i=1; i<n; ++i)
  {
    int candi = a[i-1];
    while (candi > 0 && s[i] != s[candi]) candi = a[candi-1];
    if (s[i] == s[candi]) a[i]=candi+1;
    else a[i]=0;
  }
  return a;
}

int palindromeCreation(const string& s) {
  int n = s.size();
  auto rs = s;
  reverse(rs.begin(), rs.end());
    auto res = kmpFunc(s+"_"+rs);
    int min = n-res.back();
    res = kmpFunc(rs+"_"+s);
    min = std::min(min, n-res.back());
    return min;
}
