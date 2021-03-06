/**
* Number:p3369
* Title:【模板】普通平衡树
* Status:AC
* Tag:[scapegoat tree, 替罪羊树]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int &i1) { return scanf("%d", &i1); }
inline int readi(int &i1, int &i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int &i1, int &i2, int &i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int &i1, int &i2, int &i3, int &i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char *s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

template <typename T, int MAXN>
struct Scapegoat_Tree
{
#define APLHA 0.75 // 平衡因子
    struct Node
    {
        T val;         // 值
        int cnt, sz;   // cnt-节点权值 sz-子树权值
        int rk, rkall; // rk-子树有效节点个数 rkall-子树节点总数
        Node *son[2];  // 左右儿子
        void pushup()
        {
            sz = son[0]->sz + son[1]->sz + cnt;
            rk = son[0]->rk + son[1]->rk + (cnt > 0);
            rkall = son[0]->rkall + son[1]->rkall + 1;
        }
        bool unbalance()
        {
            return ((son[0]->rkall > rkall * APLHA + 5) ||
                    (son[1]->rkall > rkall * APLHA + 5));
        }
    };
    Node tree[MAXN], *root, *tail, *null;
    vector<Node *> trace;
    void init()
    {
        root = tail = null = tree;
        *null = (Node){0, 0, 0, 0, 0, null, null};
    }
    Node *makenode(T val)
    {
        Node *p = ++tail;
        *p = (Node){val, 1, 1, 1, 1, null, null};
        return p;
    }
    void inorder(Node *p)
    {
        if (p == null)
            return;
        inorder(p->son[0]);
        if (p->cnt > 0)
            trace.push_back(p);
        inorder(p->son[1]);
    }
    Node *rebuild_help(int beg, int end)
    {
        if (beg >= end)
            return null;
        int mid = (beg + end) >> 1;
        Node *p = trace[mid];
        p->son[0] = rebuild_help(beg, mid);
        p->son[1] = rebuild_help(mid + 1, end);
        p->pushup();
        return p;
    }
    void rebuild(Node *&nod)
    {
        trace.clear();
        inorder(nod);
        nod = rebuild_help(0, trace.size());
    }
    Node **findnode(T val)
    {
        trace.clear();
        Node **cur = &root;
        while (true)
        {
            trace.push_back((Node *)cur);
            if ((*cur)->val == val || *cur == null)
                break;
            cur = &((*cur)->son[val > (*cur)->val]);
        }
        return cur;
    }
    int rank(T val)
    {
        findnode(val);
        int ans = 1;
        for (int i = 0; i < trace.size(); i++)
        {
            Node *nod = *(Node **)trace[i];
            if (nod->val < val)
                ans += nod->son[0]->sz + nod->cnt;
            else if (nod->val == val)
                ans += nod->son[0]->sz;
        }
        return ans;
    }
    T kth(int k)
    {
        for (Node *cur = root; cur != null;)
        {
            if (cur->son[0]->sz >= k)
                cur = cur->son[0];
            else if (cur->son[0]->sz + cur->cnt >= k)
                return cur->val;
            else
                k -= cur->son[0]->sz + cur->cnt, cur = cur->son[1];
        }
    }
    void insert(T val)
    {
        Node **cur = findnode(val);
        if (*cur == null)
            *cur = makenode(val);
        else
            (*cur)->cnt++;
        for (int i = trace.size() - 1; i >= 0; i--)
            (*(Node **)trace[i])->pushup();
        for (int i = 0; i < trace.size(); i++)
        {
            if ((*(Node **)trace[i])->unbalance())
            {
                rebuild(*(Node **)trace[i]);
                break;
            }
        }
    }
    void remove(T val)
    {
        Node **cur = findnode(val);
        (*cur)->cnt--;
        for (int i = trace.size() - 1; i >= 0; i--)
            (*(Node **)trace[i])->pushup();
        if (root->rk < APLHA * root->rkall)
            rebuild(root);
    }
    T prev(T val)
    {
        return kth(rank(val) - 1);
    }
    T next(T val)
    {
        return kth(rank(val + 1));
    }
#undef APLHA
};

Scapegoat_Tree<int, 100010> tree;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n);
    tree.init();
    while (n--)
    {
        int op, x;
        readi(op, x);
        switch (op)
        {
        case 1:
            tree.insert(x);
            break;
        case 2:
            tree.remove(x);
            break;
        case 3:
            printf("%d\n", tree.rank(x));
            break;
        case 4:
            printf("%d\n", tree.kth(x));
            break;
        case 5:
            printf("%d\n", tree.prev(x));
            break;
        case 6:
            printf("%d\n", tree.next(x));
            break;
        }
    }
    return 0;
}

/**
* Number:p3369
* Title:【模板】普通平衡树
* Status:AC
* Tag:[splay tree, 伸展树]
**/

