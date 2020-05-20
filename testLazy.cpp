#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef pair<int,int> pii;

typedef vector<lint> vl;
typedef pair<lint,lint> pll;
typedef unsigned long long ul;
typedef vector<ul> vu;
#define  xx first
#define  yy second
#endif
#include "lazySegtree.h"
#ifndef call_from_test

void CFR1250_C(){
  cin.tie(0);
  ios::sync_with_stdio(0);

  lint n,k;
  cin>>n>>k;

  vector<pair<pii, pll>> s(n); ;
  int len = 0;
  for (int i=0; i<n; ++i){
    cin>>s[i].first.first>>s[i].first.second>>s[i].second.first;
    s[i].yy.yy = i+1;
    len = max(len, s[i].first.second);
  }

  sort(s.begin(), s.end());

  auto f=[](lint a,lint b){return max(a,b);};
  auto g=[](lint a,lint b){return a+b;};
  lint ti=LONG_LONG_MIN,ei=0;
  SegmentTree<lint, lint> seg(f,g,g,ti,ei);

  const int sz = len + 3;
  vl init(sz, 0);
  for (int i=0; i<sz; ++i) init[i] = -k*i;
  seg.build(init);

  lint maxp = 0;
  int ll, rr;
  for (int i = n-1; i>=0; --i){
    int cur = s[i].first.first;
    while (i >=0 && s[i].first.first == cur){
      int end = s[i].first.second;
      seg.update(end, sz, s[i].second.xx);
      seg.print();
      i--;
    }
    i++;
    lint cmax = seg.query(cur, sz) - init[cur-1];
    if (cmax > maxp){
      maxp = cmax;
      ll = cur;
    }
  }

  cout<<maxp<<endl;
  if (maxp == 0) return;
  cout<<ll<<endl;

//  for (int i=ll; i<sz; ++i){
//    if (seg.query(i, i+1)== maxp + init[ll-1]) rr = i;
//  }
//  cout<<rr<<endl;
  auto it = lower_bound(s.begin(), s.end(), make_pair(pii({ll, -ll}),pll({0LL, 0LL})));

  sort(it, s.end(), [](pair<pii, pll> p1, pair<pii, pll> p2){
    return p1.first.second < p2.first.second;
  });

  vl ans;
  lint pp = 0;
  for (; it != s.end(); it++){
    pp += it->second.xx;
    ans.push_back(it->yy.yy);
    if (pp == maxp + (it->first.second - ll +1)*k)
    {
      rr = it->xx.second;
      break;
    }
  }
  cout<<rr<<endl;

  cout<<ans.size()<<endl;
  for (lint & i : ans) cout<<i<<" ";


}
/*
  verified on 2019/10/28
  https://codeforces.com/contest/1179/problem/C
*/

signed main(){
  CFR1250_C();
  return 0;
}
#endif
