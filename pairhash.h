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
    long long l = p.first;
    l = l << 32;
    l = l | p.second;
    return std::hash<long long>()(l);
  }
};
using namespace std;
typedef unordered_map<pair<int, int>, int, pair_hash> umapii;

using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<lint> vl;
typedef pair<lint,lint> pll;
#define mpr make_pair

template<class TK, class TV> struct RHashTable {
    static const int MAXN = 10000000;
    static const int MAGIC = 7654321;
    int ptr;
    int lst[MAGIC];
    int prv[MAXN];
    TK l[MAXN];
    TV x[MAXN];
    int cnt;
    int used[MAGIC];

    RHashTable() {
        ptr = 0;
        fill_n(lst, MAGIC, -1);
        cnt = 0;
    }
    void clear() {
        ptr = 0;
        for (int i = 0; i < cnt; i++) {
            lst[used[i]] = -1;
        }
        cnt = 0;
    }
    TV& operator [] (const TK& key) {
        int hs = (key % MAGIC + MAGIC) % MAGIC;
        if (!~lst[hs]) {
            used[cnt++] = hs;
        }
        for (int e = lst[hs]; ~e; e = prv[e]) {
            if (l[e] == key) {
                return x[e];
            }
        }
        l[ptr] = key, x[ptr] = 0;
        prv[ptr] = lst[hs], lst[hs] = ptr;
        return x[ptr++];
    }
    int count(TK key) {
        int hs = (key % MAGIC + MAGIC) % MAGIC;
        for (int e = lst[hs]; ~e; e = prv[e]) {
            if (l[e] == key) {
                return 1;
            }
        }
        return 0;
    }
    void erase(TK key) {
        int hs = (key % MAGIC + MAGIC) % MAGIC;
        int nxt = -1;
        for (int e = lst[hs]; ~e; e = prv[e]) {
            if (l[e] == key) {
                if (!~nxt) {
                    lst[hs] = prv[e];
                }
                else {
                    prv[nxt] = prv[e];
                }
                return;
            }
            nxt = e;
        }
    }
};

RHashTable<lint, lint> cntpre0;
RHashTable<lint, lint> cntpre1;

void solve(){
    //RHashTable<lint, lint> cnt;  //will crash duo to stack size issue
    int n;
    cin>>n;
    vl a(n); for (lint &v : a)cin>>v;
    lint x = 0;
    lint mi = 0;
    for (int bit = 0; bit < 32; ++bit){
        cntpre0.clear();
        cntpre1.clear();
        lint cntord = 0; lint cntrev = 0;
        for (int i = 0; i<n; ++i){
            lint v = a[i];

            if ((v>>bit)%2 == 0 )
            {
              cntpre0[v>>(bit+1)]++;
              cntrev += cntpre1[v>>(bit+1)];
            }
            else
            {
              cntord += cntpre0[v>>(bit+1)];
              cntpre1[v>>(bit+1)]++;
            }

        }
        lint tot = 0;

        if (cntrev >  cntord){
            x = x | (1<<bit);
        }
        mi += min(cntord, cntrev);
    }
    cout<<mi<<"\n";
    cout<<x;
}

int main()
{
    ios_base::sync_with_stdio(0);    cin.tie(NULL);    cout.tie(NULL);

    int t=1;
//    cin>>t;
    while(t--){
        solve();
    }

}
