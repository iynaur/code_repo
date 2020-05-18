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

using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef pair<int,int> pii;

typedef vector<lint> vl;
typedef pair<lint,lint> pll;

#define mpr make_pair






class BITree{
  vi rbtree;
public:
  BITree(const vi &arr){

    int n = arr.size();
    rbtree.assign(n+1, 0);

    // Store the actual values in BITree[] using update()
    for (int i=0; i<n; i++)
        updateBIT(i, arr[i]);

  }

  // Updates a node in Binary Index Tree (BITree) at given index
  // in BITree. The given value 'val' is added to BITree[i] and
  // all of its ancestors in tree.
  void updateBIT(int index, int val)// 0 - index
  {
    // index in BITree[] is 1 more than the index in arr[]
    index = index + 1;

    // Traverse all ancestors and add 'val'
    while (index < rbtree.size())
    {
      // Add 'val' to current node of BI Tree
      rbtree[index] += val;

      // Update index to that of parent in update View
      index += index & (-index);
    }
  }

  // Returns sum of arr[0..index]. This function assumes
  // that the array is preprocessed and partial sums of
  // array elements are stored in BITree[].
  int getSum(int index)  //[0, index]
  {
      int sum = 0; // Iniialize result

      // index in BITree[] is 1 more than the index in arr[]
      index = index + 1;

      // Traverse ancestors of BITree[index]
      while (index>0)
      {
          // Add current element of BITree to sum
          sum += rbtree[index];

          // Move index to parent node in getSum View
          index -= index & (-index);
      }
      return sum;
  }

  int upperBound(int x) {//largest prefix with sum not exceeding x
      int res = 0;
      int max = 0;
      while(1<<max <= rbtree.size()) max++;
      max--;
      for (int k = max; k >= 0; --k) {
          int p = res + (1 << k);
          if (p < rbtree.size() && rbtree[p] <= x) {
              x -= rbtree[p];
              res += 1 << k;
          }
      }
      return res-1;
  }
};

int main()
{
    ios_base::sync_with_stdio(0);    cin.tie(NULL);    cout.tie(NULL);

    int n ,q; cin>>n>>q;
    //vi a(n);

    vi cnt(n+1, 0);
    //SegmentTree<int> seg(n+1);
    for (int o = 0; o<n; ++o) {
        int i;
        cin>>i;
        //seg.set(i, seg.get(i) + 1);
        cnt[i] ++;
    }

    BITree bit(cnt);


    auto findk = [&](int k){

        return bit.upperBound(k-1)+1;
    };

    for (int _ = 0; _<q; ++_){
        int k; cin>>k;
        if (k > 0){
            cnt[k]++;
            bit.updateBIT(k, 1);
        } else {
            int id = findk(-k);
//            id--;
            cnt[id]--;
            bit.updateBIT(id, -1);
        }
    }

    if (bit.getSum(n) ==0) cout<<0;
    else {
        bool ok = false;
        for (int i=1; i<=n; ++i){
            for (int t=0; t<cnt[i]; ++t) {
                cout<<i<<" ";
                ok = true;
                break;
            }
            if (ok) break;
        }
    }

}
