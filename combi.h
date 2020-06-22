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
#include <bits/stdc++.h>


using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef pair<int,int> pii;

typedef vector<lint> vl;
typedef pair<lint,lint> pll;

#define mpr make_pair

lint mod = 1e9 + 7;
lint mypow(lint a, lint n){
  lint res = 1;
  lint base = a;
  while(n > 0){
    if (n%2) res = res*base%mod;
    base = base*base%mod;
    n = n/2;
  }
  return res;
}

lint rev(lint a){
  return mypow(a, mod-2);
}

struct ComBi {
  ComBi() = delete;
  explicit ComBi(int n){
    la.assign(n+1, 1);
    for (int i=1; i<=n; ++i) la[i] = la[i-1]*i%mod;

    rela.assign(n+1, 0);
    rela[n] = rev(la[n]);
    for (int i=n; i>=1; --i) rela[i-1] = rela[i] * i % mod;

  }

  lint comb(lint n, lint m){
    return (la[n] * rela[m] % mod) * rela[n-m] % mod;
  }

  vl la, rela;
};




int main()
{
    ios_base::sync_with_stdio(0);    cin.tie(NULL);    cout.tie(NULL);

    int k; cin>>k;
    string s; cin>>s;
    int n = s.size();

    ComBi cb(2e6 + 5);

    lint ans = 0;
    for (int l = n-1; l<= n + k-1; ++l){
        lint base =  cb.comb(l, n-1) * mypow(25, l - n +1) % mod;
        base = base * mypow(26, n + k - l-1) % mod;
        ans = (ans + base)%mod;
    }
    cout<<ans;


}

