#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    vector<int> b(n * m + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> a[i][j];

    auto get_id = [&](int i, int j)
    {
        int res = (i - 1) * m + j;
        if (res > n * m || res < 0)
            return 0;
        return res;
    };
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            if (a[i][j] == -1)
                continue;
            b[get_id(i, j)] = a[i][j];
        }

    vector<int> fa(n * m + 1);
    iota(fa.begin(), fa.end(), 0);

    auto find = [&](int x)
    {
        while (fa[x] != x)
            x = fa[x] = fa[fa[x]];
        return x;
    };

    auto merge = [&](int x1, int y1, int x2, int y2)
    {
        int id1 = get_id(x1, y1);
        int id2 = get_id(x2, y2);
        id1 = find(id1);
        id2 = find(id2);
        if (id1 == id2)
            return;
        b[id1] += b[id2];
        fa[id2] = id1;
    };
    const pair<int, int> dir[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            if (a[i][j] == -1)
                continue;
            for (auto [dx, dy] : dir)
            {
                int nx = i + dx, ny = j + dy;
                if (nx < 1 || nx > n ||
                    ny < 1 || ny > m ||
                    a[nx][ny] == -1)
                    continue;
                merge(i, j, nx, ny);
            }
        }

    int ans = *max_element(b.begin(), b.end());
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            if (a[i][j] != -1)
                continue;
            set<int> id_set;
            for (auto [dx, dy] : dir)
            {
                int nx = i + dx;
                int ny = j + dy;
                int id = find(get_id(nx, ny));
                id_set.insert(id);
            }
            int res = 0;
            for (auto id : id_set)
                res += b[id];
            ans = max(ans, res);
        }
    cout << ans << endl;
}
