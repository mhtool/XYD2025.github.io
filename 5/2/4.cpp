#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
string l, r, num;
long long ll, len, rr;
// dp[pos][pre][pree]
long long dp[1005][15][15];
long long numl, numr, mod = 1e9 + 7;
long long dfs(int i, bool limit, bool lead, int pre, int pree)
{
    if (i == len + 1)
        return !lead;
    int up = limit ? (num[i - 1] ^ 48) : 9;
    long long res = 0;
    if (!limit && !lead && pre != -1 && pree != -1 && dp[i][pre][pree])
        return dp[i][pre][pree];
    for (int j = 0; j <= up; j++)
    {
        bool li = 0, le = 0;
        int ppr = -1;
        if (j == up && limit)
            li = 1;
        if (lead && j == 0)
            le = 1;
        if ((j == pre || j == pree) && !le)
            continue;
        res = (res + (dfs(i + 1, li, le, (le ? -1 : j), pre) % mod)) % mod;
    }
    if (!limit && !lead && pre != -1 && pree != -1)
        dp[i][pre][pree] = res;
    return res;
}
long long solve(string x, int siz)
{
    num = x;
    len = siz;
    memset(dp, 0, sizeof(dp));
    return dfs(1, 1, 1, -1, -1) % mod;
}
int main()
{
    cin >> l >> r;
    ll = l.size(), rr = r.size();
    for (int i = 0; i < ll; i++)
        numl = (numl * 10 % mod + (l[i] ^ 48)) % mod;
    for (int i = 0; i < rr; i++)
        numr = (numr * 10 % mod + (r[i] ^ 48)) % mod;
    int m = 0;
    char pre = '*', pree = '*';
    for (int i = 0; i < ll; i++)
    {
        if ((l[i] == pre) || (l[i] == pree))
        {
            m = 1;
            break;
        }
        pree = pre;
        pre = l[i];
    }
    long long total = numr - numl + 1;
    long long invalid = solve(r, rr) - (solve(l, ll) - 1 + m);
    long long result = ((total - invalid) % mod + mod) % mod;

    cout << result << endl;
}