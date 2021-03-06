/**
* Number:hdu5762
* Title:Teacher Bo
* Status:AC
* Tag:[鸽巢原理]
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
#define PI acos(-1)
typedef long long ll;

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

bool vis[200100];
int x[100010],y[100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n,m; readi2(n,m);
        mset(vis,false);
        repne(i,0,n)readi2(x[i],y[i]);
        bool f=false;
        repne(i,0,n)
        {
            repne(j,i+1,n)
            {
                int d=abs(x[i]-x[j])+abs(y[i]-y[j]);
                if(vis[d])
                {
                    printf("YES\n");
                    goto label;
                }
                vis[d]=true;
            }
        }
        printf("NO\n");
        label:;
    }
    return 0;
}