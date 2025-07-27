#include <bits/stdc++.h>
using namespace std;
void solve()
{
    using ll = long long;
    int n, m;
    cin >> n >> m;
    vector<ll> dis(n + 1, 1e18);
    vector<tuple<int, int, ll>> edges;
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        edges.emplace_back(u - 1, v, w);
        edges.emplace_back(v, u - 1, -w);
    }
    dis[0] = 0;

    for (int i = 1; i <= n; ++i)
    {
        for (auto [u, v, w] : edges)
        {
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                if (i == n)
                {
                    cout << "false\n";
                    return;
                }
            }

        }
    }
    cout << "true\n";
}
int main()
{
    int T;
    cin >> T;
    while (T--)
        solve();
}