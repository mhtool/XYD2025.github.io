#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edge(n + 1);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
    }
    int cnt = 0;
    vector<int> dfn(n + 1), low(n + 1);
    vector<int> stk, instk(n + 1);

    vector<vector<int>> blks;
    vector<int> blk(n + 1);
    auto tarjan = [&](auto &&self, int u) -> void
    {
        dfn[u] = low[u] = ++cnt;
        stk.push_back(u);
        instk[u] = 1;
        for (int v : edge[u])
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
                blk[v] = now + 1;
                blks[now].push_back(v);
            } while (v != u);
        }
    };

    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(tarjan, i);

    int len = blks.size();
    cout << blks.size() << '\n';
    for (int i = 1; i <= n; ++i)
        cout << blk[i] << ' ';
    cout << '\n';
}