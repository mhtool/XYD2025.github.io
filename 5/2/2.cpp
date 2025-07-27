#include <bits/stdc++.h>
using namespace std;

int main()
{
    const int inf = 1e9;
    
    int n;
    cin >> n;
    
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    
    a.erase(unique(a.begin(), a.end()), a.end());
    n = a.size() - 1;
    
    vector dp(n + 1, vector(n + 1, inf));
    
    for (int i = 1; i <= n; ++i)
        dp[i][i] = 0;
    
    for (int len = 2; len <= n; ++len)
    {
        for (int i = 1; i + len - 1 <= n; ++i)
        {
            int j = i + len - 1;
            if (a[i] == a[j])
                dp[i][j] = dp[i + 1][j - 1] + 1;
            else
                dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
        }
    }
    
    cout << dp[1][n] << '\n';
}
