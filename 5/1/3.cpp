#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    long long x;
    vector<int> A;
    cin >> x >> m;
    while (x)
        A.push_back(x % 10), x /= 10;
    n = A.size();
    vector<vector<long long>> dp(m, vector<long long>(1 << n));
    dp[0][0] = 1;
    for (int i = 0; i < (1 << n); ++i)
    {
        array<int, 10> vis = {};
        for (int j = 0; j < n; ++j)
        {
            if (i == (1 << j) && A[j] == 0)
                break;
            if ((i >> j & 1) == 0 || vis[A[j]])
                continue;
            vis[A[j]] = 1;
            for (int k = 0; k < m; ++k)
                dp[(k * 10 + A[j]) % m][i] += dp[k][i ^ (1 << j)];
        }
    }
    cout << dp[0][(1 << n) - 1] << '\n';
}