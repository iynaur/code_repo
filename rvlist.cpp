#include <bits/stdc++.h>

using namespace std;
typedef long long lint;
typedef vector<int> vi;
typedef pair<int,int> pii;

typedef vector<lint> vl;
typedef pair<lint,lint> pll;

struct node {
    int a;

    pair<node*, bool> next;
    pair<node*, bool> prev;

    node(int v)
    {
        a=v;
        next = prev = {nullptr, 0};
    }


};



struct rvlist {
    pair<node*, bool> start;
    pair<node*, bool> end;
    int len;

    rvlist(){

    }

    rvlist(int v)
    {
        node* cur = new node(v);
        start = {cur, true};
        end = {cur, false};
        len = 1;
    }

    void append(rvlist & li)
    {
        if (!end.second)
            end.first->next = li.start;
        else
            end.first->prev = li.start;
        if (!li.start.second)
            li.start.first->next = end;
        else
            li.start.first->prev = end;

        end = li.end;
        len = len + li.len;
    }

    void reverseAppend(rvlist & li)
    {
        li.reverse();
        append(li);
    }

    void reverse()
    {
        swap(start, end);
    }

    rvlist reversed()
    {
        rvlist l = *this;
        l.reverse();
        return l;
    }

    void print()
    {
        pair<node*, bool> cur = start;
        while(cur.first)
        {
            cout<<cur.first->a<<" ";
            cur = cur.second?cur.first->next:cur.first->prev;
        }
        cout<<endl;
    }
};

class rvdeque {
    deque<rvlist> fo;
    bool lr_rev;
    bool ud_rev;
public:
    rvdeque(int n)
    {
        fo.resize(n);
        lr_rev = false;
        ud_rev = false;
    }

    rvlist at(int id)
    {
        rvlist l;
        if (!lr_rev) l = fo[id];
        else l = fo[fo.size()-1-id];
        if (ud_rev) l.reverse();
        return l;

    }

    void set(int id, rvlist l)
    {
        if (ud_rev) l.reverse();
        if (!lr_rev) fo[id]=l;
        else fo[fo.size()-1-id] = l;
    }

    int size(){
        return fo.size();
    }

    void push_front(const rvlist &val)
    {
        rvlist l = val;
        if (ud_rev) l.reverse();
        if (!lr_rev) fo.push_front(l);
        else fo.push_back(l);
    }

    void push_back(const rvlist &val)
    {
        rvlist l = val;
        if (ud_rev) l.reverse();
        if (lr_rev) fo.push_front(l);
        else fo.push_back(l);
    }

    void pop_back()
    {
        if (!lr_rev) fo.pop_back();
        else fo.pop_front();
    }

    void reverse()
    {
        //rev = !rev;
    }

    void foldAt(int piv)
    {
        auto &fo = *this;
        int l = fo.size();

        bool rev= false;
        if (2* piv < l)
        {
            rev = true;
            piv = l-piv;
            //if (piv==l) continue;
            lr_rev = !lr_rev;
            //cout<<"after lr_rev\n";
            //prt();
        }


        int tot = 2*piv-1;

        for (int op = piv; op<l; ++op)
        {

            auto l = fo.at(tot - op);
            auto m = fo.at(op);
            l.reverseAppend(m);
            fo.set(tot - op, l);
            //fo[tot - op].reverseAppend(fo[op]);

        }
        int n = fo.size();
        for (int i = piv; i<n; ++i) fo.pop_back();

        //restore
        //cout<<"after op\n";
        //prt();
        if (rev) ud_rev = !ud_rev;
        //cout<<"after ud_rev\n";
        //prt();
    }

    void prt()
    {
        return;
        cout<<"=====\n";
        for (int i=0; i<size(); ++i)
        {
            auto l = at(i);
            l.print();
        }
        cout<<"=====\n";
    }
};


int maint()
{
    ios_base::sync_with_stdio(0);    cin.tie(NULL);    cout.tie(NULL);

    rvlist l(1);

    for (int i = 2; i<5; ++i)
    {
        rvlist m(i);
        l.append(m);
    }

    l.print();
    l.reverse();
    l.print();

    rvlist m(1);

    for (int i = 2; i<5; ++i)
    {
        rvlist n(i);
        m.append(n);
    }
    m.print();

    l.reverseAppend(m);
    l.print();
    l.reverse();
    l.print();


}
