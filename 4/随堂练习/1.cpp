#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> s(n + 1), f(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> s[i] >> f[i];
    int s_add = 0, s_limit = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (s[i] < 0)
            s_add -= s[i];
        else
            s_limit += s[i];
    }
    vector<int> dp(s_limit + s_add + 1, -1e9);
    dp[s_add] = 0; // s = 0  dp [0 + s_add]
    for (int i = 1; i <= n; ++i)
    {
        int last
        if (s[i] >= 0)
            for (int j = s_limit + s_add; j >= 0; --j)
                if (j - s[i] >= 0)
                    dp[j] = max(dp[j], dp[j - s[i]] + f[i]);
        else

            for (int j = 0; j <= s_limit + s_add; ++j)
                if (j - s[i] <= s_limit + s_add)
                    dp[j] = max(dp[j], dp[j - s[i]] + f[i]);
    }
    int ans = 0;
    for (int i = s_add; i <= s_limit + s_add; ++i)
    {
        if (dp[i] >= 0) // f >= 0
            ans = max(ans, dp[i] + i - s_add);
    }
    cout << ans << endl;
}