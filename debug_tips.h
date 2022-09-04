#ifndef DEBUG_TIPS_H
#define DEBUG_TIPS_H

//  TLE  check time complexity
//  WA    check logic
//        try brute search
//        try prove logic
//        output format

//  operators   always use () to explicitly set order.
//  check boundray conditions
//  careful  RE, vector index range, map iterator end.

// leetcode   int overflow

// it0, it1, it2...  do not copy past without check!!

// hard but maybe easy problem:   think bfs not dfs
// check examples before code, make sure code the right process
// check time & space complexity before code, make sure code the right process

#endif // DEBUG_TIPS_H

#include <bits/stdc++.h>

using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<lint> vl;
typedef pair<lint,lint> pll;
#define mpr make_pair

void bugfunction() {
    vi a;
    // init a
    for (int i = 0; i < a.size() - 1; i++){
        if (a[i]!=a[i+1]) {
            return;
        }
    }

    //======
    auto func_na = [](){
        return int();
    };
    int ia = func_na();
    // past from some where
    int b = ia; // not get old ia;

    {
        //=======
        lint res;
        int ia, ib;
        res += ia*ib; // overflow!!!
    }

    {
        lint a = 1<<35; // wrong
        a = 1LL << 35;
    }

    {
        int a = 0;
        int b = rand();
        //...
        swap(a, b); // swap is evil, change a without a =
        //...
        assert(a == 0); // boom
    }

    {
        vl s(2);
        assert(s[1] * s[0] > 0); // to see if they are both negative or positive, but lint overflow
    }

    {
        pll c;
        lint a, b;
        c = pii(a, b); // pii to pll, a, b changed
    }
}


//#define stress  // switch
// stress variable
int n = 6;
vi a(n + 1);

#ifdef stress
#define get(x, v) x = (v);
#define stress_assert(x) assert(x)
auto initres = []() {
    for (int& v : a){
        get(v, (rand()%9) + 1);
    }
    a[rand()%n +1] = 0;
    return 0;
};
#define init_interact() initres()
#else
#define get(x, v) cin>>x;
#define init_interact()
#define stress_assert(x)
#endif

void solve(){
    init_interact();
    get(n, 6);
    set<pii> candi;


    auto ans = [&](int i, int j, int k) {
        int ma = max(a[i], a[j]);
        ma = max(ma, a[k]);
        int mi = min(a[i], a[j]);
        mi = min(mi, a[k]);
        return ma - mi;
    };

    auto gres = [&](int i, int j, int k) {
        cout<<"? "<<i<<" "<<j<<" "<<k<<"\n";
        cout.flush();
        int res;
        get(res, ans(i,j,k));
        return res;
    };
    for (int i = 2; i<=n-1; ++i) {
//        cout<<"? 1 "<<i<<" "<<n<<"\n";
//        cout.flush();
        int res;
//        cin>>res;
        res = gres(1, i, n);
        candi.insert(pii(res, i));
    }
    pii rb = *(candi.rbegin());

    int range = rb.first;
    if (range == candi.begin()->first) {
        for (int i = 3; i<=n-1; ++i) {
            int res=gres(1,2,i);
            if ( res> range) {
//                assert(res == 2*range);
                cout<<"! "<<2<<" "<<i<<"\n";
                cout.flush();
                stress_assert(a[2] * a[i] == 0);
                return;
            }
        }
        cout<<"! "<<1<<" "<<n<<"\n";
        cout.flush();
        stress_assert(a[1] * a[n] == 0);
        return;
    }
    int id = rb.second;

    set<pii> c2;
    for (int i = 2; i<=n; ++i) if (i != id) {
//        cout<<"? 1 "<<i<<" "<<id<<"\n";
//        cout.flush();
        int res;
//        cin>>res;
        res = gres(1, i, id);

        c2.insert(pii(res, i));
    }
    int id2 = (c2.rbegin())->second;
    int rg2 = (c2.rbegin())->first;
    assert(rg2 >= range);
    if (rg2 == range) {
        if (c2.begin()->first == rg2) {
            cout<<"! "<<1<<" "<<id<<"\n";
            cout.flush();
            stress_assert(a[1] * a[id] == 0);
            return;
        }
//        cout<<"! "<<1<<" "<<id2<<"\n";
//        cout.flush();
//        return;
    }
    cout<<"! "<<id<<" "<<id2<<"\n";
    stress_assert(a[id2] * a[id] == 0);
    cout.flush();

}

int main()
{
    ios_base::sync_with_stdio(0);    cin.tie(NULL);    cout.tie(NULL);

    int t;
    get(t, 1000000);
    while(t--){
        solve();
    }

}

