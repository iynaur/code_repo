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

#include "segtree.h"
#include "pairhash.h"
#include "kmp.h"
//#include "leetcode_bintree.h"
#include "leetcode_list.h"
using namespace std;

struct ScopedNanoTimer
{
    chrono::high_resolution_clock::time_point t0;
    string title;

    ScopedNanoTimer(string title_)
        : t0(chrono::high_resolution_clock::now())
    {
        title=title_;
    }
    ~ScopedNanoTimer(void)
    {
        auto  t1 = chrono::high_resolution_clock::now();
        auto nanos = chrono::duration_cast<chrono::milliseconds>(t1-t0).count();

        cout<<title<<" cost "<<nanos<<" ms\n";
    }
};

using namespace std;

typedef long long lint;
typedef unsigned long long ulint;

template<int alphasize, char base>
class Trie {
    struct Node{
        int index;
        int cnt=0;
        Node* sons[alphasize];

        Node(int id){
            index = id;
            for (auto &son : sons)son=nullptr;
        }

        void insert(const string &s)
        {
            if (s.empty()){
                cnt++;
                return;
            }
            int id = s[0]-base;
            if (!sons[id]) sons[id] = new Node(id);
            sons[id]->insert(s.substr(1));
        }

        void iter_right(string &path, string &res, int piv)
        {
            for (int i = alphasize-1; i>piv && i>=0; i--)
            {
                Node* son = sons[i];
                if (son){
                    path.push_back(base + i);
                    int npiv = piv;
                    if (piv == -1) npiv = i;
                    son->reverse_iterator(path, res, npiv);
                    path.pop_back();
                }
            }
            if (piv>=0 && sons[piv])  {
                path.push_back(base + piv);
                sons[piv]->iter_right(path, res, piv);
                path.pop_back();
            }
        }

        void iter_left(string &path, string &res, int piv)
        {
            if (piv>=0 && sons[piv])  {
                path.push_back(base + piv);
                sons[piv]->iter_left(path, res, piv);
                path.pop_back();
            }
            for (int i = piv-1; i>=0; i--)
            {
                Node* son = sons[i];
                path.push_back(base + i);
                if (son)son->reverse_iterator(path, res, piv);
                path.pop_back();
            }
        }

        void reverse_iterator(string &path, string &res, int piv)
        {
            iter_right(path, res, piv);
            //for (int i=0; i<cnt; ++i) {cout<<path;}
            Node* cur = this;
            string npath = path;
            if (piv!= -1) while(cur)
            {
                for (int i=0; i<cur->cnt; ++i) {res += npath;}
                cur = cur->sons[piv];
                npath.push_back(base + piv);
            }
            iter_left(path, res, piv);
        }
    };

    int n;
public:
    Node* rt;

    Trie(){
        n = alphasize;
        rt = new Node(-1);
    }

    void insert(const string &s)
    {
        rt->insert(s);
    }


};

string largestConcat(const vector<string>& v) {
    Trie<10, '0'> trie;

    for (auto &s : v)
    {
        trie.insert(s);
    }
    string path;
    string res;
    trie.rt->reverse_iterator(path, res, -1);
    if (res == string(res.size(), '0')) return "0";
    return res;
}

int maint()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<string> v;
    for (int i=0; i<=1000; ++i) v.push_back(std::to_string(i));
    //cout<<largestConcat(v);
    cout<<largestConcat({"98", "989"});

}
