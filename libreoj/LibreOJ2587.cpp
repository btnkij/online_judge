/**
* Number:loj2587
* Title:「APIO2018」铁人两项
* Status:AC
* Tag:[圆方树, Tarjan, 树型DP]
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

const int MAXN = 1e5 + 10;
const int MAXM = 2e5 + 10;
struct Edge
{
    int from, to, nxt;
};
struct Graph
{
    Edge edges[MAXM * 4];
    int head[MAXN * 2], edgeid;
    void init()
    {
        clr(head, -1), edgeid = 0;
    }
    void addedge(int from, int to)
    {
        edges[edgeid] = {from, to, head[from]};
        head[from] = edgeid++;
    }
} G, G1;

int dfn[MAXN], low[MAXN], dfsid;
int grpid;
vector<int> trace;
int w[MAXN * 2], totsz;
void tarjan(int u)
{
    dfn[u] = low[u] = ++dfsid;
    trace.push_back(u);
    totsz++;
    for (int i = G.head[u]; ~i; i = G.edges[i].nxt)
    {
        int v = G.edges[i].to;
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] == dfn[u])
            {
                w[++grpid] = 1;
                G1.addedge(grpid, u), G1.addedge(u, grpid);
                for (int x; x != v; trace.pop_back())
                {
                    x = trace.back();
                    G1.addedge(x, grpid), G1.addedge(grpid, x);
                    ++w[grpid];
                }
            }
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
}

ll ans;
int n, m, sz[MAXN * 2];
void dp(int u, int pre)
{
    sz[u] = int(u <= n);
    ll cnt = 0;
    for (int i = G1.head[u]; ~i; i = G1.edges[i].nxt)
    {
        int v = G1.edges[i].to;
        if (v == pre)
            continue;
        dp(v, u);
        cnt += (ll)sz[u] * sz[v];
        sz[u] += sz[v];
    }
    cnt += (ll)sz[u] * (totsz - sz[u]);
    ans += cnt * w[u];
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n, m);
    G.init(), G1.init();
    repne(i, 0, m)
    {
        int u, v;
        readi(u, v);
        G.addedge(u, v), G.addedge(v, u);
    }
    fill(w + 1, w + n + 1, -1);
    grpid = n;
    rep(i, 1, n) if (!dfn[i])
    {
        totsz = 0;
        trace.clear();
        tarjan(i);
        dp(i, -1);
    }
    printf("%lld\n", ans * 2);
    return 0;
}