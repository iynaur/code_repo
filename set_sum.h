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


set<lint> tp0, tp1;
SetSum<lint> sdb, ssin;


lint getdb(){
  assert(sdb.size() == tp1.size());
  if (sdb.empty()) return 0;
  if (tp0.size()){
    if ( *tp0.rbegin() >= *sdb.begin())
      return sdb.sum;
   else
    return sdb.sum - *sdb.begin() + *tp0.rbegin();
  } else {
    return sdb.sum - *sdb.begin();
  }
}

void add(lint d, lint tp){
  if (tp == 0) tp0.insert(d);
  else tp1.insert(d);

  if (sdb.empty() || d < *sdb.begin())
    ssin.insert(d);
  else {
    sdb.insert(d);
    ssin.insert(*sdb.begin());
    sdb.erase(sdb.begin());
  }

  if (tp == 1){
    //sdb++
    sdb.insert(*ssin.rbegin());
    ssin.erase(*ssin.rbegin());
  }
}

void rm(lint d, lint tp){
  if (tp == 0) tp0.erase(d);
  else tp1.erase(d);

  if (ssin.count(d)) ssin.erase(d);
  else {
    sdb.erase(d);
    if (ssin.empty())
    {
      assert(tp == 1);
      return;
    }
    sdb.insert(*ssin.rbegin());
    ssin.erase(*ssin.rbegin());
  }

  if (tp == 1){
    //sdb--
    ssin.insert(*sdb.begin());
    sdb.erase(sdb.begin());
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

      cout<<sdb.sum + ssin.sum + getdb()<<'\n';
    }
}