/*
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int &i1) { return scanf("%d", &i1); }
inline int readi(int &i1, int &i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int &i1, int &i2, int &i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int &i1, int &i2, int &i3, int &i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char *s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

template <typename T, int MAXN>
struct SplayTree
{
    struct Node
    {
        T val;
        int sz, cnt;
        Node *fa, *son[2];
    } tree[MAXN];
#define null ((Node *)&tree[0])
#define root tree[0].son[0]
    int nodeid;
    inline Node *makenode(T val)
    {
        tree[++nodeid] = (Node){val, 1, 1, null, null, null};
        return tree + nodeid;
    }
    inline void link(Node *u, Node *fa, int d)
    {
        if (u != null)
            u->fa = fa;
        fa->son[d] = u;
    }
    void init()
    {
        tree[nodeid = 0] = (Node){0, 0, 0, null, null, null};
        root = makenode(INF);
        link(makenode(-INF), root, 0);
    }
    inline void pushup(Node *u)
    {
        u->sz = u->cnt + u->son[0]->sz + u->son[1]->sz;
    }
    inline int dir(Node *u)
    {
        return u->fa->son[1] == u;
    }
    void rotate(Node *u)
    {
        Node *fa = u->fa, *ffa = fa->fa;
        int dfa = dir(u), dffa = dir(fa);
        link(u, ffa, dffa);
        link(u->son[dfa ^ 1], fa, dfa);
        link(fa, u, dfa ^ 1);
        pushup(fa);
        pushup(u);
    }
    void splay(Node *u, Node *top)
    {
        while (u->fa != top)
        {
            if (u->fa->fa != top)
                rotate(dir(u) == dir(u->fa) ? u->fa : u);
            rotate(u);
        }
    }
    Node *findpos(Node *u, T val)
    {
        while (true)
        {
            if (val < u->val && u->son[0] != null)
                u = u->son[0];
            else if (val > u->val && u->son[1] != null)
                u = u->son[1];
            else
                return u;
        }
    }
    bool find(T val)
    {
        splay(findpos(root, val), null);
        return root->val == val;
    }
    Node *prev(T val)
    {
        find(val);
        if (root->val < val)
            return root;
        return findpos(root->son[0], val);
    }
    Node *next(T val)
    {
        find(val);
        if (root->val > val)
            return root;
        return findpos(root->son[1], val);
    }
    void insert(T val)
    {
        Node *u = findpos(root, val), *v;
        if (u->val == val)
            u->cnt++, v = u;
        else
            link(v = makenode(val), u, val > u->val);
        splay(v, null);
    }
    void remove(T val)
    {
        Node *l = prev(val), *r = next(val);
        splay(l, null);
        splay(r, l);
        if (r->son[0]->cnt > 1)
            r->son[0]->cnt--;
        else
            r->son[0] = null;
        splay(r->son[0], null);
    }
    int rank(T val)
    {
        find(val);
        if (root->val >= val)
            return root->son[0]->sz;
        return root->son[0]->sz + root->cnt;
    }
    T kth(int k)
    {
        k++;
        Node *u = root;
        while (true)
        {
            if (u->son[0]->sz >= k)
            {
                u = u->son[0];
                continue;
            }
            k -= u->son[0]->sz;
            if (u->cnt >= k)
                return u->val;
            k -= u->cnt;
            u = u->son[1];
        }
    }
#undef null
#undef root
};

SplayTree<int, 100010> splay;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n);
    splay.init();
    while (n--)
    {
        int op, x;
        readi(op, x);
        switch (op)
        {
        case 1:
            splay.insert(x);
            break;
        case 2:
            splay.remove(x);
            break;
        case 3:
            printf("%d\n", splay.rank(x));
            break;
        case 4:
            printf("%d\n", splay.kth(x));
            break;
        case 5:
            printf("%d\n", splay.prev(x)->val);
            break;
        case 6:
            printf("%d\n", splay.next(x)->val);
            break;
        }
    }
    return 0;
}
*/

