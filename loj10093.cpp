/**
* Number:loj10093
* Title:「一本通 3.5 练习 1」网络协议
* Status:AC
* Tag:[tarjan]
**/

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

const int MAXN=110;
struct Edge
{
    int from,to,nxt;
}edges[MAXN*MAXN];
int head[MAXN],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

int dfsid,dfn[MAXN],low[MAXN];
int grpid,grp[MAXN];
stack<int> trace;
void scc(int u)
{
    dfn[u]=low[u]=++dfsid;
    trace.push(u);
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(!dfn[v])scc(v);
        if(!grp[v])low[u]=min(low[u],low[v]);
    }
    if(dfn[u]==low[u])
    {
        int t;
        ++grpid;
        do
        {
            t=trace.top(); trace.pop();
            grp[t]=grpid;
        }while(t!=u);
    }
}

int indeg[MAXN],outdeg[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    clr(head,-1);
    int n; readi(n);
    rep(u,1,n)
    {
        int v;
        while(readi(v)!=EOF && v)addedge(u,v);
    }
    rep(u,1,n)if(!dfn[u])scc(u);
    if(grpid==1)
    {
        printf("1\n0");
        return 0;
    }
    repne(i,0,edgeid)
    {
        int u=edges[i].from, v=edges[i].to;
        if(grp[u]==grp[v])continue;
        outdeg[grp[u]]++, indeg[grp[v]]++;
    }
    auto iszero=[](int x){return int(x==0);};
    int cntin=count_if(indeg+1,indeg+grpid+1,iszero);
    int cntout=count_if(outdeg+1,outdeg+grpid+1,iszero);
    printf("%d\n%d",cntin,max(cntin,cntout));
    return 0;
}