#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    vector<vector<int>> edge(n + 1);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
    }
    int cnt = 0;
    vector<int> dfn(n + 1), low(n + 1), stk, instk(n + 1);
    vector<vector<int>> blks;
    vector<int> blk(n + 1);
    auto tarjan = [&](auto &&self, int u) -> void
    {
        dfn[u] = low[u] = ++cnt;
        stk.push_back(u);
        instk[u] = 1;
        for (auto v : edge[u])
        {
            if (!dfn[v])
            {
                self(self, v);
                low[u] = min(low[u], low[v]);
            }
            else if (instk[v])
            {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u])
        {
            int now = blks.size();
            blks.emplace_back();
            int v;
            do
            {
                v = stk.back();
                stk.pop_back();
                instk[v] = 0;
                blk[v] = now;
                blks[now].push_back(v);
            } while (v != u);
        }
    };

    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(tarjan, i);

    int len = blks.size();
    vector<vector<int>> new_edge(len);
    vector<int> deg(len);
    vector<long long> b(len);

    for (int i = 1; i <= n; ++i)
        b[blk[i]] += a[i];
    for (int i = 1; i <= n; ++i)
        for (int v : edge[i])
            if (blk[i] != blk[v])
            {
                new_edge[blk[i]].push_back(blk[v]);
                ++deg[blk[v]];
            }
    
    queue<int> q;
    vector<long long> dp(len);
    for (int i = 0; i < len; ++i)
        if (deg[i] == 0)
            q.push(i), dp[i] = b[i];
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : new_edge[u])
        {
            dp[v] = max(dp[v], dp[u] + b[u]);
            --deg[v];
            if (deg[v] == 0)
                q.push(v);
        }
    }
    long long ans = *max_element(dp.begin(), dp.end());
    cout << ans << endl;
}