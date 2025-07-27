#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
main()
{
    using ll = long long;
    int n, m;
    ll ans = inf;
    cin >> n >> m;
    if (n == 1) return !puts("0");
    vector<vector<int>> dis(n, vector<int>(n, inf));
    vector<vector<int>> mn(n, vector<int>(1 << n, inf));
    vector<vector<ll>> dp(n + 1, vector<ll>(1 << n, 1ll * inf * inf));
    auto get_dp = [&](int S, int St)
    {
        ll res = 0;
        for (int i = 0; i < n; ++i)
            if (1 << i & St)
                res += mn[i][S];
        return res;
    };
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        dis[u][v] = dis[v][u] = min(dis[u][v], w);
    }
    m = 1 << n;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (1 << j & i)
                for (int k = 0; k < n; ++k)
                    if (!(1 << k & i))
                        mn[k][i] = min(mn[k][i], dis[j][k]); // 预处理出将k塞入到i的最小边权
    for (int i = 0; i < n; ++i)
        dp[0][1 << i] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j < m; ++j)
        // dp[i][j]  h = i / S = j
            for (int k = j & j - 1; k != 0; k = k - 1 & j)
            // h = i - 1, S_last in S
                dp[i][j] = min(dp[i][j], dp[i - 1][k] + i * get_dp(k, k ^ j));
        ans = min(ans, dp[i][m - 1]);
    }
    cout << ans << endl;
}