#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef pair<int,int> pii;

typedef vector<lint> vl;
typedef pair<lint,lint> pll;
typedef unsigned long long ul;
typedef vector<ul> vu;
#define  xx first
#define  yy second
#endif
#include<bits/stdc++.h>
using namespace std;

//BEGIN CUT HERE
template <typename T,typename E>
struct SegmentTree{
  using F = function<T(T,T)>;
  using G = function<T(T,E)>;
  using H = function<E(E,E)>;
  int n,height;
  int rn;
  F f;  // for query range value, example, sum   max
  G g;
  H h;  // for range update, example, add
  T ti; // zero value for query range value, 0 for sum,   min for max
        // formally,  h(*, ti) == *
  E ei; // zero value for range update,
  vector<T> dat;
  vector<E> laz;
  SegmentTree(F f,G g,H h,T ti,E ei):
    f(f),g(g),h(h),ti(ti),ei(ei){}

  void init(int n_){
    rn = n_;
    n=1;height=0;
    while(n<n_) n<<=1,height++;
    dat.assign(2*n,ti);
    laz.assign(2*n,ei);
  }

  void build(const vector<T> &v){
    int n_=v.size();
    init(n_);
    for(int i=0;i<n_;i++) dat[n+i]=v[i];
    for(int i=n-1;i;i--)
      dat[i]=f(dat[(i<<1)|0],dat[(i<<1)|1]);
  }

  inline T reflect(int k){
    return laz[k]==ei?dat[k]:g(dat[k],laz[k]);
  }

  inline void propagate(int k){
    if(laz[k]==ei) return;
    laz[(k<<1)|0]=h(laz[(k<<1)|0],laz[k]);
    laz[(k<<1)|1]=h(laz[(k<<1)|1],laz[k]);
    dat[k]=reflect(k);
    laz[k]=ei;
  }

  inline void thrust(int k){
    for(int i=height;i;i--) propagate(k>>i);
  }

  inline void recalc(int k){
    while(k>>=1)
      dat[k]=f(reflect((k<<1)|0),reflect((k<<1)|1));
  }

  void update(int a,int b,E x){ // [a, b)
    if(a>=b) return;
    thrust(a+=n);
    thrust(b+=n-1);
    for(int l=a,r=b+1;l<r;l>>=1,r>>=1){
      if(l&1) laz[l]=h(laz[l],x),l++;
      if(r&1) --r,laz[r]=h(laz[r],x);
    }
    recalc(a);
    recalc(b);
  }

  void set_val(int a,T x){
    thrust(a+=n);
    dat[a]=x;laz[a]=ei;
    recalc(a);
  }

  T query(int a,int b){ //[a, b)
    if(a>=b) return ti;
    thrust(a+=n);
    thrust(b+=n-1);
    T vl=ti,vr=ti;
    for(int l=a,r=b+1;l<r;l>>=1,r>>=1) {
      if(l&1) vl=f(vl,reflect(l++));
      if(r&1) vr=f(reflect(--r),vr);
    }
    return f(vl,vr);
  }

  using C = function<bool(T)>;

  int find(int st,C &check,T &acc,int k,int l,int r){
    if(l+1==r){
      acc=f(acc,reflect(k));
      return check(acc)?k-n:-1;
    }
    propagate(k);
    int m=(l+r)>>1;
    if(m<=st) return find(st,check,acc,(k<<1)|1,m,r);
    if(st<=l&&!check(f(acc,dat[k]))){
      acc=f(acc,dat[k]);
      return -1;
    }
    int vl=find(st,check,acc,(k<<1)|0,l,m);
    if(~vl) return vl;
    return find(st,check,acc,(k<<1)|1,m,r);
  }

  int find(int st,C &check){
    T acc=ti;
    return find(st,check,acc,1,0,n);
  }

  void print(){
    cerr<<"============\n";
    for (int i=1; i<rn; ++i){
      cerr<<query(i, i+1)<<" ";
    }
    cerr<<endl;
    cerr<<"============\n";
  }
};
//END CUT HERE

#ifndef call_from_test

void CFR1326_E(){
  cin.tie(0);
  ios::sync_with_stdio(0);

  int n;
  cin>>n;

  vi p(n);
  vi vp(n+1);
  for (int i=0; i<n; ++i) {
    cin>>p[i];
    vp[p[i]] = i+1;
  }
  vi q(n);
  for (int &i :q) cin>>i;


  auto f=[](lint a,lint b){return max(a,b);};
  auto g=[](lint a,lint b){return a+b;};
  lint ti=LONG_LONG_MIN,ei=0;
  SegmentTree<lint, lint> seg(f,g,g,ti,ei);

  const int sz = n + 3;
  vl init(sz, 0);
//  for (int i=0; i<sz; ++i) init[i] = -k*i;
  seg.build(init);

  int cur = n;
  cout<<cur<<" ";
  for (int i=0; i<n-1; ++i){
    //add bomb qi;
    seg.update(1, q[i]+1, -1);

    while(seg.query(1, n+1) <= 0){
      //cur--;

      seg.update(1, vp[cur]+1, 1);
      cur--;
    }
    cout<<cur+1<<" ";
  }


}
/*
  verified on 2019/10/28
  https://codeforces.com/contest/1179/problem/C
*/

signed main(){
  CFR1326_E();
  return 0;
}
#endif
