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

using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef pair<int,int> pii;

typedef vector<lint> vl;
typedef pair<lint,lint> pll;
typedef unsigned long long ul;
typedef vector<ul> vu;

#define mpr make_pair

class Solution {
  int n;
  vu s, t, u, v;

  vu cu, cv;

  vector<vu> a;

  bool isRowSatis(int r){

  }

  void sol(int bid){
    cu.resize(n); cv.resize(n);
    ul vb = 1<<bid;
    for (int i=0; i<n; ++i) cu[i] = u[i] & vb;
    for (int i=0; i<n; ++i) cv[i] = v[i] & vb;

    a.assign(n, vu(n, -1));

    vi satisrow(n, 0);
    vi satiscol(n, 0);


    for (int i=0; i<n; ++i){
      if (s[i] == 0 && cu[i] ||
          s[i] == 1 && cu[i] == 0) satisrow[i] = 1;
      for (int j = 0; j<n; ++j){
        if (t[j] == 0 && cv[j] ||
            t[j] == 1 && cv[j] == 0) satiscol[j] = 1;

        if (s[i] == 0 && cu[i] ){//and
          if (t[j] == 0 && cv[j] == 0){
            cout<<-1; exit(0);
          }
          a[i][j] = 1;

        }
        else if (s[i] == 0 && cu[i] == 0){
          if (cv[j] == 0) a[i][j] = 0;
          else if (t[j] == 0) {

            a[i][j] = 1;

          }
          satiscol[j] = 1;
          satisrow[i] = 1;
        }
        else if (s[i] == 1 && cu[i]){//or
          if (cv[i]){
            a[i][j]=1;
          }
          else if (t[i]) {

            a[i][j]=0;
          }
          satiscol[j] = 1;
          satisrow[i] = 1;
        }
        else {
          if (t[j] && cv[j]){
            cout<<-1; exit(0);
          }
          a[i][j] = 0;
        }
      }
    }

    set<int> needrow, needcol;
    for (int i=0; i<n; ++i){
      if (!satisrow[i]) {

        needrow.insert(i);
      }
      if (!satiscol[i]) needcol.insert(i);
    }

    if (needrow.size() == 1 || needcol.size() == 1){cout<<-1; exit(0);}

//    if (needrow.size() == 0 || needcol.size() == 0)
  }

public:
  void sol(){
    cin>>n;
   s.resize(n);
   t.resize(n);
   u.resize(n);
   v.resize(n);
   for (ul &v: s) cin>>v;
   for (ul &v: t) cin>>v;
   for (ul &v: u) cin>>v;
   for (ul &v_: v) cin>>v_;


  }
};

int tmain()
{
    ios_base::sync_with_stdio(0);    cin.tie(NULL);    cout.tie(NULL);



}
