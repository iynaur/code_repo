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

using namespace std;

typedef long long lint;
typedef vector<int> vi;
typedef pair<int,int> pii;

typedef vector<lint> vl;
typedef pair<lint,lint> pll;

class mset { // choose biggest k value
  multiset<lint> candi;
  multiset<lint> choose;
  lint sumc = 0; //
public:
  void insert(lint v){
    if (choose.empty() || v <= *choose.begin()){
      candi.insert(v);
    } else {
      choose.insert(v);
      sumc += v;
      candi.insert(*choose.begin());
      sumc -= *choose.begin();
      choose.erase(choose.begin());
    }
  }

  lint sum(){
    return sumc;
  }

  int size(){
    return choose.size() + candi.size();
  }

  bool inc(){
    if (candi.empty()) return false;
    choose.insert(*candi.rbegin());
    sumc += *candi.rbegin();
    candi.erase(prev(candi.end()));
    return true;
  }
  bool pop(lint v){
    if (candi.count(v))
    {
      candi.erase(candi.find(v));
      return true;
    }
    else {
      choose.erase(choose.find(v));
      sumc -= v;
      return inc();
    }

  }
};


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        lint s; cin>>s;

        int m = n/2;
        vector<pll> p(n);
        vector<pair<lint, pll>> eve;
        lint base = 0;
        for (auto &pl : p){
            cin>>pl.first>>pl.second;
            eve.push_back({pl.first, pl});
            eve.push_back({pl.second+1, pl});
            base += pl.first;
        }

        sort(eve.begin(), eve.end());

        mset candi;
        int cnt;
        int had = 0;

        lint ans = 0;

        for (int i = 0; i< 2*n; ++i){
            pair<lint, pll> cur = eve[i];
            if (cur.first == cur.second.first){
                candi.insert(cur.first);
                if (had + candi.size() > m) candi.inc();


            }
            else {
                if (!candi.pop(cur.second.first)) break;
                had++;
            }

            if ( i+1 < 2*n && eve[i+1].first != cur.first){
                int need = candi.size() - (m - had);
                if (need <= 0)
                  ans = max(ans, eve[i+1].first - 1);
                else
                {
                  lint lv = (s-(base - candi.sum()))/need;
                  if (lv >= cur.first)
                    ans = max(ans, min(lv, eve[i+1].first - 1));
                  else
                    break;
                }
            }
        }
        cout<<ans<<"\n";

    }
}
