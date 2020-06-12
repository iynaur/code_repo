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

vi eulerSPF(int n)
{
  vi prime = eulerSieve(n);
  vi minprime(n+1, 0);
  int c=0,i,j;
  for(i=2;i<=n;i++)
  {
    if(minprime[i] == 0)
      minprime[i]=i;
    for(j=0; j<prime.size() && i*prime[j]<=n; j++)
    {
      minprime[i*prime[j]]=prime[j];
      if(i%prime[j]==0)break;
    }
  }
  return minprime;
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

int main()
{
    ios_base::sync_with_stdio(0);    cin.tie(NULL);    cout.tie(NULL);

    int n; cin>>n;
    vl a(n);
    for (int i=0; i<n; ++i) cin>>a[i];
    vl d1(n), d2(n);

    vi p = eulerSieve(1e4);
    vi spf = eulerSPF(1e7 + 1);

    for (int i=0; i<n; ++i){
      int p = spf[a[i]];
      int pp = 1;
        while(a[i]%p == 0) {
          pp *= p;
          a[i] /= p;
        }
        if (a[i] == 1){
            d1[i]=-1;
            d2[i]=-1;
        }else{
          d1[i]=pp;
          d2[i]=a[i];
        }
    }

    for (int i=0; i<n; ++i) cout<<d1[i]<<" ";
    cout<<"\n";
    for (int i=0; i<n; ++i) cout<<d2[i]<<" ";


}
