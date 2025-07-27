#include <bits/stdc++.h>
using namespace std;

int main()
{

    int n, m, mod;
    cin >> n >> m >> mod;
    int cnt = 0;
    vector<int> dfn(n + 1), low(n + 1), stk, instk(n + 1);
    vector<vector<int>> blks;
    vector<int> blk(n + 1);
    vector<vector<int>> edge(n + 1);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
    }
    auto tarjan = [&](auto &&self, int u, const vector<vector<int>> &edge) -> void
    {
        dfn[u] = low[u] = ++cnt;
        stk.push_back(u);
        instk[u] = 1;
        for (int v : edge[u])
        {
            if (!dfn[v])
            {
                self(self, v, edge);
                low[u] = min(low[u], low[v]);
            }
            else if (instk[v])
                low[u] = min(low[u], dfn[v]);
        }
        if (dfn[u] == low[u])
        {
            int now_scc_id = blks.size();
            blks.emplace_back();
            int v;
            do
            {
                v = stk.back();
                stk.pop_back();
                instk[v] = 0;
                blk[v] = now_scc_id;
                blks[now_scc_id].push_back(v);
            } while (v != u);
        }
    };
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(tarjan, i, edge);

    int len = blks.size();
    vector<vector<int>> new_edge(len);

    for (int i = 1; i <= n; ++i)
        for (int v : edge[i])
            if (blk[i] != blk[v])
                new_edge[blk[i]].push_back(blk[v]);

    vector<int> deg(len, 0);
    for (int i = 0; i < len; ++i)
    {
        sort(new_edge[i].begin(), new_edge[i].end());
        new_edge[i].erase(unique(new_edge[i].begin(), new_edge[i].end()), new_edge[i].end());
        for (int v : new_edge[i])
            ++deg[v];
    }

    // 拓扑排序和动态规划
    queue<int> q;
    vector<long long> dp_k(len); // K: 最大节点数
    vector<long long> dp_c(len); // C: 方案数

    for (int i = 0; i < len; ++i)
    {
        if (deg[i] == 0)
        {
            q.push(i);
            dp_k[i] = blks[i].size();
            dp_c[i] = 1;
        }
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : new_edge[u])
        {
            long long new_len = dp_k[u] + blks[v].size();

            if (new_len > dp_k[v])
            {
                dp_k[v] = new_len;
                dp_c[v] = dp_c[u];
            }
            else if (new_len == dp_k[v])
                dp_c[v] = (dp_c[v] + dp_c[u]) % mod;

            --deg[v];
            if (deg[v] == 0)
                q.push(v);
        }
    }

    long long ans_k = *max_element(dp_k.begin(), dp_k.end());
    long long ans_c = 0;

    for (int i = 0; i < len; ++i)
        if (dp_k[i] == ans_k)
            ans_c = (ans_c + dp_c[i]) % mod;

    cout << ans_k << endl;
    cout << ans_c << endl;

    return 0;
}