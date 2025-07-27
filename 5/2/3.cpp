#include <bits/stdc++.h>
using namespace std;

int main()
{
    using ll = long long;
    
    vector<int> num;
    vector<vector<ll>> dp;
    
    auto dfs = [&](auto&& self, int pos, int pre, bool lead, bool limit) -> ll
    {
        if (pos == 0)
            return 1;
        
        if (!lead && !limit && dp[pos][pre] != -1)
            return dp[pos][pre];
        
        ll ans = 0;
        int up = limit ? num[pos] : 9;
        
        for (int i = 0; i <= up; ++i)
        {
            if (abs(i - pre) < 2 && !lead)
                continue;
            
            ans += self(self, pos - 1, i, lead && i == 0, limit && i == up);
        }
        
        if (!limit && !lead)
            dp[pos][pre] = ans;
        
        return ans;
    };
    
    auto solve = [&](ll x) -> ll
    {
        num.clear();
        num.push_back(0); // 占位，让下标从1开始
        
        ll tmp = x;
        while (tmp)
        {
            num.push_back(tmp % 10);
            tmp /= 10;
        }
        
        int n = num.size() - 1;
        dp.assign(n + 1, vector<ll>(15, -1));
        
        return dfs(dfs, n, -2, 1, 1);
    };
    
    ll a, b;
    cin >> a >> b;
    
    cout << solve(b) - solve(a - 1) << '\n';
    
    return 0;
}
