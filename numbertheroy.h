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
#include <limits.h>

using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<lint> vl;
typedef pair<lint,lint> pll;

lint gcd(lint a, lint b){

    if (a>b) swap(a, b);
    if (b%a == 0) return a;
    return gcd(b%a, a);
}

void euler(int n, vi &prime, vi &minprime)
{
  prime.clear();
  minprime.assign(n+1, 0);
  for(int i=2;i<=n;i++)
  {
    if(!minprime[i])
      prime.push_back(i),minprime[i]=i;
    for(int j=0; j<prime.size() && i*prime[j]<=n; j++)

    {
      minprime[i*prime[j]]=prime[j];
      if(i%prime[j]==0)break;
    }
  }
}

vi eulerSieve(int n)    // 查找记录2-n的素数
{
    vi p;
    vector<bool> vst(n+1, false);
    for (int i = 2; i <= n; i++)
    {
        if (vst[i] == false)  // 如果未被筛过，则为素数
            p.push_back(i);
        for (int j = 0; j < p.size(); j++)
        {
            if (i * p[j] > n)      // 当要标记的合数超出范围时跳出
                break;
            vst[i * p[j]] = true;     // 将已经记录的素数的倍数进行标记
            if (i % p[j] == 0)      //关键步骤
                break;
        }
    }
    return p;
}

vector<pll> defactor(lint v, const vi& p){// prime,   power
    vector<pll> ans;
    int pid = 0;
    while(v>1){
        int cnt = 0;
        while(v%p[pid] == 0) {
            cnt++;
            v= v/p[pid];
        }
        if (cnt) ans.push_back({p[pid], cnt});
        pid++;
        if (v > 1 && (pid >= p.size() || lint(p[pid])*p[pid]>v)){
            ans.push_back({v, 1});
            break;
        }
    }
    return ans;
}

vector<pii> defactorSPF(int v, const vi& spf){// prime,   power
    vector<pii> ans;
    while(v>1){
        int p = spf[v];
        if (ans.empty() || ans.back().first != p){
          ans.push_back({p,1});
        } else {
          ans.back().second++;
        }
        v= v/p;
    }
    return ans;
}

lint mod = 998244353;
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


int tmain()
{
    ios_base::sync_with_stdio(0);    cin.tie(NULL);    cout.tie(NULL);

    int n; cin>>n;
    vl a(n, 9840769);
    for (int i=0; i<n; ++i) cin>>a[i];
    vl d1(n), d2(n);

    vi p;
    vi spf;
    euler(1e7 + 1, p, spf);

    for (int i=0; i<n; ++i){
      vector<pii> ans = defactorSPF(a[i], spf);
      if (ans.size() < 2){
          d1[i]=-1;
          d2[i]=-1;
      }else{
          d1[i] = mypow(ans[0].first, ans[0].second);
          d2[i]=a[i]/d1[i];
      }
    }

    for (int i=0; i<n; ++i) cout<<d1[i]<<" ";
    cout<<"\n";
    for (int i=0; i<n; ++i) cout<<d2[i]<<" ";
    cout<<"\n";

}
