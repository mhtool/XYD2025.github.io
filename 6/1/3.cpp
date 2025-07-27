#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

int main()
{
    int n;
    ll m; 
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<vector<ll>> dp(n + 1);
    vector<int> sz(n + 1);

    auto dfs = [&](auto &&self, int u, int f) -> void
    {
        sz[u] = 1;
        dp[u].assign(2, 0LL);

        for (auto [v, w] : adj[u])
        {
            if (v == f) // 避免向上返回父节点
                continue;

            self(self, v, u);

            vector<ll> next_dp(sz[u] + sz[v] + 1, -1e18); // 初始化为一个极小值，表示状态不可达

            for (int i = 0; i <= sz[u]; ++i)
            {
                for (int j = 0; j <= sz[v]; ++j)
                {
                    ll black_in_v = j;
                    ll white_in_v = sz[v] - j;
                    
                    // v 子树外的黑点数
                    ll black_outside_v = m - j;
                    // v 子树外的白点数
                    ll white_outside_v = (n - m) - white_in_v;

                    ll edge_contrib = (ll)w * (black_in_v * black_outside_v + white_in_v * white_outside_v);
                    
                    // 合并后的新状态，总黑点数为 i + j
                    int new_black_count = i + j;
                    ll new_val = dp[u][i] + dp[v][j] + edge_contrib;

                    // 更新合并后的 dp table
                    if (next_dp[new_black_count] < new_val)
                        next_dp[new_black_count] = new_val;
                }
            }
            
            // 更新 u 的子树大小和 dp table
            sz[u] += sz[v];
            dp[u] = next_dp;
        }
    };
    
    // 从节点 1 开始 DFS，父节点设为 0
    dfs(dfs, 1, 0);

    // 最终答案是根节点 1 的 dp table 中，黑点数为 m 时的值
    cout << dp[1][m] << endl;

    return 0;
}