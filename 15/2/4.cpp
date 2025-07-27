#include <bits/stdc++.h>
using namespace std;
void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    s = " " + s;
    vector<int> pi(n + 1);
    for (int i = 2; i <= n; ++i)
    {
        int len = pi[i - 1];
        while (len && s[i] != s[len + 1])
            len = pi[len];
        if (s[i] == s[len + 1])
            ++len;
        pi[i] = len;
    }

    vector<int> dep(n + 1);
    for (int i = 1; i <= n; ++i)
        dep[i] = dep[pi[i]] + 1;

    vector<vector<int>> edges(n + 1);
    for (int i = 1; i <= n; ++i)
        edges[pi[i]].push_back(i);
    vector<int> stk(n + 1);
    int top = 0;
    long long ans = 1;
    const int mod = 1e9 + 7;

    function<void(int, int)> dfs = [&](int u, int now_id)
    {
        if (u != 0)
            stk[++top] = u;

        while (now_id + 1 <= top && stk[now_id + 1] <= u / 2)
            ++now_id;

        ans = 1ll * ans * (now_id + 1) % mod;

        for (int v : edges[u])
            dfs(v, now_id);

        --top;
    };

    dfs(0, 0);

    cout << ans << endl;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
}