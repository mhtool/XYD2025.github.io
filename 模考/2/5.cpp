#include <bits/stdc++.h>

// 采用您的代码风格偏好
using namespace std;
const int INF = 1e9;
using ll = long long;


int main()
{

    ll n, m, k;
    cin >> n >> m >> k;

    // dp[i][mask] 表示经过 i 次操作后，
    // 处于 mask 状态（一个位掩码）的总方案数。
    vector<vector<ll>> dp(m + 1, vector<ll>(1 << n, 0));

    // 初始状态：每个物品 i 单独作为起始状态，方案数为 1
    // mask 中只有第 i-1 位为 1
    for (ll i = 1; i <= n; ++i) {
        dp[0][1LL << (i - 1)] = 1;
    }

    // 执行 m 次操作
    for (ll i = 0; i < m; ++i) {
        ll x, y;
        cin >> x >> y;

        // 遍历所有可能的状态 mask
        for (ll mask = 0; mask < (1 << n); ++mask) {
            if (dp[i][mask] == 0) continue; // 优化：跳过无法达到的状态

            bool bit_x = (mask >> (x - 1)) & 1;
            bool bit_y = (mask >> (y - 1)) & 1;
            
            // 状态转移逻辑
            if (bit_x == bit_y) {
                // 如果 x 和 y 的状态相同，两种选择都会导致结果状态不变
                dp[i + 1][mask] += dp[i][mask] * 2;
            } else {
                // 如果 x 和 y 的状态不同
                // 一种选择是状态不变
                dp[i + 1][mask] += dp[i][mask];
                // 另一种选择是其中一个的状态被另一个同化（都变为1）
                dp[i + 1][mask | (1LL << (x - 1)) | (1LL << (y - 1))] += dp[i][mask];
            }
        }
    }

    // 计算总方案数：所有最终状态中，物品 k 的状态位为 1 的方案总和
    ll total_ways = 0;
    for (ll mask = 0; mask < (1 << n); ++mask) {
        if (mask & (1LL << (k - 1))) {
            total_ways += dp[m][mask];
        }
    }

    // 对每个物品 i，计算其与物品 k 同时为 1 的概率
    for (ll i = 1; i <= n; ++i) {
        ll res_ways = 0;
        for (ll mask = 0; mask < (1 << n); ++mask) {
            // 检查物品 i 和物品 k 的状态位是否都为 1
            if ((mask & (1LL << (i - 1))) && (mask & (1LL << (k - 1)))) {
                res_ways += dp[m][mask];
            }
        }
        
        // 计算并输出最简分式
        if (total_ways == 0) { // 避免除以零
            cout << "0/1\n";
        } else {
            ll common_divisor = std::gcd(res_ways, total_ways);
            cout << res_ways / common_divisor << "/" << total_ways / common_divisor << "\n";
        }
    }

}