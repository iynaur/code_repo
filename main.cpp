#include <iostream>
#include <string>
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

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};



struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isSubPath(ListNode* head, TreeNode* root, bool tight = false) {
        vector<int> pat;
        while(head){
            pat.push_back(head->val);
            head = head->next;
        }

        vector<int> kmp = kmpFunc(pat);

        int n = pat.size();
        bool ok = 0;
        function<void(TreeNode* r, int)> dfs = [&](TreeNode* r, int len)
        {
            if (len == n) {ok =1; return;}
            if (!r) return;

            int cur = r->val;

            while(len>0 && cur != pat[len]) len = kmp[len-1];
            if (cur == pat[len]) len++;
            dfs(r->left, len);
            dfs(r->right, len);
        };
        dfs(root, 0);
        return ok;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    Solution s;
    kmpFunc(string("asddf"));

}
