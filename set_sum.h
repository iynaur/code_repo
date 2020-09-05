#include <bits/stdc++.h>

using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<lint> vl;
typedef pair<lint,lint> pll;
#define mpr make_pair

template <typename T>
struct SetSum {
  std::set<T> st;
  T sum;

  void insert(T t){
    st.insert(t);
    sum += t;
  }

  void erase(T t){
    st.erase(st.find(t));
    sum -= t;
  }

  void erase(typename set<T>::iterator it){
    sum -= *it;
    st.erase(it);
  }

  typename set<T>::iterator begin(){
    return st.begin();
  }

  typename set<T>::reverse_iterator rbegin(){
    return st.rbegin();
  }

  lint size(){
    return st.size();
  }

  bool empty(){
    return st.empty();
  }

  lint count(T t){
    return st.count(t);
  }

};

template <typename T>
struct SetPartSum {
  SetSum<T> low, high;
  function<bool(T, T)> less = [](T t1, T t2){
    return t1 < t2;
  };

  void add(T t){
    if (less(t, *high.begin())){
      low.insert(t);
    } else {
      high.insert(t);
      low.insert(*high.begin());
      high.erase(high.begin());
    }
  }

  bool needShink = false;
  void remove(T t){
    if (low.count(t)){
      low.erase(t);
    } else {
      high.erase(t);
      if (low.empty()){
        needShink = true;
      } else {
        high.insert(*low.rbegin());
        low.erase(*low.rbegin());
      }
    }
  }

  void expand(){
    assert(low.size());
    high.insert(*low.rbegin());
    low.erase(*low.rbegin());
  }

  void shink(){
    if (needShink){
      needShink = false;
      return;
    }
    assert(high.size());
    low.insert(*high.begin());
    high.erase(high.begin());
  }
};



set<lint> tp0, tp1;
//SetSum<lint> sdb, ssin;
SetPartSum<lint> sp;

lint getdb(){
  if (sp.high.empty()) return 0;
  if (tp0.size()){
    if ( *tp0.rbegin() >= *sp.high.begin())
      return sp.high.sum;
   else
    return sp.high.sum - *sp.high.begin() + *tp0.rbegin();
  } else {
    return sp.high.sum - *sp.high.begin();
  }
}

void add(lint d, lint tp){
  if (tp == 0) tp0.insert(d);
  else tp1.insert(d);

  sp.add(d);

  if (tp == 1){
    sp.expand();
  }
}

void rm(lint d, lint tp){
  if (tp == 0) tp0.erase(d);
  else tp1.erase(d);

  sp.remove(d);

  if (tp == 1){
    sp.shink();
  }
}

int main()
{
    ios_base::sync_with_stdio(0);    cin.tie(NULL);    cout.tie(NULL);

    int n; cin>>n;


    while(n--){
      lint tp, d; cin>>tp>>d;

      if (d > 0){
        add(d, tp);
      } else {
        rm(-d, tp);
      }

      cout<<sp.high.sum + sp.low.sum + getdb()<<'\n';
    }
}
