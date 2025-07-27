#include <bits/stdc++.h>
using namespace std;
const int M = 40000 + 10;
int main()
{
    int n;
    cin >> n;
    vector<int> id, map_id(M);
    vector<vector<int>> edge(n + 1);
    int root = 0;
    auto get_id = [&](int x)
    {
        if (x == -1)
            return 0;
        if (!map_id[x])
            id.push_back(x), map_id[x] = id.size();
        return map_id[x];
    };
    for (int i = 1; i <= n; ++i)
    {
        int u, v;
        cin >> u >> v;
        u = get_id(u), v = get_id(v);
        if (u == 0)
            root = v;
        else if (v == 0)
            root = u;
        else
        {
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
    }
    vector<int> dep(n + 1);
    vector<vector<int>> fa(n + 1, vector<int>(20));
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

    dfs(dfs, root, 0);

    for (int i = 1; i < 20; ++i)
        for (int u = 1; u <= n; ++u)
            fa[u][i] = fa[fa[u][i - 1]][i - 1];

    auto get_lca = [&](int u, int v) -> int
    {
        if (dep[u] < dep[v])
            swap(u, v);
        int step = dep[u] - dep[v];
        for (int i = 19; i >= 0; --i)
            if (step & (1 << i))
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

    int q;
    cin >> q;
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        u = get_id(u), v = get_id(v);
        int lca = get_lca(u, v);
        if (u == lca)
            cout << 1 << '\n';
        else if (v == lca)
            cout << 2 << '\n';
        else
            cout << 0 << '\n';
    }
}