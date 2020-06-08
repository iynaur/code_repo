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
#include <list>

using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef pair<int,int> pii;

typedef vector<lint> vl;
typedef pair<lint,lint> pll;

int baseres(const vi &base, int v){
  for (auto x : base) v = min(v, v^x);
  return v;
}

vi baseof(const vi &sum){
  vi b;
  int n = sum.size();
  for (int i=0; i<n; ++i){
    int v = baseres(b, sum[i]);
    if (sum[i] && v){
      b.push_back(v);
    }
  }
  return b;
}

const int  INT_BITS = 32;

int maxSubarrayXORMy(vi set){
  int n = set.size();
  int cur = 0;
  vi b = baseof(set);
  for (int i = INT_BITS-1; i>=0; --i){
    int ncur = cur + (1<<i);
    if (baseres(b, ncur) < (1<<i)){
      cur = ncur;
    }
  }
  return cur;
}


int maxSubarrayXOR(vi set)
{
  int n = set.size();
    // Initialize index of
    // chosen elements
    int index = 0;

    // Traverse through all
    // bits of integer
    // starting from the most
    // significant bit (MSB)
    for (int i = INT_BITS-1; i >= 0; i--)
    {
        // Initialize index of
        // maximum element and
        // the maximum element
        int maxInd = index;
        int maxEle = INT_MIN;
        for (int j = index; j < n; j++)
        {
            // If i'th bit of set[j]
            // is set and set[j] is
            // greater than max so far.
            if ( (set[j] & (1 << i)) != 0
                     && set[j] > maxEle )
                maxEle = set[j], maxInd = j;
        }

        // If there was no
        // element with i'th
        // bit set, move to
        // smaller i
        if (maxEle == INT_MIN)
        continue;

        // Put maximum element
        // with i'th bit set
        // at index 'index'
        swap(set[index], set[maxInd]);

        // Update maxInd and
        // increment index
        maxInd = index;

        // Do XOR of set[maxIndex]
        // with all numbers having
        // i'th bit as set.
        for (int j=0; j<n; j++)
        {
            // XOR set[maxInd] those
            // numbers which have the
            // i'th bit set
            if (j != maxInd &&
               (set[j] & (1 << i)) != 0)
                set[j] = set[j] ^ set[maxInd];
        }

        // Increment index of
        // chosen elements
        index++;
    }

    // Final result is
    // XOR of all elements
    int res = 0;
    for (int i = 0; i < n; i++)
        res ^= set[i];
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);    cin.tie(NULL);    cout.tie(NULL);

    while(1){
      int n = 20;
      vi a(n);
      for (int &i : a) i = rand()%int(1e9 + 7);
      for (int i : a) cout<<i<<" ";
      cout<<endl<<maxSubarrayXOR(a)<<endl;
      if (maxSubarrayXOR(a) != maxSubarrayXORMy(a)){
        cout<<"=====================\n";
        return 0;
      }
    }

}
