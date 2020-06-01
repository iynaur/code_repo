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

vi primesUntil(int n){
    vi p;
    p.push_back(2);
    for (int i =3; i<=n; ++i){
        for (int j=0; j<p.size(); ++j){
            if (i%p[j] == 0) break;
            if (p[j]* p[j]> i)
            {
                p.push_back(i);
                break;
            }
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

void main_test()
{
    ios_base::sync_with_stdio(0);    cin.tie(NULL);    cout.tie(NULL);

    int n; cin>>n;
    vi a(n); for (int &v:a) cin>>v;

    vi p = primesUntil(2e5);

    map<int, int> revp;
    for (int i=0; i<p.size(); ++i){
        revp[p[i]] = i;
    }

    vector<multiset<int>> scnt(p.size());
    vi tcnt(p.size(), 0);

    auto add = [&](int pid, int cnt){
        tcnt[pid]++;
        scnt[pid].insert(cnt);
        if (scnt[pid].size()>2){
            scnt[pid].erase(prev(scnt[pid].end()));
        }
    };


    for (int i = 0; i<a.size(); ++i){
        int v = a[i];
        vector<pii> fact = defactor(v, p);
        for (pii pp : fact){
          add(revp[pp.first], pp.second);
        }
    }

    lint res = 1;
    for (int pid=0; pid<p.size(); ++pid){
        if (tcnt[pid]<= n-2) continue;
        if (tcnt[pid] == n-1) for (int i=0; i< *scnt[pid].begin(); ++i){
                res *= p[pid];
            }
        else for (int i=0; i< *next(scnt[pid].begin()); ++i){
            res *= p[pid];
        }
    }
    cout<<res;


}
