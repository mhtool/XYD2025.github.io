#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    struct Edge
    {
        int v, w;
    };
    vector<vector<Edge>> edge(n + 1);
    int ans = 0;
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edge[u].emplace_back(v, w);
        edge[v].emplace_back(u, w);
    }
    auto dfs = [&](auto &&self, int u, int f) -> int
    {
        int d1 = 0, d2 = 0;
        for (int i = head[u]; i; i = nxt[i])
        {
            if (v == f)
                continue;
            int dist = self(self, v, u) + w;
            if (dist > d1)
                d2 = d1, d1 = dist;
            else if (dist > d2)
                d2 = dist;
        }

        ans = max(ans, d1 + d2);
        return d1;
    };

    dfs(dfs, 1, 0);

    cout << ans << endl;

    return 0;
}