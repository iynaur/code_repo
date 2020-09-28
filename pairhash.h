#pragma once
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<lint> vl;
typedef pair<lint,lint> pll;
#define mpr make_pair

lint seed = rand();
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


    std::size_t operator () (const lint &l) const {

        return std::hash<long long>()(l^seed);
    }
};

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

typedef long long ll;
const ll TIME = chrono::high_resolution_clock::now().time_since_epoch().count();
const ll SEED = (ll)(new ll);
const ll RANDOM = TIME ^ SEED;
const ll MOD = (int)1e9+7;
const ll MUL = (int)1e6+3;
struct chash{
    ll operator()(ll x) const { return std::hash<ll>{}((x ^ RANDOM) % MOD * MUL); }
};

template<class TK, class TV> struct RHashTable {
    static const int MAXN =  1000000;
    static const int MAGIC =  654321;
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

    void forall( function<void(pair<TK, TV>)> f){
      for (int i = 0; i < cnt; i++) {
          int hs = used[i];
          for (int e = lst[hs]; ~e; e = prv[e]) {
            f({l[e], x[e]});
          }
      }

    }

    void print(){
      cerr<<"===start===\n";
      function<void(pair<TK, TV>)> out= [](pair<TK, TV> p){
        cerr<<p.first<<" "<<p.second<<"\n";
      };
      forall(out);
      cerr<<"===end===\n";
    }
};

RHashTable<lint, lint> cntpre0;
RHashTable<lint, lint> cntpre1;

void solve(){
    int n= 3e5;;
    cin>>n;
    vl a(n); for (lint &v : a) cin>>v;
    lint x = 0;
    lint mi = 0;
    seed = rand();
    for (int bit = 0; bit < 30; ++bit){
        gp_hash_table<lint, lint, custom_hash> cntpre0;
        gp_hash_table<lint, lint, custom_hash> cntpre;
        lint cntord = 0;
        for (int i = 0; i<n; ++i){
            //            lint v = a[i];
            lint key = a[i]>>(bit+1);
            cntpre[key]++;
            if ((a[i]>>bit)%2 == 0 )
                cntpre0[key]++;
            else
                cntord += cntpre0[key];

        }
        lint tot = 0;
        for (pll p : cntpre){
            tot += p.second * (p.second-1) / 2;
            lint s0 = cntpre0[p.first];
            lint s1 = p.second - s0;
            tot -= s0*(s0-1)/2 + s1*(s1-1)/2;
        }
        if (tot - cntord >  cntord){
            x = x | (1<<bit);
        }
        mi += min(cntord, tot - cntord);
    }
    cout<<mi<<"\n";
    cout<<x<<"\n";
    //    cout<<clock();
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
