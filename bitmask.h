#include <bits/stdc++.h>

using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<lint> vl;
typedef pair<lint,lint> pll;

#define mpr make_pair

int bitcnt(lint v){
  return __builtin_popcountll(v);
}

lint nextSubMask(lint mask, lint sub){
  return (sub - 1) & mask;
}

class Solution {
    int n, k;

    int N;

    vector<int> cando;
//    vector<int> cvst;
    vector<vector<int>> dep;
    vi need;
    vi dp;

    int Cando(int mask){
        if (cando[mask] != -1) return cando[mask];
        int res = 0;
        for (int i = 0; i<n; ++i){
            if (mask & (1<<i)) continue;

            if ((mask | need[i]) == mask) res |= (1<<i);
        }
        return cando[mask] = res;
    }

    int res(int mask){
        if (dp[mask] != -1) return dp[mask];
        int can = Cando(mask);
        if (can == 0) return dp[mask] = 0;

        int need = min((int)bitcnt(can), k);
        int ans = n;
        for (int sub = can; sub; sub = nextSubMask(can, sub)){
          if (bitcnt(sub) == need){
            ans = min(ans, res(mask | sub) + 1);
          }
        }
        return dp[mask] = ans;
    }

public:
    int minNumberOfSemesters(int n_, const vector<vector<int>>& dep_, int k_) {
        n = n_; k = k_;
        N = 1<<n;
        dep = dep_;

        cando.clear();
        cando.assign(N, -1);
        need.assign(n, 0);

        for (vi & dp : dep){
            need[dp[1] - 1] |= 1<<(dp[0]-1);
        }

        dp.assign(N, -1);

        int a = res(0);

        return a;

    }
};
