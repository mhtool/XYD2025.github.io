#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> a[i][j];
    const int dx[] = {0, 0, 1, 0};
    const int dy[] = {0, 1, 0, -1};
    auto id = [&](int x, int y)
    {
        return (x - 1) * m + y;
    };
    auto reid = [&](int p)
    {
        return make_pair((p + m - 1) / m, (p + m - 1) % m + 1);
    };
    vector<int> fa((n + 1) * m + 1);
    auto find = [&](int u)
    {
        while (u != fa[u])
            u = fa[u] = fa[fa[u]];
        return u;
    };
    iota(fa.begin(), fa.end(), 0);
    for (int i = 1; i <= k; ++i)
    {
        int x, y;
        cin >> x >> y;
        while (x <= n)
        {
            tie(x, y) = reid(find(id(x, y)));
            if (x == n + 1)
                break;
            int nx = x + dx[a[x][y]];
            int ny = y + dy[a[x][y]];
            a[x][y] = 2;
            fa[id(x, y)] = id(x + 1, y);
            x = nx, y = ny;
        }
        cout << y << " \n"[i == k];
    }
}
