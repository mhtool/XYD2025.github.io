#include <bits/stdc++.h>
using namespace std;
int main()
{
    typedef long long ll;
    int n, m;
    ll k;
    cin >> n >> m >> k;
    auto a = vector(n, vector<ll>(m));
    for (auto &row : a)
        for (auto &x : row)
            cin >> x;
    int step = (n + m - 2 + 1) / 2;
    ll ans = 0;
    vector<map<ll, int>> dp(n);
    auto dfs = [&](auto &&self, int x, int y, ll now, int p) -> void
    {
        if (x >= n || y >= m || x < 0 || y < 0)
            return;
        now ^= a[x][y];
        if (x + y == step)
        {
            if (p)
                ++dp[x][now];
            else
                ans += dp[x][k ^ now ^ a[x][y]];
            return;
        }
        if (p)
        {
            self(self, x + 1, y, now, p);
            self(self, x, y + 1, now, p);
        }
        else
        {
            self(self, x - 1, y, now, p);
            self(self, x, y - 1, now, p);
        }
    };

    dfs(dfs, 0, 0, 0, 1);
    dfs(dfs, n - 1, m - 1, 0, 0);
    cout << ans << endl;
    return 0;
}