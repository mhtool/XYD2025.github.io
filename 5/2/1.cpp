#include <bits/stdc++.h>
using namespace std;

int main()
{
    using ll = long long;
    const ll inf = 1e18;

    int n;
    cin >> n;

    vector dp(n + 1, vector(n + 1, inf));
    vector a(n + 1, 0), sum(n + 1, 0);

    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    for (int i = 1; i <= n; ++i)
        dp[i][i] = 0;

    for (int len = 2; len <= n; ++len)
    {
        for (int l = 1; l + len - 1 <= n; ++l)
        {
            int r = l + len - 1;
            for (int k = l; k + 1 <= r; ++k)
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + sum[r] - sum[l - 1]);
        }
    }

    cout << dp[1][n] << '\n';
}
