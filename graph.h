#include <bits/stdc++.h>

using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<lint> vl;
typedef pair<lint,lint> pll;

lint MST_prim(const vector<vi> &m, int start, int end){// 0, n if 0-indexed or 1, n+1 if 1-indexed
  assert(m.size() >= end);
  assert(m[0].size() >= end);
  vector<int>lowest(end),vertex(end,0);

  for(int j=start;j<end;j++){

    lowest[j]=m[start][j];//将start号节点插入最小构造树中
  }
  vertex[start]=1;//标记start号节点
  int totalcost=0;
  for(int i=0;i<end-start-1;i++){
    int mincost=INT_MAX, index=-1;
    for(int j=start;j<end;j++){//寻找与树中已有点相连的最短边
      if(!vertex[j] && lowest[j]<mincost){
        mincost=lowest[j];
        index=j;
      }
    }
    assert(index != -1);
    vertex[index]=1;//标记新加入树的点
    totalcost+=lowest[index];
    for(int j=start;j<end;j++){
      if(m[index][j]<lowest[j]){//利用新加入树的点刷新最短边
        lowest[j]=m[index][j];
      }
    }
  }
  return totalcost;
}

int main_graph(){
  vector<vi> mp;
  mp.push_back(vi({0,1,2,3}));
  mp.push_back(vi({1,0,2,3}));
  mp.push_back(vi({2,2,0,3}));
  mp.push_back(vi({3,3,3,0}));

  MST_prim(mp, 0, 4);
}
