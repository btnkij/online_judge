/**
* Number:spoj1812
* Title:Longest Common Substring II
* Status:AC
* Tag:[后缀自动机, sam]
* desc: 求多个字符串的最长公共子串长度
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
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
struct Node
{
    int link, len, nxt[26]; // 后缀链接，当前节点可以表示的最长子串长度
} sam[MAXN << 1];
int sz = 1, last = 1; // 后缀自动机节点个数，最新的节点编号
void extend(int ch)
{
    int cur = ++sz, pre = last;
    sam[cur].len = sam[pre].len + 1;
    while (pre && !sam[pre].nxt[ch])
    {
        sam[pre].nxt[ch] = cur;
        pre = sam[pre].link;
    }
    if (!pre)
        sam[cur].link = 1;
    else
    {
        int ori = sam[pre].nxt[ch];
        if (sam[ori].len == sam[pre].len + 1)
            sam[cur].link = ori;
        else
        {
            int clone = ++sz;
            sam[clone] = sam[ori];
            sam[clone].len = sam[pre].len + 1;
            sam[cur].link = sam[ori].link = clone;
            while (pre && sam[pre].nxt[ch] == ori)
            {
                sam[pre].nxt[ch] = clone;
                pre = sam[pre].link;
            }
        }
    }
    last = cur;
}

char s[MAXN];
int bin[MAXN], ord[MAXN << 1];       // 桶，节点的拓扑序
int dp[MAXN << 1], dpall[MAXN << 1]; // 当前串与第一个串在节点i匹配的最大长度
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    reads(s);
    int L = strlen(s);
    for (char *p = s; *p; p++)
        extend(*p - 'a');            // 建第一个字符串的后缀自动机
    rep(i, 2, sz) bin[sam[i].len]++; // 桶排序，节点按len排序就是拓扑序
    rep(i, 1, L) bin[i] += bin[i - 1];
    rep(i, 2, sz) ord[bin[sam[i].len]--] = i; // 排序后第i个节点编号是ord[i]
    clr(dpall, INF);
    while (reads(s) != EOF)
    {
        clr(dp, 0);
        int cur = 1, len = 0;
        for (char *p = s; *p; p++)
        {
            int ch = *p - 'a';
            if (sam[cur].nxt[ch]) // 匹配，长度+1
            {
                cur = sam[cur].nxt[ch];
                len++;
                dp[cur] = max(dp[cur], len);
                continue;
            }
            while (cur && !sam[cur].nxt[ch])
                cur = sam[cur].link; // 失配，沿后缀链接后退
            if (cur == 0)
                cur = 1, len = 0; // 如果退到空串
            else
            {
                len = sam[cur].len + 1;
                cur = sam[cur].nxt[ch];
                dp[cur] = max(dp[cur], len);
            }
        }
        for (int i = sz - 1; i >= 1; i--) // dp沿后缀链接向上传递
        {
            int u = ord[i];
            // 如果字符串u可以匹配，它的后缀一定可以匹配
            if (dp[u]) dp[sam[u].link] = sam[sam[u].link].len;
        }
        rep(i, 2, sz) dpall[i] = min(dpall[i], dp[i]);
    }
    int ans = *max_element(dpall + 2, dpall + sz + 1);
    printf("%d", ans);
    return 0;
}