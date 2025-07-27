#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n;
    vector<vector<int>> edge(n + 1);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    cin >> m;
    vector<int> node_list(1, 1);
    vector<int> dep(n + 1);
    vector<vector<int>> fa(n + 1, vector<int>(20));
    for (int i = 1; i <= m; ++i)
    {
        int x;
        cin >> x;
        node_list.push_back(x);
    }
    auto dfs = [&](auto &&self, int u, int f) -> void
    {
        fa[u][0] = f;
        for (int v : edge[u])
            if (v != f)
            {
                dep[v] = dep[u] + 1;
                self(self, v, u);
            }
    };

    dfs(dfs, 1, 0);

    for (int i = 1; i < 20; ++i)
        for (int u = 1; u <= n; ++u)
            fa[u][i] = fa[fa[u][i - 1]][i - 1];

    auto get_lca = [&](int u, int v) -> int
    {
        if (dep[u] < dep[v])
            swap(u, v);
        for (int i = 19; i >= 0; --i)
            if (dep[fa[u][i]] >= dep[v])
                u = fa[u][i];
        if (u == v)
            return u;
        for (int i = 19; i >= 0; --i)
            if (fa[u][i] != fa[v][i])
            {
                u = fa[u][i];
                v = fa[v][i];
            }
        return fa[u][0];
    };

    auto get_dis = [&](int u, int v) -> int
    {
        int lca = get_lca(u, v);
        return dep[u] + dep[v] - 2 * dep[lca];
    };

    long long ans = 0;

    int last = 1;
    for (int x : node_list)
    {
        ans += get_dis(last, x);
        last = x;
    }
    
    cout << ans << endl;
}