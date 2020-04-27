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

lint mod = 998244353;
lint pow(lint a, lint n){
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
  return pow(a, mod-2);
}

lint comb(lint n, lint m, vl la, vl rela){
  return (la[n] * rela[m] % mod) * rela[n-m] % mod;
}

int main()
{
    ios_base::sync_with_stdio(0);    cin.tie(NULL);    cout.tie(NULL);

    lint n, k;
    cin>>n>>k;

    vl la(n+1, 1);
    for (int i=1; i<=n; ++i) la[i] = la[i-1]*i%mod;

    vl rela(n+1);
    rela[n] = rev(la[n]);
    for (int i=n; i>=1; --i) rela[i-1] = rela[i] * i % mod;


    if (k == 0){
      cout<<la[n]<<endl;
    } else if (k <= n-1) {

      k = n-k;
      lint ans = 0;
      for (lint i = 0; i<=k-1; ++i){
        lint p = ((i%2 == 0)? 1LL : -1LL)*pow(k-i, n) * comb(k, i, la, rela) % mod;
        ans = (ans+p)%mod;
      }
      ans = ans*comb(n, k, la, rela)%mod;
      cout<<2*(ans + mod)%mod;
    }
    else cout<<0;
}
