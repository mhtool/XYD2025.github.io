#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int INF = 0x3f3f3f3f;
int n;
vector<vector<int>> dist;
int memo[16][1 << 16];

// 记忆化搜索函数
// i: 当前所在城市
// S: 已访问城市的集合（包含当前城市i）
// 返回值: 从当前状态出发，访问完所有剩余城市并回到起点0的最短路径长度
int dfs(int i, int S)
{
    // 如果所有城市都已访问
    if (S == (1 << n) - 1)
        return dist[i][0]; // 回到起点0

    // 如果已经计算过这个状态
    if (memo[i][S] != -1)
    {
        return memo[i][S];
    }

    int res = INF;
    // 尝试访问所有未访问的城市


    return memo[i][S] = res;
}

int main()
{
    cin >> n;

    dist.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];

    // 初始化记忆化数组
    memset(memo, -1, sizeof(memo));

   
    
    dp[0][1 << 0] = 0;
    for(int S = 0; S < (1 << n); ++S)
    for (int i = 0; i < n; ++i)
        if (S >> i & 1)
        for (int j = 0; j < n; j++)
            if (!(S & (1 << j)))
            {                             // 如果城市j尚未访问
                int new_S = S | (1 << j); // 将城市j加入访问集合
                // 1001 0 3
                // 1011
                // 1001
                // 0010
                ToMin(dp[j][new_S], dp[i][S] + dist[i][j])
            }
    cout << ans << endl;
    return 0;
}
