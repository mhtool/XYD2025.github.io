#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int main()
{
    int n, m, num;
    cin >> n >> m >> num;
    auto edge = vector(n + 1, vector(n + 1, vector(num + 1, INF)));
    for (int i = 0; i < m; ++i)
    {
        int l, r, c, w;
        cin >> l >> r >> c >> w;
        edge[l][r][w] = c;
    }
    int full_mask = (1 << num) ;
    auto ans = vector(n + 1, vector(n + 1, vector<int>(num + 1, INF)));
    auto floyd = [&](int mask)
    {
        auto dis = vector(n + 1, vector(n + 1, INF));
        vector<int> used;
        for (int i = 1; i <= num; ++i)
            if (mask & (1 << (i - 1)))
                used.push_back(i);
        for (int i = 1; i<= n; ++i)
            dis[i][i] = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                for (int w : used)
                    dis[i][j] = min(dis[i][j], edge[i][j][w]);
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        int cnt = used.size();
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                ans[i][j][cnt] = min(ans[i][j][cnt], dis[i][j]);
    };

    for (int i = 0; i < full_mask; ++i)
        floyd(i);

    int q;
    cin >> q;
    while (q--)
    {
        int u, v, k;
        cin >> u >> v >> k;
        if (k > num || ans[u][v][k] == INF)
            cout << "NO WAY" << endl;
        else
            cout << ans[u][v][k] << endl;
    }
}