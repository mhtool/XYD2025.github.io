#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int popcount(int x)
{
    int res = 0;
    while (x) // lowbit
        x -= x & -x, ++res;
    return res;
}

int main()
{
    int n, k;
    cin >> n >> k;
    int S = 1 << n;

    // [S][k]
    auto now = vector(S, vector<long long>(k + 1, 0));
    auto last = now;

    vector<int> status;
    for (int i = 0; i < S; ++i)
        if ((i & (i << 1)) == 0)
            status.push_back(i);

    last[0][0] = 1;

    for (int i = 1; i <= n; ++i) // level
    {
        for (int j : status) // 合法的
        {
            int num_j = popcount(j); // 我们这层要放多少个国王

            int range = j | (j << 1) | (j >> 1);

            for (int t : status) // 上一层的状态
            {
                if (t & range) // 如果上一层的国王在我们的攻击范围内
                    continue;

                for (int l = num_j; l <= k; ++l)
                    // dp[i][j][l] += dp[i - 1][t][l - num_j]
                    now[j][l] += last[t][l - num_j];
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < S; ++i)
        ans += last[i][k];

    cout << ans << endl;

    return 0;
}