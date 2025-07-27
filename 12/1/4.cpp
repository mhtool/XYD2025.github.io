#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    const int mod = 12345;
    vector<int> dp(n + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        dp[i] = dp[i - 1];
        for (int j = 2; j <= i; ++j)
            dp[i] = (dp[i] + 1ll * dp[i - j] * dp[j - 2] % mod) % mod;
    }
    cout << dp[n] << endl;
}