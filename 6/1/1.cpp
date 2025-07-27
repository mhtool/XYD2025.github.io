#include <bits/stdc++.h>
using namespace std;

int main()
{

    int n, m;
    cin >> n >> m;
    vector<vector<int>> edge(n + 1);
    vector<int> val(n + 1, 0);
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1e9));

    for (int i = 1; i <= n; ++i)
    {
        int a, b;
        cin >> a >> b;
        edge[a].push_back(i);
        val[i] = b;
    }

    auto dfs = [&](auto &&self, int u, int f) -> void
    {
        if (u > 0)
            dp[u][1] = val[u];
        else
            dp[u][0] = 0;

        for (auto v : edge[u])
        {
            if (v == f)
                continue;
            self(self, v, u);
            for (int i = m; i >= 0; --i)
                for (int j = 0; j <= i; ++j)
                    if (dp[u][i - j] > -1e9)
                        dp[u][i] = max(dp[u][i], dp[u][i - j] + dp[v][j]);
        }
    };

    dfs(dfs, 0, -1);
    if (dp[0][m] < 0)
        cout << 0 << endl;
    else
        cout << dp[0][m] << endl;
}