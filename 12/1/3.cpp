#include <bits/stdc++.h>
using namespace std;
int main()
{
    const int mod = 1e9 + 7;
    int n;
    cin >> n;
    vector<int> dp(n + 1);
    dp[0] = 1;
    dp[1] = 0;
    for (int i = 2; i <= n; ++i)
        dp[i] = (1ll * (i - 1) * (dp[i - 1] + dp[i - 2])) % mod;
    cout << dp[n] << endl;
}