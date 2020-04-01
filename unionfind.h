#include <bits/stdc++.h>
using namespace std;

struct UnionFind {//index [0, n)
    vector<int> fa;
    explicit UnionFind(int n){
        fa.resize(n);
        for (int i=0; i<n; ++i)fa[i]=i;
    }

    int findP(int i) {
        while(i != fa[i]) {
            fa[i] = fa[fa[i]];
            i = fa[i];
        }
        return i;
    }

    int find(int n) {
        int m = n;
        while (fa[m]!=m)
            m = fa[m];
        fa[n] = m;
        return m;
    }
    void unite(int m, int n) {
        int p1 = find(m);
        int p2 = find(n);
        if (p1!=p2)
            fa[p1] = p2;
        return;
    }

    int g(int son)
    {
        while (fa[fa[son]] != fa[son]) fa[son] = fa[fa[son]];
        return fa[son];
    }

    void connectAtoB(int a, int b)
    {
        //if (a>b) swap(a, b);
        fa[g(a)]= g(b);
    }

};