/**
* Number:p3369
* Title:【模板】普通平衡树
* Status:AC
* Tag:[fhq treap]
**/

/*
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

template<typename T, int MAXN>
struct Treap
{
    struct Node
    {
        int son[2], size, cnt, w;
        T val;
    }tree[MAXN];
    int node_id, root;
    int makenode(T val)
    {
        Node& nod = tree[++node_id];
        nod = (Node){0, 0, 1, 1, rand(), val};
        return node_id;
    }
    void maintain(int id)
    {
        Node& mid = tree[id];
        const Node& ltree = tree[mid.son[0]];
        const Node& rtree = tree[mid.son[1]];
        mid.size = ltree.size + rtree.size + mid.cnt;
    }
    void splitByValue(T val, int p, int& l, int& r)
    {
        if(p == 0)
        {
            l = r = 0;
            return;
        }
        if(tree[p].val <= val)
        {
            l = p;
            splitByValue(val, tree[p].son[1], tree[l].son[1], r);
        }
        else
        {
            r = p;
            splitByValue(val, tree[p].son[0], l, tree[r].son[0]);
        }
        maintain(p);
    }
    void splitBySize(int size, int p, int& l, int& r)
    {
        if(p == 0)
        {
            l = r = 0;
            return;
        }
        int lsz = tree[tree[p].son[0]].size;
        if(lsz < size)
        {
            l = p;
            splitBySize(size - lsz - tree[p].cnt, tree[p].son[1], tree[l].son[1], r);
        }
        else
        {
            r = p;
            splitBySize(size, tree[p].son[0], l, tree[r].son[0]);
        }
        maintain(p);
    }
    int merge(int l, int r)
    {
        if(l == 0 || r == 0)return l | r;
        int p;
        if(tree[l].w < tree[r].w)
        {
            p = r;
            tree[r].son[0] = merge(l, tree[r].son[0]);
        }
        else
        {
            p = l;
            tree[l].son[1] = merge(tree[l].son[1], r);
        }
        maintain(p);
        return p;
    }
    void insert(T val)
    {
        int l, m, r;
        splitByValue(val, root, l, r);
        splitByValue(val - 1, l, l, m);
        if(m)tree[m].cnt++, tree[m].size++;
        else m = makenode(val);
        root = merge(merge(l, m), r);
    }
    void remove(T val)
    {
        int l, m, r;
        splitByValue(val, root, l, r);
        splitByValue(val - 1, l, l, m);
        if(m)
        {
            if(tree[m].cnt == 1)m = 0;
            else tree[m].cnt--, tree[m].size--;
        }
        root = merge(merge(l, m), r);
    }
    int rank(T val)
    {
        int l, r;
        splitByValue(val - 1, root, l, r);
        int ans = tree[l].size + 1;
        root = merge(l, r);
        return ans;
    }
    T kth(int k)
    {
        int l, r, p;
        splitBySize(k, root, l, r);
        for(p = l; tree[p].son[1]; p = tree[p].son[1]);
        root = merge(l, r);
        return tree[p].val;
    }
    T prev(T val)
    {
        int l, r, p;
        splitByValue(val - 1, root, l, r);
        for(p = l; tree[p].son[1]; p = tree[p].son[1]);
        root = merge(l, r);
        return tree[p].val;
    }
    T next(T val)
    {
        int l, r, p;
        splitByValue(val, root, l, r);
        for(p = r; tree[p].son[0]; p = tree[p].son[0]);
        root = merge(l, r);
        return tree[p].val;
    }
};

Treap<int, 100010> treap;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    while(n--)
    {
        int op,x; readi(op,x);
        switch(op)
        {
        case 1:
            treap.insert(x);
            break;
        case 2:
            treap.remove(x);
            break;
        case 3:
            printf("%d\n",treap.rank(x));
            break;
        case 4:
            printf("%d\n",treap.kth(x));
            break;
        case 5:
            printf("%d\n",treap.prev(x));
            break;
        case 6:
            printf("%d\n",treap.next(x));
            break;
        }
    }
    return 0;
}
*/