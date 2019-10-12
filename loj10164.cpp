/**
* Number:loj10164
* Title:「一本通 5.3 例 2」数字游戏
* Status:AC
* Tag:[数位dp]
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

vector<int> num;
int dfs(int dep,int pre,bool bound)
{
    if(dep==-1)return 1;
    int lim=bound?num[dep]:9;
    int ans=0;
    for(int i=pre;i<=lim;i++)ans+=dfs(dep-1,i,bound&&i==lim);
    return ans;
}
int solve(int x)
{
    num.clear();
    for(;x;x/=10)num.push_back(x%10);
    return dfs(num.size()-1,0,true);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int a,b;
    while(readi(a,b)!=EOF)
    {
        printf("%d\n",solve(b)-solve(a-1));
    }
    return 0;
}