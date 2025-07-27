#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, p;
const int N = 220;

int main()
{
    cin >> n >> p;
    vector<vector<int>> edge(n + 1);
    vector<int> fa(n + 1);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
        fa[v] = u;
    }
    vector<int> sz(n + 1);
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 1e9));
    int root = 1;
    // for (int i = 1; i <= n; ++i)
    //     if (!fa[i])
    //         root = i;
    auto dfs = [&](auto &&self, int u, int f) -> void
    {
        dp[u][1] = 0;
        sz[u] = 1;

        for (int v : edge[u])
        {
            if (v == f)
                continue;
            self(self, v, u);
            sz[u] += sz[v];
            auto tmp = dp[u];
            for (int j = 1; j <= sz[u]; ++j)
                ++tmp[j];
            for (int j = sz[u]; j >= 1; --j)
                for (int k = min(j - 1, sz[v]); k >= 1; --k)
                    tmp[j] = min(tmp[j], dp[u][j - k] + dp[v][k]);
            dp[u] = tmp;
        }
    };
    dfs(dfs, root, 0);

    int ans = dp[root][p];
    for (int i = 1; i <= n; ++i)
        ans = min(ans, dp[i][p] + 1);
    cout << ans << endl;
    return 0;
}